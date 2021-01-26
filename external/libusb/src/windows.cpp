/*
 * avrdude - A Downloader/Uploader for AVR device programmers
 * Copyright (C) 2019 Marius Greuel
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "libwinusb.h"

extern "C"
{
#include "error.h"
#include "usbi.h"
}

static std::string CreateMessageFromError(HRESULT hr)
{
    LPSTR pszMessage = nullptr;
    DWORD dwChars = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, hr, 0, (LPSTR)&pszMessage, 0, nullptr);
    if (dwChars > 0 && pszMessage != nullptr)
    {
        if (dwChars > 0 && pszMessage[dwChars - 1] == '\n')
            dwChars--;

        if (dwChars > 0 && pszMessage[dwChars - 1] == '\r')
            dwChars--;

        std::string message = std::string(pszMessage, dwChars);
        LocalFree(pszMessage);
        return message;
    }
    else
    {
        return "Unknown error";
    }
}

static int usb_hresult_to_errno(HRESULT hr)
{
    if (SUCCEEDED(hr))
        return 0;

    switch (hr)
    {
    case HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER):
        return EINVAL;
    case HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY):
        return ENOMEM;
    case HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED):
        return EPERM;
    case HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE):
    case HRESULT_FROM_WIN32(ERROR_BAD_DEVICE):
    case HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND):
        return ENODEV;
    case HRESULT_FROM_WIN32(ERROR_SEM_TIMEOUT):
    case HRESULT_FROM_WIN32(ERROR_OPERATION_ABORTED):
        return ETIMEDOUT;
    default:
        return EIO;
    }
}

void usb_os_init(void)
{
}

void usb_set_debug(int level)
{
    if (usb_log_get_level() || level)
    {
        USBMSG("setting debugging level to %d (%s)\n", level, level ? "on" : "off");
    }

    usb_log_set_level(static_cast<USB_LOG_LEVEL>(level));
}

int usb_os_find_busses(struct usb_bus** busses)
{
    auto bus = static_cast<struct usb_bus*>(std::malloc(sizeof(struct usb_bus)));
    if (bus == nullptr)
    {
        USBERR("memory allocation failed\n");
        return -ENOMEM;
    }

    std::memset(bus, 0, sizeof(*bus));
    std::strcpy(bus->dirname, "bus-0");

    USBMSG("found %s\n", bus->dirname);

    *busses = bus;
    return 0;
}

int usb_os_find_devices(struct usb_bus* bus, struct usb_device** devices)
{
    if (bus == nullptr)
    {
        return -EINVAL;
    }

    if (devices == nullptr)
    {
        return -EINVAL;
    }

    LibWinUsb::UsbDeviceEnumerator enumerator;
    HRESULT hr = enumerator.EnumerateDevices();
    if (FAILED(hr))
    {
        return -1;
    }

    struct usb_device* fdev = nullptr;

    const auto& list = enumerator.GetDevices();
    for (const auto& item : list)
    {
        struct usb_device* dev = static_cast<struct usb_device*>(std::malloc(sizeof(struct usb_device)));
        if (dev == nullptr)
        {
            USBERR0("memory allocation failed\n");
            return -ENOMEM;
        }

        std::memset(dev, 0, sizeof(*dev));

        std::unique_ptr<LibWinUsb::UsbDriver> driver;
        if (FAILED(item->Open(driver)) ||
            FAILED(driver->GetDescriptor(USB_DT_DEVICE, 0, 0, &dev->descriptor, sizeof(dev->descriptor), nullptr, 5000)))
        {
            free(dev);
            continue;
        }

        _snprintf(dev->filename, LIBUSB_PATH_MAX - 1, "%s--%s",
            LibWinUsb::Encoding::ToAnsi(item->GetInterfacePath()).c_str(),
            LibWinUsb::Encoding::ToAnsi(item->GetService()).c_str());

        LIST_ADD(fdev, dev);

        USBMSG("found %s on %s\n", dev->filename, bus->dirname);
    }

    *devices = fdev;
    return 0;
}

int usb_os_determine_children(struct usb_bus* bus)
{
    return 0;
}

int usb_os_open(usb_dev_handle* dev)
{
    if (dev == nullptr)
    {
        USBERR("invalid device handle %p", dev);
        return -EINVAL;
    }

    dev->impl_info = nullptr;
    dev->config = 0;
    dev->interface = -1;
    dev->altsetting = -1;

    std::string dev_name = dev->device->filename;
    auto pos = dev_name.find("--");
    if (pos == std::string::npos)
    {
        USBERR("invalid file name %s\n", dev->device->filename);
        return -ENOENT;
    }

    std::unique_ptr<LibWinUsb::UsbDriver> driver;
    HRESULT hr = LibWinUsb::UsbDevice::Open(LibWinUsb::Encoding::ToUnicode(dev_name.substr(pos + 2)), LibWinUsb::Encoding::ToUnicode(dev_name.substr(0, pos)), driver);
    if (FAILED(hr))
    {
        USBERR("failed to open %s: win error: %s\n", dev->device->filename, CreateMessageFromError(hr).c_str());
        return -ENOENT;
    }

    dev->impl_info = driver.release();

    return 0;
}

int usb_os_close(usb_dev_handle* dev)
{
    delete static_cast<LibWinUsb::UsbDriver*>(dev->impl_info);

    dev->impl_info = nullptr;
    dev->interface = -1;
    dev->altsetting = -1;

    return 0;
}

int usb_control_msg(usb_dev_handle* dev, int requestType, int request, int value, int index, char* bytes, int size, int timeout)
{
    if (dev->impl_info == nullptr)
    {
        USBERR0("error: device not open\n");
        return -EINVAL;
    }

    if (requestType == (USB_ENDPOINT_IN | USB_TYPE_STANDARD | USB_RECIP_DEVICE) && request == USB_REQ_GET_DESCRIPTOR)
    {
        uint32_t bytesReturned = 0;
        HRESULT hr = static_cast<LibWinUsb::UsbDriver*>(dev->impl_info)->GetDescriptor(
            static_cast<uint8_t>(value >> 8),
            static_cast<uint8_t>(value),
            static_cast<uint16_t>(index),
            bytes,
            static_cast<uint16_t>(size),
            &bytesReturned,
            timeout);
        if (FAILED(hr))
        {
            return -usb_hresult_to_errno(hr);
        }

        return static_cast<int>(bytesReturned);
    }
    else
    {
        uint32_t bytesReturned = 0;
        HRESULT hr = static_cast<LibWinUsb::UsbDriver*>(dev->impl_info)->ControlTransfer(
            static_cast<uint8_t>(requestType),
            static_cast<uint8_t>(request),
            static_cast<uint16_t>(value),
            static_cast<uint16_t>(index),
            bytes,
            static_cast<uint16_t>(size),
            &bytesReturned,
            timeout);
        if (FAILED(hr))
        {
            return -usb_hresult_to_errno(hr);
        }

        return static_cast<int>(bytesReturned);
    }
}

int usb_set_configuration(usb_dev_handle* dev, int configuration)
{
    if (dev->impl_info == nullptr)
    {
        USBERR0("error: device not open\n");
        return -EINVAL;
    }

    if (dev->config == configuration)
    {
        return 0;
    }

    if (dev->interface >= 0)
    {
        USBERR0("can't change configuration, an interface is still in use (claimed)\n");
        return -EINVAL;
    }

    HRESULT hr = static_cast<LibWinUsb::UsbDriver*>(dev->impl_info)->SetConfiguration(static_cast<uint8_t>(configuration));
    if (FAILED(hr))
    {
        return -usb_hresult_to_errno(hr);
    }

    dev->config = configuration;
    dev->interface = -1;
    dev->altsetting = -1;

    return 0;
}

int usb_claim_interface(usb_dev_handle* dev, int interface)
{
    if (dev->impl_info == nullptr)
    {
        USBERR0("device not open\n");
        return -EINVAL;
    }

    if (dev->config == 0)
    {
        USBERR("could not claim interface %d, invalid configuration %d\n", interface, dev->config);
        return -EINVAL;
    }

    if (dev->interface == interface)
    {
        return 0;
    }

    HRESULT hr = static_cast<LibWinUsb::UsbDriver*>(dev->impl_info)->ClaimInterface(static_cast<uint8_t>(interface));
    if (FAILED(hr))
    {
        return -usb_hresult_to_errno(hr);
    }

    dev->interface = interface;
    dev->altsetting = 0;

    return 0;
}

int usb_release_interface(usb_dev_handle* dev, int interface)
{
    if (dev->impl_info == nullptr)
    {
        USBERR0("device not open\n");
        return -EINVAL;
    }

    if (dev->config == 0)
    {
        USBERR("could not release interface %d, invalid configuration %d\n", interface, dev->config);
        return -EINVAL;
    }

    HRESULT hr = static_cast<LibWinUsb::UsbDriver*>(dev->impl_info)->ReleaseInterface(static_cast<uint8_t>(interface));
    if (FAILED(hr))
    {
        return -usb_hresult_to_errno(hr);
    }

    dev->interface = -1;
    dev->altsetting = -1;

    return 0;
}

int usb_set_altinterface(usb_dev_handle* dev, int alternate)
{
    if (dev->impl_info == nullptr)
    {
        USBERR0("device not open\n");
        return -EINVAL;
    }

    if (dev->config == 0)
    {
        USBERR("could not set alt interface %d: invalid configuration %d\n", alternate, dev->config);
        return -EINVAL;
    }

    if (dev->interface < 0)
    {
        USBERR("could not set alt interface %d: no interface claimed\n", alternate);
        return -EINVAL;
    }

    HRESULT hr = static_cast<LibWinUsb::UsbDriver*>(dev->impl_info)->SetAlternateSetting(
        static_cast<uint8_t>(dev->interface),
        static_cast<uint8_t>(alternate));
    if (FAILED(hr))
    {
        return -usb_hresult_to_errno(hr);
    }

    dev->altsetting = alternate;

    return 0;
}

int usb_bulk_read(usb_dev_handle* dev, int ep, char* bytes, int size, int timeout)
{
    if (dev->impl_info == nullptr)
    {
        USBERR0("device not open\n");
        return -EINVAL;
    }

    if (dev->config == 0)
    {
        USBERR("invalid configuration %d\n", dev->config);
        return -EINVAL;
    }

    if (dev->interface < 0)
    {
        USBERR("invalid interface %d\n", dev->interface);
        return -EINVAL;
    }

    if ((ep & USB_ENDPOINT_IN) == 0)
    {
        USBERR("invalid endpoint 0x%02x", ep);
        return -EINVAL;
    }

    uint32_t bytesRead = 0;
    HRESULT hr = static_cast<LibWinUsb::UsbDriver*>(dev->impl_info)->ReadPipe(
        static_cast<uint8_t>(ep),
        bytes,
        size,
        &bytesRead,
        timeout);
    if (FAILED(hr))
    {
        return -usb_hresult_to_errno(hr);
    }

    return static_cast<int>(bytesRead);
}

int usb_bulk_write(usb_dev_handle* dev, int ep, char* bytes, int size, int timeout)
{
    if (dev->impl_info == nullptr)
    {
        USBERR0("device not open\n");
        return -EINVAL;
    }

    if (dev->config == 0)
    {
        USBERR("invalid configuration %d\n", dev->config);
        return -EINVAL;
    }

    if (dev->interface < 0)
    {
        USBERR("invalid interface %d\n", dev->interface);
        return -EINVAL;
    }

    if ((ep & USB_ENDPOINT_IN) != 0)
    {
        USBERR("invalid endpoint 0x%02x", ep);
        return -EINVAL;
    }

    uint32_t bytesWritten = 0;
    HRESULT hr = static_cast<LibWinUsb::UsbDriver*>(dev->impl_info)->WritePipe(
        static_cast<uint8_t>(ep),
        bytes,
        size,
        &bytesWritten,
        timeout);
    if (FAILED(hr))
    {
        return -usb_hresult_to_errno(hr);
    }

    return static_cast<int>(bytesWritten);
}

int usb_interrupt_read(usb_dev_handle* dev, int ep, char* bytes, int size, int timeout)
{
    return usb_bulk_read(dev, ep, bytes, size, timeout);
}

int usb_interrupt_write(usb_dev_handle* dev, int ep, char* bytes, int size, int timeout)
{
    return usb_bulk_write(dev, ep, bytes, size, timeout);
}
