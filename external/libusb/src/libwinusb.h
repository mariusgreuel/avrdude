//
// libwinusb.h
// Copyright (C) 2019 Marius Greuel. All rights reserved.
//

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cerrno>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>
#include <winusb.h>
#include <winioctl.h>
#include <devpkey.h>
#include <usbiodef.h>
#include <setupapi.h>
#include <strsafe.h>
#include <lusb0_usb.h>

#pragma comment(lib, "winusb")
#pragma comment(lib, "setupapi")

namespace LibWinUsb
{
    class Handle
    {
    public:
        Handle() = default;

        ~Handle()
        {
            Close();
        }

        Handle(const Handle&) = delete;
        Handle& operator=(const Handle& other) = delete;
        Handle(Handle&&) = default;
        Handle& operator=(Handle&& other) = default;

        operator HANDLE() const noexcept
        {
            return m_handle;
        }

        void Close() noexcept
        {
            if (m_handle != nullptr)
            {
                CloseHandle(m_handle);
                m_handle = nullptr;
            }
        }

        void Attach(HANDLE handle) noexcept
        {
            assert(m_handle == nullptr);
            m_handle = handle;
        }

        HANDLE Detach() noexcept
        {
            HANDLE handle = m_handle;
            m_handle = nullptr;
            return handle;
        }

    protected:
        HANDLE m_handle = nullptr;
    };

    class Event : public Handle
    {
    public:
        Event() = default;
        Event(const Event&) = delete;
        Event& operator=(const Event& other) = delete;
        Event(Event&&) = default;
        Event& operator=(Event&& other) = default;

        HRESULT Create(BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName = nullptr, LPSECURITY_ATTRIBUTES lpAttributes = nullptr) noexcept
        {
            HANDLE hEvent = CreateEventW(lpAttributes, bManualReset, bInitialState, lpName);
            if (hEvent == nullptr)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            Close();
            Attach(hEvent);
            return S_OK;
        }

        HRESULT Open(LPCWSTR lpName, DWORD dwDesiredAccess = EVENT_ALL_ACCESS, BOOL bInheritHandle = FALSE) noexcept
        {
            HANDLE hEvent = OpenEventW(dwDesiredAccess, bInheritHandle, lpName);
            if (hEvent == nullptr)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            Close();
            Attach(hEvent);
            return S_OK;
        }

        HRESULT Set() noexcept
        {
            if (!SetEvent(m_handle))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            return S_OK;
        }

        HRESULT Reset() noexcept
        {
            if (!ResetEvent(m_handle))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            return S_OK;
        }
    };

    class AutoResetEvent : public Event
    {
    public:
        HRESULT Create(BOOL bInitialState = FALSE, LPCWSTR lpName = nullptr, LPSECURITY_ATTRIBUTES lpAttributes = nullptr)
        {
            return Event::Create(FALSE, bInitialState, lpName, lpAttributes);
        }
    };

    class ManualResetEvent : public Event
    {
    public:
        HRESULT Create(BOOL bInitialState = FALSE, LPCWSTR lpName = nullptr, LPSECURITY_ATTRIBUTES lpAttributes = nullptr)
        {
            return Event::Create(TRUE, bInitialState, lpName, lpAttributes);
        }
    };

    class Encoding
    {
    public:
        static std::string ToAnsi(const std::wstring& text)
        {
            std::string str;

            if (!text.empty())
            {
                int chars = ::WideCharToMultiByte(CP_ACP, 0, text.c_str(), static_cast<int>(text.size()), nullptr, 0, nullptr, nullptr);
                if (chars == 0)
                {
                    return std::string();
                }

                str.resize(chars);
                chars = ::WideCharToMultiByte(CP_ACP, 0, text.c_str(), static_cast<int>(text.size()), &str[0], static_cast<int>(str.size()), nullptr, nullptr);
                if (chars == 0)
                {
                    return std::string();
                }
            }

            return str;
        }

        static std::wstring ToUnicode(const std::string& text)
        {
            std::wstring str;

            if (!text.empty())
            {
                int chars = ::MultiByteToWideChar(CP_ACP, 0, text.c_str(), static_cast<int>(text.size()), nullptr, 0);
                if (chars == 0)
                {
                    return std::wstring();
                }

                str.resize(chars);
                chars = ::MultiByteToWideChar(CP_ACP, 0, text.c_str(), static_cast<int>(text.size()), &str[0], static_cast<int>(str.size()));
                if (chars == 0)
                {
                    return std::wstring();
                }
            }

            return str;
        }
    };

    class DeviceInfo : public SP_DEVINFO_DATA
    {
    public:
        DeviceInfo()
        {
            static_cast<SP_DEVINFO_DATA&>(*this) = { sizeof(SP_DEVINFO_DATA) };
        }

        DeviceInfo(const DeviceInfo&) = delete;
        DeviceInfo& operator=(const DeviceInfo& other) = delete;
        DeviceInfo(DeviceInfo&&) = delete;
        DeviceInfo& operator=(DeviceInfo&& other) = delete;

