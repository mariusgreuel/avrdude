//
// libwinftdi.h
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

namespace LibWinFtdi
{
    enum
    {
        FT_OK,
        FT_INVALID_HANDLE,
        FT_DEVICE_NOT_FOUND,
        FT_DEVICE_NOT_OPENED,
        FT_IO_ERROR,
        FT_INSUFFICIENT_RESOURCES,
        FT_INVALID_PARAMETER,
        FT_INVALID_BAUD_RATE,
        FT_DEVICE_NOT_OPENED_FOR_ERASE,
        FT_DEVICE_NOT_OPENED_FOR_WRITE,
        FT_FAILED_TO_WRITE_DEVICE,
        FT_EEPROM_READ_FAILED,
        FT_EEPROM_WRITE_FAILED,
        FT_EEPROM_ERASE_FAILED,
        FT_EEPROM_NOT_PRESENT,
        FT_EEPROM_NOT_PROGRAMMED,
        FT_INVALID_ARGS,
        FT_NOT_SUPPORTED,
        FT_OTHER_ERROR,
        FT_DEVICE_LIST_NOT_READY,
    };

    enum
    {
        FT_DEVICE_BM,
        FT_DEVICE_AM,
        FT_DEVICE_100AX,
        FT_DEVICE_UNKNOWN,
        FT_DEVICE_2232C,
        FT_DEVICE_232R,
        FT_DEVICE_2232H,
        FT_DEVICE_4232H,
        FT_DEVICE_232H,
    };

    enum
    {
        FT_FLAGS_OPENED = 1,
        FT_FLAGS_HISPEED = 2,
    };

    enum
    {
        FT_OPEN_BY_SERIAL_NUMBER = 1,
        FT_OPEN_BY_DESCRIPTION = 2,
        FT_OPEN_BY_LOCATION = 4,
    };

    enum
    {
        FT_PURGE_RX = 1,
        FT_PURGE_TX = 2,
    };

    enum
    {
        FT_EVENT_RXCHAR = 1,
        FT_EVENT_MODEM_STATUS = 2,
        FT_EVENT_LINE_STATUS = 4,
    };

    typedef PVOID FT_HANDLE;
    typedef ULONG FT_STATUS;

    struct DeviceInfo
    {
        ULONG Flags;
        ULONG Type;
        ULONG ID;
        DWORD LocId;
        char SerialNumber[16];
        char Description[64];
        FT_HANDLE ftHandle;
    };

    class FtdiApi
    {
    public:
        FtdiApi() = default;
        FtdiApi(const FtdiApi&) = delete;
        FtdiApi& operator=(const FtdiApi&) = delete;
        FtdiApi(FtdiApi&&) = delete;
        FtdiApi& operator=(FtdiApi&&) = delete;

        ~FtdiApi()
        {
            Unload();
        }

        HRESULT Load()
        {
            if (m_module != nullptr)
                return S_FALSE;

            HMODULE module = LoadLibraryExW(L"ftd2xx.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
            if (module == nullptr)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }

            HRESULT hr = S_OK;
            if (FAILED(hr = LoadImport(module, "FT_CreateDeviceInfoList", &FT_CreateDeviceInfoList)) ||
                FAILED(hr = LoadImport(module, "FT_GetDeviceInfoList", &FT_GetDeviceInfoList)) ||
                FAILED(hr = LoadImport(module, "FT_OpenEx", &FT_OpenEx)) ||
                FAILED(hr = LoadImport(module, "FT_Close", &FT_Close)) ||
                FAILED(hr = LoadImport(module, "FT_ResetDevice", &FT_ResetDevice)) ||
                FAILED(hr = LoadImport(module, "FT_ResetPort", &FT_ResetPort)) ||
                FAILED(hr = LoadImport(module, "FT_CyclePort", &FT_ResetPort)) ||
                FAILED(hr = LoadImport(module, "FT_Purge", &FT_Purge)) ||
                FAILED(hr = LoadImport(module, "FT_SetTimeouts", &FT_SetTimeouts)) ||
                FAILED(hr = LoadImport(module, "FT_SetBaudRate", &FT_SetBaudRate)) ||
                FAILED(hr = LoadImport(module, "FT_SetBitMode", &FT_SetBitMode)) ||
                FAILED(hr = LoadImport(module, "FT_SetLatencyTimer", &FT_SetLatencyTimer)) ||
                FAILED(hr = LoadImport(module, "FT_GetQueueStatus", &FT_GetQueueStatus)) ||
                FAILED(hr = LoadImport(module, "FT_SetEventNotification", &FT_SetEventNotification)) ||
                FAILED(hr = LoadImport(module, "FT_SetUSBParameters", &FT_SetUSBParameters)) ||
                FAILED(hr = LoadImport(module, "FT_Read", &FT_Read)) ||
                FAILED(hr = LoadImport(module, "FT_Write", &FT_Write)))
            {
                FreeLibrary(module);
                return hr;
            }

            m_module = module;
            return S_OK;
        }

