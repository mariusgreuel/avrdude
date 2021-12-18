//
// usb_com_locator.h
// Copyright (C) 2019 Marius Greuel. All rights reserved.
//

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <initguid.h>
#include <devpkey.h>
#include <setupapi.h>
#include <winioctl.h>
#include <cassert>
#include <cstdarg>
#include <cwchar>
#include <cwctype>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma comment(lib, "setupapi.lib")

namespace UsbComLocator
{
    enum class MessageLevel
    {
        Error,
        Info,
        Verbose,
        Debug,
    };

    struct IConsole
    {
        virtual void WriteLine(MessageLevel level, const std::string& message) = 0;
    };

    class Win32
    {
    public:
        static std::wstring CreateMessageFromHResult(long hr)
        {
            std::wstring message;

            LPWSTR pszMessage = nullptr;
            DWORD dwChars = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, hr, 0, (LPWSTR)&pszMessage, 0, nullptr);
            if (dwChars > 0 && pszMessage != nullptr)
            {
                if (dwChars > 0 && pszMessage[dwChars - 1] == '\n')
                    dwChars--;

                if (dwChars > 0 && pszMessage[dwChars - 1] == '\r')
                    dwChars--;

                message = std::wstring(pszMessage, dwChars);

                LocalFree(pszMessage);
            }