    public:
        HRESULT Open(HDEVINFO hDeviceInfoSet, LPCWSTR pszDeviceInstanceId, HWND hwndParent = nullptr, DWORD dwOpenFlags = 0)
        {
            if (!SetupDiOpenDeviceInfoW(hDeviceInfoSet, pszDeviceInstanceId, hwndParent, dwOpenFlags, this))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            return S_OK;
        }

        HRESULT GetProperty(HDEVINFO hDeviceInfoSet, const DEVPROPKEY* key, bool& value)
        {
            DEVPROP_BOOLEAN buffer{};
            DEVPROPTYPE type = DEVPROP_TYPE_EMPTY;
            DWORD dwRequiredSize = 0;
            if (!SetupDiGetDevicePropertyW(hDeviceInfoSet, this, key, &type, reinterpret_cast<PBYTE>(&buffer), sizeof(buffer), &dwRequiredSize, 0))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            if (type != DEVPROP_TYPE_BOOLEAN)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_DATATYPE);
            }

            value = buffer != DEVPROP_FALSE;
            return S_OK;
        }

        HRESULT GetProperty(HDEVINFO hDeviceInfoSet, const DEVPROPKEY* key, uint32_t& value)
        {
            uint32_t buffer{};
            DEVPROPTYPE type = DEVPROP_TYPE_EMPTY;
            DWORD dwRequiredSize = 0;
            if (!SetupDiGetDevicePropertyW(hDeviceInfoSet, this, key, &type, reinterpret_cast<PBYTE>(&buffer), sizeof(buffer), &dwRequiredSize, 0))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            if (type != DEVPROP_TYPE_UINT32)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_DATATYPE);
            }

            value = buffer;
            return S_OK;
        }

        HRESULT GetProperty(HDEVINFO hDeviceInfoSet, const DEVPROPKEY* key, GUID& value)
        {
            GUID buffer{};
            DEVPROPTYPE type = DEVPROP_TYPE_EMPTY;
            DWORD dwRequiredSize = 0;
            if (!SetupDiGetDevicePropertyW(hDeviceInfoSet, this, key, &type, reinterpret_cast<PBYTE>(&buffer), sizeof(buffer), &dwRequiredSize, 0))
            {
                DWORD dwError = GetLastError();
                if (dwError != ERROR_INSUFFICIENT_BUFFER)
                {
                    return HRESULT_FROM_WIN32(dwError);
                }
            }

            if (type != DEVPROP_TYPE_GUID)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_DATATYPE);
            }

            value = buffer;
            return S_OK;
        }

        HRESULT GetProperty(HDEVINFO hDeviceInfoSet, const DEVPROPKEY* key, std::wstring& value)
        {
            DEVPROPTYPE type = DEVPROP_TYPE_EMPTY;
            DWORD dwRequiredSize = 0;
            if (!SetupDiGetDevicePropertyW(hDeviceInfoSet, this, key, &type, nullptr, 0, &dwRequiredSize, 0))
            {
                DWORD dwError = GetLastError();
                if (dwError != ERROR_INSUFFICIENT_BUFFER)
                {
                    return HRESULT_FROM_WIN32(dwError);
                }
            }

            if (type != DEVPROP_TYPE_STRING)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_DATATYPE);
            }

            std::vector<uint8_t> buffer(dwRequiredSize);
            if (!SetupDiGetDevicePropertyW(hDeviceInfoSet, this, key, &type, buffer.data(), dwRequiredSize, nullptr, 0))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            LPCWSTR pszValue = reinterpret_cast<LPCWSTR>(buffer.data());
            DWORD dwChars = dwRequiredSize / sizeof(WCHAR);
            if (dwChars > 0 && pszValue[dwChars - 1] == 0)
            {
                dwChars--;
            }

            value = std::wstring(pszValue, dwChars);
            return S_OK;
        }

        HRESULT GetProperty(HDEVINFO hDeviceInfoSet, const DEVPROPKEY* key, std::vector<std::wstring>& values)
        {
            DEVPROPTYPE type = DEVPROP_TYPE_EMPTY;
            DWORD dwRequiredSize = 0;
            if (!SetupDiGetDevicePropertyW(hDeviceInfoSet, this, key, &type, nullptr, 0, &dwRequiredSize, 0))
            {
                DWORD dwError = GetLastError();
                if (dwError != ERROR_INSUFFICIENT_BUFFER)
                {
                    return HRESULT_FROM_WIN32(dwError);
                }
            }

            if (type != DEVPROP_TYPE_STRING_LIST)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_DATATYPE);
            }

            std::vector<uint8_t> buffer(dwRequiredSize);
            if (!SetupDiGetDevicePropertyW(hDeviceInfoSet, this, key, &type, buffer.data(), dwRequiredSize, nullptr, 0))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            auto data = reinterpret_cast<const wchar_t*>(buffer.data());
            while (*data != 0)
            {
                values.push_back(data);
                data += wcslen(data) + 1;
            }

            return S_OK;
        }
    };

    class DeviceInfoSet
    {
    public:
        DeviceInfoSet() = default;
        DeviceInfoSet(const DeviceInfoSet&) = delete;
        DeviceInfoSet& operator=(const DeviceInfoSet& other) = delete;
        DeviceInfoSet(DeviceInfoSet&&) = delete;
        DeviceInfoSet& operator=(DeviceInfoSet&& other) = delete;

        ~DeviceInfoSet()
        {
            Destroy();
        }

    public:
        operator HDEVINFO() const noexcept
        {
            return m_hDeviceInfoSet;
        }

    public:
        HRESULT Create(const GUID* classGuid, HWND hwndParent)
        {
            Destroy();

            HDEVINFO hDeviceInfoSet = SetupDiCreateDeviceInfoList(classGuid, hwndParent);
            if (hDeviceInfoSet == INVALID_HANDLE_VALUE)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            m_hDeviceInfoSet = hDeviceInfoSet;
            return S_OK;
        }

        HRESULT GetClassDevs(const GUID* classGuid, PCWSTR pszEnumerator, HWND hWndParent, DWORD dwFlags)
        {
            Destroy();

            HDEVINFO hDeviceInfoSet = SetupDiGetClassDevsW(classGuid, pszEnumerator, hWndParent, dwFlags);
            if (hDeviceInfoSet == INVALID_HANDLE_VALUE)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            m_hDeviceInfoSet = hDeviceInfoSet;
            return S_OK;
        }

        void Destroy()
        {
            if (m_hDeviceInfoSet != INVALID_HANDLE_VALUE)
            {
                SetupDiDestroyDeviceInfoList(m_hDeviceInfoSet);
                m_hDeviceInfoSet = INVALID_HANDLE_VALUE;
            }
        }

    private:
        HDEVINFO m_hDeviceInfoSet = INVALID_HANDLE_VALUE;
    };

    class UsbDriver
    {
    public:
        virtual ~UsbDriver()
        {
            Close();
        }

        UsbDriver() = default;
        UsbDriver(const UsbDriver&) = delete;
        UsbDriver& operator=(const UsbDriver& other) = delete;
        UsbDriver(UsbDriver&&) = delete;
        UsbDriver& operator=(UsbDriver&& other) = delete;

    public:
        virtual HRESULT Open(LPCWSTR pszPath)
        {
            Close();

            HANDLE hDevice = CreateFileW(
                pszPath,
                GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                nullptr,
                OPEN_EXISTING,
                FILE_FLAG_OVERLAPPED,
                nullptr);
            if (hDevice == INVALID_HANDLE_VALUE)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            m_hDevice.Attach(hDevice);
            return S_OK;
        }

        virtual void Close()
        {
            m_hDevice.Close();
        }

        virtual HRESULT GetDescriptor(uint8_t type, uint8_t index, uint16_t languageID, void* buffer, uint16_t bufferSize, uint32_t* bytesReturned, uint32_t timeout) = 0;
        virtual HRESULT ControlTransfer(uint8_t requesttype, uint8_t request, uint16_t value, uint16_t index, void* buffer, uint16_t bufferSize, uint32_t* bytesReturned, uint32_t timeout) = 0;
        virtual HRESULT SetConfiguration(uint8_t configuration) = 0;
        virtual HRESULT ClaimInterface(uint8_t interfaceIndex) = 0;
        virtual HRESULT ReleaseInterface(uint8_t interfaceIndex) = 0;
        virtual HRESULT SetAlternateSetting(uint8_t interfaceIndex, uint8_t alternate) = 0;
        virtual HRESULT ReadPipe(uint8_t pipeId, void* buffer, uint32_t bufferSize, uint32_t* bytesRead, uint32_t timeout) = 0;
        virtual HRESULT WritePipe(uint8_t pipeId, void* buffer, uint32_t bufferSize, uint32_t* bytesWritten, uint32_t timeout) = 0;

    protected:
        Handle m_hDevice;
    };

    class WinUsbDriver : public UsbDriver
    {
    public:
        HRESULT Open(LPCWSTR pszPath) override
        {
            HRESULT hr = UsbDriver::Open(pszPath);
            if (FAILED(hr))
            {
                return hr;
            }

            WINUSB_INTERFACE_HANDLE hWinUsbInterface = nullptr;
            if (!WinUsb_Initialize(m_hDevice, &hWinUsbInterface))
            {
                DWORD dwError = GetLastError();
                Close();
                return HRESULT_FROM_WIN32(dwError);
            }

            m_hWinUsbInterface = hWinUsbInterface;
            return S_OK;
        }

        void Close() override
        {
            if (m_hWinUsbInterface != nullptr)
            {
                WinUsb_Free(m_hWinUsbInterface);
                m_hWinUsbInterface = nullptr;
            }

            UsbDriver::Close();
        }

        HRESULT GetDescriptor(uint8_t type, uint8_t index, uint16_t languageID, void* buffer, uint16_t bufferSize, uint32_t* bytesReturned, uint32_t timeout) override
        {
            UNREFERENCED_PARAMETER(timeout);

            if (bytesReturned != nullptr)
            {
                *bytesReturned = 0;
            }

            ULONG bytesTransferred = 0;
            if (!WinUsb_GetDescriptor(m_hWinUsbInterface, type, index, languageID, static_cast<PUCHAR>(buffer), bufferSize, &bytesTransferred))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            if (bytesReturned != nullptr)
            {
                *bytesReturned = bytesTransferred;
            }

            return S_OK;
        }

        HRESULT ControlTransfer(uint8_t requesttype, uint8_t request, uint16_t value, uint16_t index, void* buffer, uint16_t bufferSize, uint32_t* bytesReturned, uint32_t timeout) override
        {
            UNREFERENCED_PARAMETER(timeout);

            if (bytesReturned != nullptr)
            {
                *bytesReturned = 0;
            }

            WINUSB_SETUP_PACKET packet{};
            packet.RequestType = requesttype;
            packet.Request = request;
            packet.Value = value;
            packet.Index = index;
            packet.Length = bufferSize;

            ULONG bytesTransferred = 0;
            if (!WinUsb_ControlTransfer(m_hWinUsbInterface, packet, static_cast<PUCHAR>(buffer), bufferSize, &bytesTransferred, nullptr))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            if (bytesReturned != nullptr)
            {
                *bytesReturned = bytesTransferred;
            }

            return S_OK;
        }

        HRESULT SetConfiguration(uint8_t configuration) override
        {
            // Not supported, fail silently.
            return S_FALSE;
        }

        HRESULT ClaimInterface(uint8_t interfaceIndex) override
        {
            m_associatedInterface.index = interfaceIndex;

            if (interfaceIndex > 0)
            {
                WINUSB_INTERFACE_HANDLE handle = nullptr;
                if (!WinUsb_GetAssociatedInterface(m_hWinUsbInterface, interfaceIndex, &handle))
                {
                    return HRESULT_FROM_WIN32(GetLastError());
                }

                m_associatedInterface.first = false;
                m_associatedInterface.handle = handle;
            }
            else
            {
                m_associatedInterface.first = true;
                m_associatedInterface.handle = m_hWinUsbInterface;
            }

            return S_OK;
        }

        HRESULT ReleaseInterface(uint8_t interfaceIndex) override
        {
            if (interfaceIndex != m_associatedInterface.index)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
            }

            if (m_associatedInterface.handle != nullptr && !m_associatedInterface.first)
            {
                WinUsb_Free(m_associatedInterface.handle);
                m_associatedInterface.handle = nullptr;
            }

            return S_OK;
        }

        HRESULT SetAlternateSetting(uint8_t interfaceIndex, uint8_t alternate) override
        {
            if (m_associatedInterface.handle == nullptr)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
            }

            return E_FAIL;
        }

        HRESULT ReadPipe(uint8_t pipeId, void* buffer, uint32_t bufferSize, uint32_t* bytesRead, uint32_t timeout) override
        {
            UNREFERENCED_PARAMETER(timeout);

            if (bytesRead != nullptr)
            {
                *bytesRead = 0;
            }

            if (m_associatedInterface.handle == nullptr)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
            }

            if (!WinUsb_SetPipePolicy(m_associatedInterface.handle, pipeId, PIPE_TRANSFER_TIMEOUT, sizeof(timeout), &timeout))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            ULONG lengthTransferred = 0;
            if (!WinUsb_ReadPipe(m_associatedInterface.handle, pipeId, static_cast<PUCHAR>(buffer), bufferSize, &lengthTransferred, nullptr))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            if (bytesRead != nullptr)
            {
                *bytesRead = lengthTransferred;
            }

            return S_OK;
        }

        HRESULT WritePipe(uint8_t pipeId, void* buffer, uint32_t bufferSize, uint32_t* bytesWritten, uint32_t timeout) override
        {
            UNREFERENCED_PARAMETER(timeout);

            if (bytesWritten != nullptr)
            {
                *bytesWritten = 0;
            }

            if (m_associatedInterface.handle == nullptr)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
            }

            if (!WinUsb_SetPipePolicy(m_associatedInterface.handle, pipeId, PIPE_TRANSFER_TIMEOUT, sizeof(timeout), &timeout))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            ULONG lengthTransferred = 0;
            if (!WinUsb_WritePipe(m_associatedInterface.handle, pipeId, static_cast<PUCHAR>(buffer), bufferSize, &lengthTransferred, nullptr))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            if (bytesWritten != nullptr)
            {
                *bytesWritten = lengthTransferred;
            }

            return S_OK;
        }

    private:
        struct Interface
        {
            WINUSB_INTERFACE_HANDLE handle = nullptr;
            uint8_t index = 0;
            bool first = false;
        };

        WINUSB_INTERFACE_HANDLE m_hWinUsbInterface = nullptr;
        Interface m_associatedInterface;
    };

    class LibUsbDriver : public UsbDriver
    {
    public:
        HRESULT Open(LPCWSTR pszPath) override
        {
            HRESULT hr = UsbDriver::Open(pszPath);
            if (FAILED(hr))
            {
                return hr;
            }

            hr = m_event.Create();
            if (FAILED(hr))
            {
                Close();
                return hr;
            }

            return S_OK;
        }

        void Close() override
        {
            m_event.Close();
            UsbDriver::Close();
        }

        HRESULT GetDescriptor(uint8_t type, uint8_t index, uint16_t languageID, void* buffer, uint16_t bufferSize, uint32_t* bytesReturned, uint32_t timeout) override
        {
            libusb_request data{};
            data.timeout = timeout;
            data.descriptor.type = type;
            data.descriptor.index = index;
            data.descriptor.language_id = languageID;
            data.descriptor.recipient = USB_RECIP_DEVICE;
            return DeviceIoControl(LIBUSB_IOCTL_GET_DESCRIPTOR, &data, sizeof(data), buffer, bufferSize, bytesReturned);
        }

        HRESULT ControlTransfer(uint8_t requesttype, uint8_t request, uint16_t value, uint16_t index, void* buffer, uint16_t bufferSize, uint32_t* bytesTransmitted, uint32_t timeout) override
        {
            libusb_request data{};
            data.timeout = timeout;

            uint32_t ioControlCode = 0;
            switch (requesttype & (0x03 << 5))
            {
            case USB_TYPE_STANDARD:
                switch (request)
                {
                case USB_REQ_GET_STATUS:
                    ioControlCode = LIBUSB_IOCTL_GET_STATUS;
                    data.status.recipient = requesttype & 0x1F;
                    data.status.index = index;
                    break;
                case USB_REQ_CLEAR_FEATURE:
                    ioControlCode = LIBUSB_IOCTL_CLEAR_FEATURE;
                    data.feature.recipient = requesttype & 0x1F;
                    data.feature.feature = value;
                    data.feature.index = index;
                    break;
                case USB_REQ_SET_FEATURE:
                    ioControlCode = LIBUSB_IOCTL_SET_FEATURE;
                    data.feature.recipient = requesttype & 0x1F;
                    data.feature.feature = value;
                    data.feature.index = index;
                    break;
                case USB_REQ_GET_DESCRIPTOR:
                    ioControlCode = LIBUSB_IOCTL_GET_DESCRIPTOR;
                    data.descriptor.recipient = requesttype & 0x1F;
                    data.descriptor.type = (value >> 8) & 0xFF;
                    data.descriptor.index = value & 0xFF;
                    data.descriptor.language_id = index;
                    break;
                case USB_REQ_SET_DESCRIPTOR:
                    ioControlCode = LIBUSB_IOCTL_SET_DESCRIPTOR;
                    data.descriptor.recipient = requesttype & 0x1F;
                    data.descriptor.type = (value >> 8) & 0xFF;
                    data.descriptor.index = value & 0xFF;
                    data.descriptor.language_id = index;
                    break;
                case USB_REQ_GET_CONFIGURATION:
                    ioControlCode = LIBUSB_IOCTL_GET_CONFIGURATION;
                    break;
                case USB_REQ_SET_CONFIGURATION:
                    data.configuration.configuration = value;
                    ioControlCode = LIBUSB_IOCTL_SET_CONFIGURATION;
                    break;
                case USB_REQ_GET_INTERFACE:
                    ioControlCode = LIBUSB_IOCTL_GET_INTERFACE;
                    data.intf.interface_number = index;
                    break;
                case USB_REQ_SET_INTERFACE:
                    ioControlCode = LIBUSB_IOCTL_SET_INTERFACE;
                    data.intf.interface_number = index;
                    data.intf.altsetting_number = value;
                    break;
                default:
                    return E_INVALIDARG;
                }
                break;
            case USB_TYPE_CLASS:
            case USB_TYPE_VENDOR:
                ioControlCode = (requesttype & 0x80) != 0 ? LIBUSB_IOCTL_VENDOR_READ : LIBUSB_IOCTL_VENDOR_WRITE;
                data.vendor.type = (requesttype >> 5) & 0x03;
                data.vendor.recipient = requesttype & 0x1F;
                data.vendor.request = request;
                data.vendor.value = value;
                data.vendor.index = index;
                break;
            default:
                return E_INVALIDARG;
            }

            if ((requesttype & USB_ENDPOINT_IN) == 0)
            {
                if (bytesTransmitted != nullptr)
                {
                    *bytesTransmitted = 0;
                }

                if (bufferSize > 0)
                {
                    std::vector<uint8_t> out(sizeof(data) + bufferSize);
                    std::memcpy(out.data(), &data, sizeof(data));
                    std::memcpy(out.data() + sizeof(data), buffer, bufferSize);
                    HRESULT hr = DeviceIoControl(ioControlCode, out.data(), sizeof(data) + bufferSize, nullptr, 0);
                    if (FAILED(hr))
                        return hr;

                    if (bytesTransmitted != nullptr)
                    {
                        *bytesTransmitted = bufferSize;
                    }

                    return hr;
                }
                else
                {
                    return DeviceIoControl(ioControlCode, &data, sizeof(data), nullptr, 0);
                }
            }
            else
            {
                return DeviceIoControl(ioControlCode, &data, sizeof(data), buffer, bufferSize, bytesTransmitted);
            }
        }

        HRESULT SetConfiguration(uint8_t configuration) override
        {
            libusb_request data{};
            data.configuration.configuration = configuration;
            data.timeout = LIBUSB_DEFAULT_TIMEOUT;
            return DeviceIoControl(LIBUSB_IOCTL_SET_CONFIGURATION, &data, sizeof(data), nullptr, 0);
        }

        HRESULT ClaimInterface(uint8_t interfaceIndex) override
        {
            libusb_request data{};
            data.intf.interface_number = interfaceIndex;
            data.timeout = LIBUSB_DEFAULT_TIMEOUT;
            return DeviceIoControl(LIBUSB_IOCTL_CLAIM_INTERFACE, &data, sizeof(data), nullptr, 0);
        }

        HRESULT ReleaseInterface(uint8_t interfaceIndex) override
        {
            libusb_request data{};
            data.intf.interface_number = interfaceIndex;
            data.timeout = LIBUSB_DEFAULT_TIMEOUT;
            return DeviceIoControl(LIBUSB_IOCTL_RELEASE_INTERFACE, &data, sizeof(data), nullptr, 0);
        }

        HRESULT SetAlternateSetting(uint8_t interfaceIndex, uint8_t alternate) override
        {
            libusb_request data{};
            data.intf.interface_number = interfaceIndex;
            data.intf.altsetting_number = alternate;
            data.timeout = LIBUSB_DEFAULT_TIMEOUT;
            return DeviceIoControl(LIBUSB_IOCTL_SET_INTERFACE, &data, sizeof(data), nullptr, 0);
        }

        HRESULT ReadPipe(uint8_t pipeId, void* buffer, uint32_t bufferSize, uint32_t* bytesRead, uint32_t timeout) override
        {
            return DeviceIoTransfer(LIBUSB_IOCTL_INTERRUPT_OR_BULK_READ, pipeId, buffer, bufferSize, bytesRead, timeout);
        }

        HRESULT WritePipe(uint8_t pipeId, void* buffer, uint32_t bufferSize, uint32_t* bytesWritten, uint32_t timeout) override
        {
            return DeviceIoTransfer(LIBUSB_IOCTL_INTERRUPT_OR_BULK_WRITE, pipeId, buffer, bufferSize, bytesWritten, timeout);
        }

    private:
        static const uint32_t LIBUSB_DEFAULT_TIMEOUT = 5000;

        static const uint32_t LIBUSB_IOCTL_SET_CONFIGURATION = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_GET_CONFIGURATION = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_SET_INTERFACE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_GET_INTERFACE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_SET_FEATURE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_CLEAR_FEATURE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x806, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_GET_STATUS = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x807, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_SET_DESCRIPTOR = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x808, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_GET_DESCRIPTOR = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x809, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_INTERRUPT_OR_BULK_WRITE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80A, METHOD_IN_DIRECT, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_INTERRUPT_OR_BULK_READ = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80B, METHOD_OUT_DIRECT, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_VENDOR_WRITE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80C, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_VENDOR_READ = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80D, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_RESET_ENDPOINT = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80E, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_ABORT_ENDPOINT = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80F, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_RESET_DEVICE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x810, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_SET_DEBUG_LEVEL = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x811, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_GET_VERSION = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x812, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_ISOCHRONOUS_WRITE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x813, METHOD_IN_DIRECT, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_ISOCHRONOUS_READ = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x814, METHOD_OUT_DIRECT, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_CLAIM_INTERFACE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x815, METHOD_BUFFERED, FILE_ANY_ACCESS);
        static const uint32_t LIBUSB_IOCTL_RELEASE_INTERFACE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x816, METHOD_BUFFERED, FILE_ANY_ACCESS);

