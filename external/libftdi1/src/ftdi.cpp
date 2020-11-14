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

#include "libwinftdi.h"
#include <winsock2.h>
#include <ftdi.h>

using namespace LibWinFtdi;

static ftdi_chip_type MapChipType(ULONG type)
{
    switch (type)
    {
    case FT_DEVICE_BM:
        return TYPE_BM;
    case FT_DEVICE_AM:
        return TYPE_AM;
    case FT_DEVICE_100AX:
        return TYPE_AM;
    case FT_DEVICE_2232C:
        return TYPE_2232C;
    case FT_DEVICE_232R:
        return TYPE_R;
    case FT_DEVICE_2232H:
        return TYPE_2232H;
    case FT_DEVICE_4232H:
        return TYPE_4232H;
    case FT_DEVICE_232H:
        return TYPE_232H;
    default:
        return TYPE_AM;
    }
}

static int SetError(struct ftdi_context* ftdi, int result, const char* error_str)
{
    if (ftdi != nullptr)
    {
        ftdi->error_str = error_str;
    }

    return result;
}

const char* ftdi_get_error_string(struct ftdi_context* ftdi)
{
    return ftdi != nullptr && ftdi->error_str != nullptr ? ftdi->error_str : "unknown error";
}

struct ftdi_context* ftdi_new(void)
{
    struct ftdi_context* ftdi = new struct ftdi_context();

    if (ftdi_init(ftdi) != 0)
    {
        delete ftdi;
        return nullptr;
    }

    return ftdi;
}

void ftdi_free(struct ftdi_context* ftdi)
{
    ftdi_deinit(ftdi);
    delete ftdi;
}

int ftdi_set_interface(struct ftdi_context* ftdi, enum ftdi_interface interface)
{
    if (ftdi == nullptr)
    {
        return SetError(ftdi, -2, "USB device unavailable");
    }

    if (ftdi->usb_dev != nullptr)
    {
        if (ftdi->index != (interface != INTERFACE_ANY ? interface : INTERFACE_A))
        {
            return SetError(ftdi, -3, "Interface can not be changed on an already open device");
        }
    }

    switch (interface)
    {
    case INTERFACE_ANY:
    case INTERFACE_A:
        ftdi->interface = 0;
        ftdi->index = INTERFACE_A;
        break;
    case INTERFACE_B:
        ftdi->interface = 1;
        ftdi->index = INTERFACE_B;
        break;
    case INTERFACE_C:
        ftdi->interface = 2;
        ftdi->index = INTERFACE_C;
        break;
    case INTERFACE_D:
        ftdi->interface = 3;
        ftdi->index = INTERFACE_D;
        break;
    default:
        return SetError(ftdi, -1, "Unknown interface");
    }

    return 0;
}

int ftdi_init(struct ftdi_context* ftdi)
{
    std::memset(ftdi, 0, sizeof(struct ftdi_context));
    return 0;
}

void ftdi_deinit(struct ftdi_context* ftdi)
{
    if (ftdi != nullptr && ftdi->usb_dev != nullptr)
    {
        std::unique_ptr<FtdiDevice> device(reinterpret_cast<FtdiDevice*>(ftdi->usb_dev));
        ftdi->usb_dev = nullptr;
    }
}

int ftdi_usb_open_desc_index(struct ftdi_context* ftdi, int vendor, int product,
    const char* description, const char* serial, unsigned int index)
{
    if (ftdi == nullptr)
    {
        return SetError(ftdi, -3, "invalid ftdi context");
    }

    FtdiEnumerator enumerator;
    auto status = enumerator.EnumerateDevices();
    if (status != FT_OK)
    {
        return SetError(ftdi, -3, "failed to enumerate devices");
    }

    for (auto const& info : enumerator.GetDevices())
    {
        if ((info.Flags & FT_FLAGS_OPENED) != 0)
            continue;

        if (vendor != static_cast<uint16_t>(info.ID >> 16))
            continue;

        if (product != static_cast<uint16_t>(info.ID >> 0))
            continue;

        if (description != nullptr && strcmp(description, info.Description) != 0)
            continue;

        if (serial != nullptr && strcmp(serial, info.SerialNumber) != 0)
            continue;

        if (index > 0)
        {
            index--;
            continue;
        }

        auto device = std::make_unique<FtdiDevice>();
        FT_STATUS status = device->OpenBySerialNumber(info.SerialNumber);
        if (status == FT_OK)
        {
            device->ResetDevice();
            device->Purge();
            device->SetBitMode(0, 0);
            device->SetTimeouts(5000, 5000);
            status = device->SetEventNotification(FT_EVENT_RXCHAR);
        }

        if (status != FT_OK)
        {
            return SetError(ftdi, -3, "failed to open device");
        }

        ftdi->type = MapChipType(info.Type);
        ftdi->usb_dev = reinterpret_cast<struct libusb_device_handle*>(device.release());
        return 0;
    }

    return SetError(ftdi, -3, "device not found");
}