        HRESULT Unload()
        {
            if (m_module == nullptr)
                return S_FALSE;

            FreeLibrary(m_module);
            m_module = nullptr;

            return S_OK;
        }

    private:
        template<typename T>
        static HRESULT LoadImport(HMODULE module, LPCSTR lpProcName, T** ptr)
        {
            auto proc = GetProcAddress(module, lpProcName);
            if (proc == nullptr)
            {
                *ptr = nullptr;
                return HRESULT_FROM_WIN32(GetLastError());
            }

            *ptr = reinterpret_cast<T*>(proc);
            return S_OK;
        }

    private:
        HMODULE m_module = nullptr;

    protected:
        FT_STATUS(WINAPI* FT_CreateDeviceInfoList)(LPDWORD lpdwNumDevs) = nullptr;
        FT_STATUS(WINAPI* FT_GetDeviceInfoList)(DeviceInfo* pDest, LPDWORD lpdwNumDevs) = nullptr;
        FT_STATUS(WINAPI* FT_OpenEx)(PVOID pArg1, DWORD Flags, FT_HANDLE* pHandle) = nullptr;
        FT_STATUS(WINAPI* FT_Close)(FT_HANDLE ftHandle) = nullptr;
        FT_STATUS(WINAPI* FT_ResetDevice)(FT_HANDLE ftHandle) = nullptr;
        FT_STATUS(WINAPI* FT_ResetPort)(FT_HANDLE ftHandle) = nullptr;
        FT_STATUS(WINAPI* FT_CyclePort)(FT_HANDLE ftHandle) = nullptr;
        FT_STATUS(WINAPI* FT_Purge)(FT_HANDLE ftHandle, DWORD dwMask) = nullptr;
        FT_STATUS(WINAPI* FT_SetTimeouts)(FT_HANDLE ftHandle, DWORD dwReadTimeout, DWORD dwWriteTimeout) = nullptr;
        FT_STATUS(WINAPI* FT_SetBaudRate)(FT_HANDLE ftHandle, DWORD dwBaudRate) = nullptr;
        FT_STATUS(WINAPI* FT_SetBitMode)(FT_HANDLE ftHandle, UCHAR ucMask, UCHAR ucEnable) = nullptr;
        FT_STATUS(WINAPI* FT_SetLatencyTimer)(FT_HANDLE ftHandle, UCHAR ucTimer) = nullptr;
        FT_STATUS(WINAPI* FT_GetQueueStatus)(FT_HANDLE ftHandle, DWORD* dwRxBytes) = nullptr;
        FT_STATUS(WINAPI* FT_SetEventNotification)(FT_HANDLE ftHandle, DWORD Mask, PVOID Param) = nullptr;
        FT_STATUS(WINAPI* FT_SetUSBParameters)(FT_HANDLE ftHandle, DWORD dwInTransferSize, DWORD dwOutTransferSize) = nullptr;
        FT_STATUS(WINAPI* FT_Read)(FT_HANDLE ftHandle, LPVOID lpBuffer, DWORD dwBytesToRead, LPDWORD lpBytesReturned) = nullptr;
        FT_STATUS(WINAPI* FT_Write)(FT_HANDLE ftHandle, LPVOID lpBuffer, DWORD dwBytesToWrite, LPDWORD lpBytesWritten) = nullptr;
    };