#include <pshpack1.h>

        struct interface_request
        {
            uint32_t interface_number;
            uint32_t altsetting_number;
            uint8_t intf_use_index : 1;
            uint8_t altf_use_index : 1;
            uint8_t : 6;
            int16_t interface_index;
            int16_t altsetting_index;
        };

        struct libusb_request
        {
            uint32_t timeout;
            union
            {
                struct
                {
                    uint32_t configuration;
                } configuration;
                interface_request intf;
                struct
                {
                    uint32_t endpoint;
                    uint32_t packet_size;
                    uint32_t max_transfer_size;
                    uint32_t transfer_flags;
                    uint32_t iso_start_frame_latency;
                } endpoint;
                struct
                {
                    uint32_t type;
                    uint32_t recipient;
                    uint32_t request;
                    uint32_t value;
                    uint32_t index;
                } vendor;
                struct
                {
                    uint32_t recipient;
                    uint32_t feature;
                    uint32_t index;
                } feature;
                struct
                {
                    uint32_t recipient;
                    uint32_t index;
                    uint32_t status;
                } status;
                struct
                {
                    uint32_t type;
                    uint32_t index;
                    uint32_t language_id;
                    uint32_t recipient;
                } descriptor;
                struct
                {
                    uint32_t level;
                } debug;
                struct
                {
                    uint32_t major;
                    uint32_t minor;
                    uint32_t micro;
                    uint32_t nano;
                    uint32_t mod_value;
                } version;
                struct
                {
                    uint32_t property;
                } device_property;
                struct
                {
                    uint32_t key_type;
                    uint32_t name_offset;
                    uint32_t value_offset;
                    uint32_t value_length;
                } device_registry_key;
                struct
                {
                    uint32_t objname_index;
                } objname;
                struct
                {
                    uint32_t information_type;
                } query_device;
                struct
                {
                    uint32_t interface_index;
                    uint32_t pipe_id;
                    uint32_t policy_type;
                } pipe_policy;
                struct
                {
                    uint32_t policy_type;
                } power_policy;
                struct
                {
                    uint32_t reset_type;
                } reset_ex;
                struct
                {
                    uint8_t request_type;
                    uint8_t request;
                    uint16_t value;
                    uint16_t index;
                    uint16_t length;
                } control;
            };
        };