int ftdi_usb_close(struct ftdi_context* ftdi)
{
    if (ftdi == nullptr || ftdi->usb_dev == nullptr)
    {
        return SetError(ftdi, -3, "invalid device");
    }

    auto device = reinterpret_cast<FtdiDevice*>(ftdi->usb_dev);
    auto status = device->Close();
    if (status != FT_OK)
    {
        return SetError(ftdi, -1, "Failed to close device");
    }

    return 0;
}

int ftdi_usb_purge_buffers(struct ftdi_context* ftdi)
{
    if (ftdi == nullptr || ftdi->usb_dev == nullptr)
    {
        return SetError(ftdi, -3, "invalid device");
    }

    auto device = reinterpret_cast<FtdiDevice*>(ftdi->usb_dev);
    auto status = device->Purge();
    if (status != FT_OK)
    {
        return SetError(ftdi, -1, "Failed to purge buffers");
    }

    return 0;
}

int ftdi_set_baudrate(struct ftdi_context* ftdi, int baudrate)
{
    if (ftdi == nullptr || ftdi->usb_dev == nullptr)
    {
        return SetError(ftdi, -3, "invalid device");
    }

    if (ftdi->bitbang_enabled)
    {
        baudrate /= 16;
    }

    if (baudrate <= 0)
    {
        return SetError(ftdi, -1, "invalid baudrate");
    }

    auto device = reinterpret_cast<FtdiDevice*>(ftdi->usb_dev);
    auto status = device->SetBaudRate(baudrate);
    if (status != FT_OK)
    {
        return SetError(ftdi, -2, "Failed to set baudrate");
    }

    ftdi->baudrate = baudrate;
    return 0;
}

int ftdi_set_bitmode(struct ftdi_context* ftdi, unsigned char bitmask, unsigned char mode)
{
    if (ftdi == nullptr || ftdi->usb_dev == nullptr)
    {
        return SetError(ftdi, -2, "invalid device");
    }

    auto device = reinterpret_cast<FtdiDevice*>(ftdi->usb_dev);
    auto status = device->SetBitMode(bitmask, mode);
    if (status != FT_OK)
    {
        return SetError(ftdi, -1, "Failed to set bitmode");
    }

    ftdi->bitbang_mode = mode;
    ftdi->bitbang_enabled = mode == BITMODE_RESET ? 0 : 1;
    return 0;
}

int ftdi_set_latency_timer(struct ftdi_context* ftdi, unsigned char latency)
{
    if (ftdi == nullptr || ftdi->usb_dev == nullptr)
    {
        return SetError(ftdi, -3, "invalid device");
    }

    if (latency < 1)
    {
        return SetError(ftdi, -1, "invalid latency");
    }

    auto device = reinterpret_cast<FtdiDevice*>(ftdi->usb_dev);
    auto status = device->SetLatencyTimer(latency);
    if (status != FT_OK)
    {
        return SetError(ftdi, -1, "Failed to set latency timer");
    }

    return 0;
}

int ftdi_read_data(struct ftdi_context* ftdi, unsigned char* buf, int size)
{
    if (ftdi == nullptr || ftdi->usb_dev == nullptr)
    {
        return SetError(ftdi, -666, "invalid device");
    }

    auto device = reinterpret_cast<FtdiDevice*>(ftdi->usb_dev);

    auto handle = device->GetNotificationEvent();
    if (handle != nullptr)
    {
        DWORD dwStatus = WaitForSingleObject(handle, 1000);
        if (dwStatus != WAIT_OBJECT_0)
        {
            return 0;
        }
    }

    DWORD bytesInQueue = 0;
    auto status = device->GetQueueStatus(&bytesInQueue);
    if (status != FT_OK)
    {
        return SetError(ftdi, -1, "Failed to get queue status");
    }

    DWORD bytesRead = 0;
    if (bytesInQueue > 0)
    {
        if (size > static_cast<int>(bytesInQueue))
            size = static_cast<int>(bytesInQueue);

        status = device->Read(buf, size, &bytesRead);
        if (status != FT_OK)
        {
            return SetError(ftdi, -1, "Failed to read data");
        }
    }

    return bytesRead;
}

int ftdi_write_data(struct ftdi_context* ftdi, const unsigned char* buf, int size)
{
    if (ftdi == nullptr || ftdi->usb_dev == nullptr)
    {
        return SetError(ftdi, -666, "invalid device");
    }

    auto device = reinterpret_cast<FtdiDevice*>(ftdi->usb_dev);

    DWORD bytesWritten = 0;
    auto status = device->Write(const_cast<unsigned char*>(buf), size, &bytesWritten);
    if (status != FT_OK)
    {
        return SetError(ftdi, -1, "Failed to write data");
    }

    return bytesWritten;
}