    class FtdiEnumerator : public FtdiApi
    {
    public:
        FtdiEnumerator() = default;
        FtdiEnumerator(const FtdiEnumerator&) = delete;
        FtdiEnumerator& operator=(const FtdiEnumerator&) = delete;
        FtdiEnumerator(FtdiEnumerator&&) = delete;
        FtdiEnumerator& operator=(FtdiEnumerator&&) = delete;

    public:
        FT_STATUS EnumerateDevices()
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            DWORD lpdwNumDevs = 0;
            FT_STATUS status = FT_CreateDeviceInfoList(&lpdwNumDevs);
            if (status != FT_OK)
                return status;

            m_devices.resize(lpdwNumDevs);

            status = FT_GetDeviceInfoList(m_devices.data(), &lpdwNumDevs);
            if (status != FT_OK)
                return status;

            return FT_OK;
        }

        const std::vector<DeviceInfo>& GetDevices() const
        {
            return m_devices;
        }

    private:
        std::vector<DeviceInfo> m_devices;
    };

    class FtdiDevice : public FtdiApi
    {
    public:
        FtdiDevice() = default;
        FtdiDevice(const FtdiDevice&) = delete;
        FtdiDevice& operator=(const FtdiDevice&) = delete;
        FtdiDevice(FtdiDevice&&) = delete;
        FtdiDevice& operator=(FtdiDevice&&) = delete;

        ~FtdiDevice()
        {
            if (m_event != nullptr)
            {
                CloseHandle(m_event);
            }
        }

        HANDLE GetNotificationEvent() const
        {
            return m_event;
        }

    public:
        FT_STATUS OpenBySerialNumber(const char* serialNumber)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_OpenEx(const_cast<char*>(serialNumber), FT_OPEN_BY_SERIAL_NUMBER, &m_handle);
        }

        FT_STATUS OpenByLocation(uint32_t location)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_OpenEx(&location, FT_OPEN_BY_LOCATION, &m_handle);
        }

        FT_STATUS Close()
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_Close(m_handle);
        }

        FT_STATUS ResetDevice()
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_ResetDevice(m_handle);
        }

        FT_STATUS ResetPort()
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_ResetPort(m_handle);
        }

        FT_STATUS CyclePort()
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_CyclePort(m_handle);
        }

        FT_STATUS Purge(DWORD dwMask = FT_PURGE_RX | FT_PURGE_TX)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_Purge(m_handle, dwMask);
        }

        FT_STATUS SetTimeouts(DWORD dwReadTimeout, DWORD dwWriteTimeout)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_SetTimeouts(m_handle, dwReadTimeout, dwWriteTimeout);
        }

        FT_STATUS SetBaudRate(DWORD dwBaudRate)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_SetBaudRate(m_handle, dwBaudRate);
        }

        FT_STATUS SetBitMode(UCHAR ucMask, UCHAR ucEnable)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_SetBitMode(m_handle, ucMask, ucEnable);
        }

        FT_STATUS SetLatencyTimer(UCHAR ucTimer)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_SetLatencyTimer(m_handle, ucTimer);
        }

        FT_STATUS GetQueueStatus(DWORD* dwRxBytes)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_GetQueueStatus(m_handle, dwRxBytes);
        }

        FT_STATUS SetEventNotification(DWORD Mask)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            if (m_event == nullptr)
            {
                m_event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
            }

            return FT_SetEventNotification(m_handle, Mask, m_event);
        }

        FT_STATUS SetUSBParameters(DWORD dwInTransferSize, DWORD dwOutTransferSize)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_SetUSBParameters(m_handle, dwInTransferSize, dwOutTransferSize);
        }

        FT_STATUS Read(LPVOID lpBuffer, DWORD dwBytesToRead, LPDWORD lpBytesReturned)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_Read(m_handle, lpBuffer, dwBytesToRead, lpBytesReturned);
        }

        FT_STATUS Write(LPVOID lpBuffer, DWORD dwBytesToWrite, LPDWORD lpBytesWritten)
        {
            if (FAILED(Load()))
            {
                return FT_INVALID_HANDLE;
            }

            return FT_Write(m_handle, lpBuffer, dwBytesToWrite, lpBytesWritten);
        }

    private:
        FT_HANDLE m_handle = nullptr;
        HANDLE m_event = nullptr;
    };
}