#include <poppack.h>

    private:
        static const uint32_t maxReadWriteSize = 0x10000;

        HRESULT DeviceIoTransfer(uint32_t ioControlCode, uint8_t pipeId, void* buffer, uint32_t bufferSize, uint32_t* bytesTransferred, uint32_t timeout)
        {
            if (bytesTransferred != nullptr)
            {
                *bytesTransferred = 0;
            }

            if (timeout == 0)
            {
                timeout = INFINITE;
            }

            ManualResetEvent event;
            HRESULT hr = event.Create();
            if (FAILED(hr))
            {
                return hr;
            }

            uint32_t transferred = 0;
            while (bufferSize > 0)
            {
                uint32_t chunkSize = bufferSize > maxReadWriteSize ? maxReadWriteSize : bufferSize;

                libusb_request transfer{};
                transfer.endpoint.endpoint = pipeId;
                transfer.endpoint.packet_size = 0;

                event.Reset();

                OVERLAPPED overlapped{};
                overlapped.hEvent = event;
                hr = DeviceIoControl(ioControlCode, &transfer, sizeof(transfer), buffer, chunkSize, nullptr, &overlapped);
                if (FAILED(hr))
                {
                    return hr;
                }

                if (WaitForSingleObject(overlapped.hEvent, timeout) != WAIT_OBJECT_0)
                {
                    libusb_request cancel{};
                    cancel.endpoint.endpoint = pipeId;
                    cancel.timeout = LIBUSB_DEFAULT_TIMEOUT;
                    DeviceIoControl(LIBUSB_IOCTL_ABORT_ENDPOINT, &cancel, sizeof(cancel), nullptr, 0);
                    return HRESULT_FROM_WIN32(ERROR_TIMEOUT);
                }

                DWORD dwNumberOfBytesTransferred = 0;
                if (!GetOverlappedResult(m_hDevice, &overlapped, &dwNumberOfBytesTransferred, TRUE))
                {
                    return HRESULT_FROM_WIN32(GetLastError());
                }

                transferred += dwNumberOfBytesTransferred;
                if (dwNumberOfBytesTransferred != chunkSize)
                {
                    break;
                }

                buffer = static_cast<uint8_t*>(buffer) + dwNumberOfBytesTransferred;
                bufferSize -= dwNumberOfBytesTransferred;
            }

            if (bytesTransferred != nullptr)
            {
                *bytesTransferred = transferred;
            }

            return S_OK;
        }

        HRESULT DeviceIoControl(
            uint32_t ioControlCode,
            void* lpInBuffer,
            uint32_t inBufferSize,
            void* pOutBuffer,
            uint32_t outBufferSize,
            uint32_t* bytesReturned = nullptr,
            LPOVERLAPPED pOverlapped = nullptr)
        {
            if (bytesReturned != nullptr)
            {
                *bytesReturned = 0;
            }

            if (pOverlapped == nullptr)
            {
                m_event.Reset();

                OVERLAPPED overlapped{};
                overlapped.hEvent = m_event;
                if (!::DeviceIoControl(m_hDevice, ioControlCode, lpInBuffer, inBufferSize, pOutBuffer, outBufferSize, nullptr, &overlapped))
                {
                    DWORD dwError = GetLastError();
                    if (dwError != ERROR_IO_PENDING)
                    {
                        return HRESULT_FROM_WIN32(dwError);
                    }
                }

                DWORD dwNumberOfBytesTransferred = 0;
                if (!::GetOverlappedResult(m_hDevice, &overlapped, &dwNumberOfBytesTransferred, TRUE))
                {
                    return HRESULT_FROM_WIN32(GetLastError());
                }

                if (bytesReturned != nullptr)
                {
                    *bytesReturned = dwNumberOfBytesTransferred;
                }
            }
            else
            {
                DWORD dwBytesReturned = 0;
                if (!::DeviceIoControl(m_hDevice, ioControlCode, lpInBuffer, inBufferSize, pOutBuffer, outBufferSize, &dwBytesReturned, pOverlapped))
                {
                    DWORD dwError = GetLastError();
                    if (dwError != ERROR_IO_PENDING)
                    {
                        return HRESULT_FROM_WIN32(dwError);
                    }
                }

                if (bytesReturned != nullptr)
                {
                    *bytesReturned = dwBytesReturned;
                }
            }

            return S_OK;
        }

    private:
        ManualResetEvent m_event;
    };

    class UsbDevice
    {
        friend class UsbDeviceEnumerator;

    public:
        UsbDevice() = default;
        UsbDevice(const UsbDevice&) = delete;
        UsbDevice& operator=(const UsbDevice& other) = delete;
        UsbDevice(UsbDevice&&) = delete;
        UsbDevice& operator=(UsbDevice&& other) = delete;

    public:
        std::wstring GetInstanceId() const { return m_instanceId; }
        std::wstring GetInterfacePath() const { return m_interfacePath; }
        std::wstring GetService() const { return m_service; }

    public:
        HRESULT Open(std::unique_ptr<UsbDriver>& driver)
        {
            return Open(m_service, m_interfacePath, driver);
        }

        static HRESULT Open(const std::wstring& service, const std::wstring& interfacePath, std::unique_ptr<UsbDriver>& driver)
        {
            if (_wcsicmp(service.c_str(), L"WINUSB") == 0)
            {
                driver = std::make_unique<WinUsbDriver>();
            }
            else if (_wcsicmp(service.c_str(), L"libusb0") == 0 || _wcsicmp(service.c_str(), L"libusbK") == 0)
            {
                driver = std::make_unique<LibUsbDriver>();
            }
            else
            {
                return E_NOTIMPL;
            }

            return driver->Open(interfacePath.c_str());
        }

    private:
        std::wstring m_instanceId;
        std::wstring m_interfacePath;
        std::wstring m_service;
    };

    class UsbDeviceEnumerator
    {
    public:
        UsbDeviceEnumerator() = default;
        UsbDeviceEnumerator(const UsbDeviceEnumerator&) = delete;
        UsbDeviceEnumerator& operator=(const UsbDeviceEnumerator& other) = delete;
        UsbDeviceEnumerator(UsbDeviceEnumerator&&) = delete;
        UsbDeviceEnumerator& operator=(UsbDeviceEnumerator&& other) = delete;

    public:
        std::vector<std::unique_ptr<UsbDevice>>& GetDevices() { return m_devices; }

    public:
        HRESULT EnumerateDevices()
        {
            DeviceInfoSet deviceInfoSet;
            HRESULT hr = deviceInfoSet.GetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, nullptr, nullptr, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
            if (FAILED(hr))
                return hr;

            for (DWORD index = 0; ; index++)
            {
                DeviceInfo deviceInfo;
                if (!SetupDiEnumDeviceInfo(deviceInfoSet, index, &deviceInfo))
                {
                    DWORD dwError = GetLastError();
                    if (dwError != ERROR_NO_MORE_ITEMS)
                    {
                        return HRESULT_FROM_WIN32(dwError);
                    }

                    break;
                }

                SP_DEVICE_INTERFACE_DATA deviceInterface = { sizeof(SP_DEVICE_INTERFACE_DATA) };
                if (!SetupDiEnumDeviceInterfaces(deviceInfoSet, &deviceInfo, &GUID_DEVINTERFACE_USB_DEVICE, 0, &deviceInterface))
                {
                    DWORD dwError = GetLastError();
                    if (dwError != ERROR_NO_MORE_ITEMS)
                    {
                        return HRESULT_FROM_WIN32(dwError);
                    }
                }
                else
                {
                    auto device = std::make_unique<UsbDevice>();

                    uint32_t installState = 0;
                    if (SUCCEEDED(deviceInfo.GetProperty(deviceInfoSet, &DEVPKEY_Device_InstanceId, device->m_instanceId)) &&
                        SUCCEEDED(deviceInfo.GetProperty(deviceInfoSet, &DEVPKEY_Device_InstallState, installState)) &&
                        SUCCEEDED(deviceInfo.GetProperty(deviceInfoSet, &DEVPKEY_Device_Service, device->m_service)) &&
                        SUCCEEDED(GetDeviceInterfacePath(deviceInfoSet, &deviceInterface, device->m_interfacePath)) &&
                        installState == 0)
                    {
                        m_devices.push_back(std::move(device));
                    }
                }
            }

            return S_OK;
        }

        HRESULT GetDeviceInterfacePath(HDEVINFO hDeviceInfoSet, PSP_DEVICE_INTERFACE_DATA pDeviceInterfaceData, std::wstring& deviceInterfacePath)
        {
            DWORD dwRequiredSize = 0;
            if (!SetupDiGetDeviceInterfaceDetailW(hDeviceInfoSet, pDeviceInterfaceData, nullptr, 0, &dwRequiredSize, nullptr))
            {
                DWORD dwError = GetLastError();
                if (dwError != ERROR_INSUFFICIENT_BUFFER)
                {
                    return HRESULT_FROM_WIN32(dwError);
                }
            }

            std::vector<uint8_t> buffer(dwRequiredSize);
            SP_DEVICE_INTERFACE_DETAIL_DATA_W* pDeviceInterfaceDetailData = reinterpret_cast<SP_DEVICE_INTERFACE_DETAIL_DATA_W*>(buffer.data());
            pDeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);

            if (!SetupDiGetDeviceInterfaceDetailW(hDeviceInfoSet, pDeviceInterfaceData, pDeviceInterfaceDetailData, dwRequiredSize, &dwRequiredSize, nullptr))
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            deviceInterfacePath = pDeviceInterfaceDetailData->DevicePath;
            return S_OK;
        }

    private:
        std::vector<std::unique_ptr<UsbDevice>> m_devices;
    };
}