            return message;
        }

    };

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

        Handle& operator=(HANDLE handle)
        {
            Close();
            m_handle = handle;
            return *this;
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

    class RegistryKey
    {
    public:
        RegistryKey() = default;

        RegistryKey(HKEY hKey) : m_hKey(hKey)
        {
        }

        ~RegistryKey()
        {
            Close();
        }

        RegistryKey(const RegistryKey&) = delete;
        RegistryKey& operator=(const RegistryKey& other) = delete;
        RegistryKey(RegistryKey&&) = default;
        RegistryKey& operator=(RegistryKey&& other) = default;

        operator HKEY() const noexcept
        {
            return m_hKey;
        }

        void Close() noexcept
        {
            if (m_hKey != nullptr)
            {
                RegCloseKey(m_hKey);
                m_hKey = nullptr;
            }
        }

        void Attach(HKEY handle) noexcept
        {
            assert(m_hKey == nullptr);
            m_hKey = handle;
        }

        HKEY Detach() noexcept
        {
            HKEY handle = m_hKey;
            m_hKey = nullptr;
            return handle;
        }

        HRESULT QueryValue(LPCWSTR pszValueName, std::wstring& value) noexcept
        {
            DWORD dwType = 0;
            DWORD dwRequiredSize = 0;
            LSTATUS nError = RegQueryValueExW(m_hKey, pszValueName, nullptr, &dwType, nullptr, &dwRequiredSize);
            if (nError != ERROR_SUCCESS)
            {
                return HRESULT_FROM_WIN32(nError);
            }

            if (dwType != REG_SZ && dwType != REG_EXPAND_SZ)
            {
                return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
            }

            std::vector<uint8_t> buffer(dwRequiredSize);
            nError = RegQueryValueExW(m_hKey, pszValueName, nullptr, &dwType, buffer.data(), &dwRequiredSize);
            if (nError != ERROR_SUCCESS)
            {
                return HRESULT_FROM_WIN32(nError);
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

    protected:
        HKEY m_hKey = nullptr;
    };

    class DeviceInfo : public SP_DEVINFO_DATA
    {
    public:
        DeviceInfo()
        {
            (SP_DEVINFO_DATA&)(*this) = { sizeof(SP_DEVINFO_DATA) };
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

        HRESULT GetRegistryValue(HDEVINFO hDeviceInfoSet, LPCWSTR pszValueName, std::wstring& value)
        {
            HKEY hKey = SetupDiOpenDevRegKey(hDeviceInfoSet, this, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
            if (hKey == INVALID_HANDLE_VALUE)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            RegistryKey key(hKey);
            return key.QueryValue(pszValueName, value);
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

    class Device
    {
    public:
        Device() = default;
        Device(const Device&) = delete;
        Device& operator=(const Device& other) = delete;
        Device(Device&&) = delete;
        Device& operator=(Device&& other) = delete;

    public:
        bool IsBootloaderMode() const
        {
            return !m_isCompositeDevice;
        }

        HRESULT Open(
            DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE,
            DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
            LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr)
        {
            HANDLE hDevice = CreateFileW(
                (L"\\\\.\\" + m_port).c_str(),
                dwDesiredAccess,
                0,
                lpSecurityAttributes,
                OPEN_EXISTING,
                dwFlagsAndAttributes,
                nullptr);
            if (hDevice == INVALID_HANDLE_VALUE)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            m_hDevice = hDevice;
            return S_OK;
        }

        void Close()
        {
            m_hDevice.Close();
        }

        HRESULT WaitForPortAvailability(uint32_t retries = 100, uint32_t timeout = 10)
        {
            while (true)
            {
                HRESULT hr = Open();
                if (SUCCEEDED(hr))
                {
                    Close();
                    return S_OK;
                }

                if (retries == 0)
                {
                    return hr;
                }

                Sleep(timeout);
                retries--;
            }
        }

        HRESULT Reset()
        {
            HRESULT hr = Open();
            if (FAILED(hr))
            {
                return hr;
            }

            EscapeCommFunction(m_hDevice, CLRDTR);

            DCB dcb = { sizeof(DCB) };
            dcb.BaudRate = CBR_1200;
            dcb.fDtrControl = DTR_CONTROL_DISABLE;
            dcb.fRtsControl = RTS_CONTROL_DISABLE;
            dcb.ByteSize = 8;
            dcb.Parity = NOPARITY;
            dcb.StopBits = ONESTOPBIT;
            SetCommState(m_hDevice, &dcb);

            Close();
            return S_OK;
        }

    public:
        std::wstring m_instanceId;
        std::wstring m_port;
        std::wstring m_location;
        std::wstring m_productName;
        bool m_isPresent = false;
        bool m_isCompositeDevice = false;
        uint16_t m_vid = 0;
        uint16_t m_pid = 0;
        Handle m_hDevice;
    };

    class Enumerator
    {
    public:
        Enumerator() = default;
        Enumerator(const Enumerator&) = delete;
        Enumerator& operator=(const Enumerator& other) = delete;
        Enumerator(Enumerator&&) = delete;
        Enumerator& operator=(Enumerator&& other) = delete;

    public:
        std::vector<std::shared_ptr<Device>>& GetDevices() { return m_devices; }

    public:
        HRESULT EnumerateDevices(bool includeUnpluggedDevices = false)
        {
            m_devices.clear();

            DeviceInfoSet deviceInfoSet;
            HRESULT hr = deviceInfoSet.GetClassDevs(&GUID_DEVINTERFACE_COMPORT, nullptr, nullptr, (includeUnpluggedDevices ? 0 : DIGCF_PRESENT) | DIGCF_DEVICEINTERFACE);
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

                auto device = std::make_shared<Device>();
                if (SUCCEEDED(deviceInfo.GetProperty(deviceInfoSet, &DEVPKEY_Device_InstanceId, device->m_instanceId)))
                {
                    ParseVidPid(device->m_instanceId.c_str(), L"VID_", device->m_vid);
                    ParseVidPid(device->m_instanceId.c_str(), L"PID_", device->m_pid);

                    deviceInfo.GetProperty(deviceInfoSet, &DEVPKEY_Device_IsPresent, device->m_isPresent);
                    deviceInfo.GetProperty(deviceInfoSet, &DEVPKEY_Device_BusReportedDeviceDesc, device->m_productName);
                    deviceInfo.GetRegistryValue(deviceInfoSet, L"PortName", device->m_port);

                    device->m_isCompositeDevice = IsCompositeDevice(device->m_instanceId.c_str());
                    if (device->m_isCompositeDevice)
                    {
                        GetCompositeDevicePortLocation(deviceInfoSet, deviceInfo, device->m_location);
                    }
                    else
                    {
                        deviceInfo.GetProperty(deviceInfoSet, &DEVPKEY_Device_LocationInfo, device->m_location);
                    }

                    m_devices.push_back(std::move(device));
                }
            }

            return S_OK;
        }

        bool ParseVidPid(_In_z_ wchar_t const* buffer, wchar_t const* prefix, uint16_t& value)
        {
            wchar_t const* match = wcsstr(buffer, prefix);
            if (match == nullptr)
            {
                return false;
            }

            match += wcslen(prefix);

            wchar_t* endptr = nullptr;
            value = static_cast<uint16_t>(std::wcstoul(match, &endptr, 16));
            return endptr == match + 4;
        }

    private:
        HRESULT GetCompositeDevicePortLocation(HDEVINFO hDeviceInfoSet, DeviceInfo& deviceInfo, std::wstring& location)
        {
            DeviceInfoSet deviceInfoSet;
            HRESULT hr = deviceInfoSet.Create(nullptr, nullptr);
            if (FAILED(hr))
            {
                return hr;
            }

            std::wstring parentDeviceInstanceId;
            hr = deviceInfo.GetProperty(hDeviceInfoSet, &DEVPKEY_Device_Parent, parentDeviceInstanceId);
            if (FAILED(hr))
            {
                return hr;
            }

            DeviceInfo parentDeviceInfo;
            hr = parentDeviceInfo.Open(deviceInfoSet, parentDeviceInstanceId.c_str());
            if (FAILED(hr))
            {
                return hr;
            }

            hr = parentDeviceInfo.GetProperty(deviceInfoSet, &DEVPKEY_Device_LocationInfo, location);
            if (FAILED(hr))
            {
                return hr;
            }

            return S_OK;
        }

        static bool IsCompositeDevice(LPCWSTR deviceInstanceId)
        {
            return wcsstr(deviceInstanceId, L"&MI_") != nullptr;
        }

    private:
        std::vector<std::shared_ptr<Device>> m_devices;
    };

    class Locator
    {
    public:
        struct Options
        {
            bool WaitForDevice = true;
            bool FindRelatedDevices = true;
            bool AutoReset = true;
            uint32_t Retries = 0xFFFFFFFF;
            uint32_t RetryIntervall = 100;
        };

    public:
        Locator(IConsole* console = nullptr) : m_console(console)
        {
        }

        Locator(const Locator&) = delete;
        Locator& operator=(const Locator& other) = delete;
        Locator(Locator&&) = delete;
        Locator& operator=(Locator&& other) = delete;

    public:
        std::string FindPortForDevice(const std::string& deviceId, const Options* options = nullptr)
        {
            auto device = FindDevice(Encoding::ToUnicode(deviceId), options);
            if (device == nullptr)
                return std::string();

            return Encoding::ToAnsi(device->m_port);
        }

        std::wstring FindPortForDevice(const std::wstring& deviceId, const Options* options = nullptr)
        {
            auto device = FindDevice(deviceId, options);
            if (device == nullptr)
                return std::wstring();

            return device->m_port;
        }

        std::shared_ptr<Device> FindDevice(const std::string& deviceId, const Options* options = nullptr)
        {
            return FindDevice(Encoding::ToUnicode(deviceId), options);
        }

        std::shared_ptr<Device> FindDevice(const std::wstring& deviceId, const Options* options = nullptr)
        {
            if (options == nullptr)
            {
                static Options defaults;
                options = &defaults;
            }

            uint32_t retries = options->Retries;
            while (true)
            {
                m_enumerator.EnumerateDevices(true);

                auto devices = FindDevices(deviceId, options->FindRelatedDevices);
                if (devices.size() == 0)
                {
                    throw std::runtime_error("Device not found.");
                }

                auto device = devices[0];
                if (device->m_isPresent)
                {
                    PrintMessage(MessageLevel::Verbose, "Found device at port '%ws'", device->m_port.c_str());
                    PrintDeviceProperties(device);

                    HRESULT hr = device->WaitForPortAvailability(options->Retries, options->RetryIntervall);
                    if (FAILED(hr))
                    {
                        PrintMessage(MessageLevel::Error, "Failed to open serial port: %ws", Win32::CreateMessageFromHResult(hr).c_str());
                        throw std::runtime_error("Failed to open serial port.");
                    }

                    if (device->IsBootloaderMode() || !options->AutoReset)
                    {
                        return device;
                    }

                    PrintMessage(MessageLevel::Info, "Entering bootloader mode...");
                    hr = device->Reset();
                    if (FAILED(hr))
                    {
                        PrintMessage(MessageLevel::Error, "Failed to reset device: %ws", Win32::CreateMessageFromHResult(hr).c_str());
                        throw std::runtime_error("Failed to reset device.");
                    }

                    retries = options->Retries;

                    while (true)
                    {
                        m_enumerator.EnumerateDevices(true);
                        auto relatedDevices = FindRelatedDevices(devices);
                        if (relatedDevices.size() > 0)
                        {
                            auto relatedDevice = relatedDevices[0];
                            if (relatedDevice->m_isPresent)
                            {
                                PrintMessage(MessageLevel::Verbose, "Found device at port '%ws'", relatedDevice->m_port.c_str());
                                PrintDeviceProperties(relatedDevice);

                                hr = relatedDevice->WaitForPortAvailability(options->Retries, options->RetryIntervall);
                                if (FAILED(hr))
                                {
                                    PrintMessage(MessageLevel::Error, "Failed to open serial port: %ws", Win32::CreateMessageFromHResult(hr).c_str());
                                    throw std::runtime_error("Failed to open serial port.");
                                }

                                return relatedDevice;
                            }
                        }

                        if (!options->WaitForDevice || retries == 0)
                        {
                            return nullptr;
                        }

                        Sleep(options->RetryIntervall);
                        retries--;
                    }
                }
                
                if (!options->WaitForDevice || retries == 0)
                {
                    return nullptr;
                }

                if (retries == options->Retries)
                {
                    PrintMessage(MessageLevel::Info, "No device present, retrying every %ums...", options->RetryIntervall);
                }
                
                Sleep(options->RetryIntervall);
                retries--;
            }
        }

        void LocateAllDevices()
        {
            PrintMessage(MessageLevel::Verbose, "Enumerating devices...");
            m_enumerator.EnumerateDevices(true);

            for (auto& device : m_enumerator.GetDevices())
            {
                PrintMessage(MessageLevel::Info, "Found device: %ws", device->m_instanceId.c_str());
                PrintDeviceProperties(device);
            }
        }

    private:
        std::vector<std::shared_ptr<Device>> FindDevices(const std::wstring& deviceId, bool findRelatedDevices = false)
        {
            uint32_t comPort = 0;
            uint16_t vid = 0;
            uint16_t pid = 0;
            if (swscanf_s(ToUpper(deviceId).c_str(), L"COM%u", &comPort) == 1)
            {
                auto devices = FindDevicesByPort(deviceId);
                if (devices.size() > 0)
                {
                    // 1) Return plugged-in devices with exact COM port match.
                    return devices;
                }

                auto unpluggedDevices = FindDevicesByPort(deviceId, true);

                if (findRelatedDevices)
                {
                    auto relatedDevices = FindRelatedDevices(unpluggedDevices);
                    if (relatedDevices.size() > 0)
                    {
                        // 2) Return plugged-in devices related to the COM port.
                        return relatedDevices;
                    }
                }

                // 3) Return unplugged devices with exact COM port match.
                return unpluggedDevices;
            }
            else if (swscanf_s(ToUpper(deviceId).c_str(), L"USB:%hX:%hX", &vid, &pid) == 2)
            {
                auto devices = FindDevicesByUsbId(vid, pid);
                if (devices.size() > 0)
                {
                    // 1) Return plugged-in devices with exact USB VID:PID match.
                    return devices;
                }

                auto unpluggedDevices = FindDevicesByUsbId(vid, pid, std::wstring(), true);

                if (findRelatedDevices)
                {
                    // 2) Return plugged-in devices with related USB VID:PID and HUB location.
                    auto relatedDevices = FindRelatedDevices(unpluggedDevices);
                    if (relatedDevices.size() > 0)
                    {
                        return relatedDevices;
                    }

                    // 3) Return plugged-in devices with related USB VID:PID (bootloader device never plugged-in).
                    relatedDevices = FindRelatedDevices(vid, pid);
                    if (relatedDevices.size() > 0)
                    {
                        return relatedDevices;
                    }
                }

                // 4) Return unplugged devices with exact USB VID:PID match.
                return unpluggedDevices;
            }
            else
            {
                throw std::runtime_error("Invalid device specifier.");
            }
        }

        std::vector<std::shared_ptr<Device>> FindDevicesByPort(const std::wstring& port, bool includeUnpluggedDevices = false)
        {
            std::vector<std::shared_ptr<Device>> devices;

            for (auto& device : m_enumerator.GetDevices())
            {
                if ((device->m_isPresent || includeUnpluggedDevices) &&
                    _wcsicmp(device->m_port.c_str(), port.c_str()) == 0)
                {
                    devices.push_back(device);
                }
            }

            return devices;
        }

        std::vector<std::shared_ptr<Device>> FindDevicesByUsbId(uint16_t vid, uint16_t pid, const std::wstring& location = std::wstring(), bool includeUnpluggedDevices = false)
        {
            std::vector<std::shared_ptr<Device>> devices;

            for (auto& device : m_enumerator.GetDevices())
            {
                if ((device->m_isPresent || includeUnpluggedDevices) &&
                    device->m_vid == vid &&
                    device->m_pid == pid &&
                    (location.empty() || device->m_location == location))
                {
                    devices.push_back(device);
                }
            }

            return devices;
        }

        std::vector<std::shared_ptr<Device>> FindRelatedDevices(const std::vector<std::shared_ptr<Device>>& devices)
        {
            std::vector<std::shared_ptr<Device>> relatedDevices;

            for (const auto& device : devices)
            {
                auto relatedPids = GetRelatedPids(device->m_pid, device->IsBootloaderMode());
                for (auto relatedPid : relatedPids)
                {
                    auto list = FindDevicesByUsbId(device->m_vid, relatedPid, device->m_location);
                    relatedDevices.insert(relatedDevices.end(), list.begin(), list.end());
                }
            }

            return relatedDevices;
        }

        std::vector<std::shared_ptr<Device>> FindRelatedDevices(uint16_t vid, uint16_t pid)
        {
            std::vector<std::shared_ptr<Device>> relatedDevices;

            auto relatedPids = GetRelatedPids(pid, true);
            for (auto relatedPid : relatedPids)
            {
                auto list = FindDevicesByUsbId(vid, relatedPid);
                relatedDevices.insert(relatedDevices.end(), list.begin(), list.end());
            }

            return relatedDevices;
        }

        static std::vector<uint16_t> GetRelatedPids(uint16_t pid, bool isBootloaderMode)
        {
            // Arduino boards with a direct USB connection (such as Leonardo or Micro)
            // have one USB serial port for the bootloader and one for the sketch.
            // Bootloader and sketch devices have the same VID but different PIDs.
            // To find related PIDs (bootloader vs. sketch device), we use the following heuristics:
            // Arduino, Adafruit, etc.:
            // - Bootloader PID: PIDxxxx with the MSB cleared
            // - Sketch PID: PIDxxxx with the MSB set
            // Others, who did not understand the above (Sparkfun):
            // - Bootloader PID: PIDxxxx
            // - Sketch PID: PIDxxxx + 1

            std::vector<uint16_t> relatedPids;

            if (isBootloaderMode)
            {
                relatedPids.push_back(pid | 0x8000);
                relatedPids.push_back(pid + 1);
            }
            else
            {
                relatedPids.push_back(pid & 0x7FFF);
                relatedPids.push_back(pid - 1);
            }

            return relatedPids;
        }

    private:
        static std::wstring ToUpper(std::wstring text)
        {
            for (auto& ch : text)
            {
                ch = static_cast<wchar_t>(std::towupper(ch));
            }

            return text;
        }

        void PrintMessage(MessageLevel level, _In_z_ _Printf_format_string_ const char* format, ...)
        {
            if (m_console != nullptr)
            {
                va_list args;
                va_start(args, format);
                PrintMessage(level, format, args);
                va_end(args);
            }
        }

        void PrintMessage(MessageLevel level, _In_z_ _Printf_format_string_ const char* format, va_list args)
        {
            if (m_console != nullptr)
            {
                va_list args2;
                va_copy(args2, args);
                size_t needed = vsnprintf(nullptr, 0, format, args2);
                va_end(args2);

                std::string str;
                if (needed > 0)
                {
                    str.resize(needed + 1);
                    size_t used = vsnprintf(&str[0], needed + 1, format, args);
                    str.resize(used);
                }

                m_console->WriteLine(level, str);
            }
        }

        void PrintDeviceProperties(const std::shared_ptr<Device>& device)
        {
            if (m_console != nullptr)
            {
                PrintMessage(MessageLevel::Debug, "- InstanceId: %ws", device->m_instanceId.c_str());
                PrintMessage(MessageLevel::Debug, "- Port: %ws", device->m_port.c_str());
                PrintMessage(MessageLevel::Debug, "- Location: %ws", device->m_location.c_str());
                PrintMessage(MessageLevel::Debug, "- ProductName: %ws", device->m_productName.c_str());
                PrintMessage(MessageLevel::Debug, "- IsPresent: %s", device->m_isPresent ? "true" : "false");
                PrintMessage(MessageLevel::Debug, "- IsCompositeDevice: %s", device->m_isCompositeDevice ? "true" : "false");
            }
        }

    private:
        IConsole* m_console = nullptr;
        Enumerator m_enumerator;
    };
}
