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

extern "C"
{
#include "avrdude.h"
}

#include "usb_com_helper.h"
#include "usb_com_locator.h"

class AvrdudeConsole : public UsbComLocator::IConsole
{
public:
    void WriteLine(UsbComLocator::MessageLevel level, const std::string& message) override
    {
        switch (level)
        {
        case UsbComLocator::MessageLevel::Verbose:
            avrdude_message(MSG_NOTICE, "%s: %s\n", progname, message.c_str());
            break;
        case UsbComLocator::MessageLevel::Debug:
            avrdude_message(MSG_DEBUG, "%s: %s\n", progname, message.c_str());
            break;
        default:
            avrdude_message(MSG_INFO, "%s: %s\n", progname, message.c_str());
            break;
        }
    }
};

int win32_find_usb_com_port(const char* deviceId, char** port, bool wait_for_device, bool find_related_devices, bool auto_reset)
{
    try
    {
        UsbComLocator::Locator::Options options;
        options.WaitForDevice = wait_for_device;
        options.FindRelatedDevices = find_related_devices;
        options.AutoReset = auto_reset;

        AvrdudeConsole console;
        UsbComLocator::Locator locator(&console);
        std::string filename = locator.FindPortForDevice(deviceId, &options);
        if (filename.empty())
        {
            *port = nullptr;
            return -1;
        }

        filename = "\\\\.\\" + filename;

        size_t bufferSize = filename.size() + 1;
        *port = static_cast<char*>(malloc(bufferSize));
        if (*port == nullptr)
        {
            return -1;
        }

        strncpy(*port, filename.c_str(), bufferSize);
        return 0;
    }
    catch (const std::exception&)
    {
        *port = nullptr;
        return -1;
    }
}
