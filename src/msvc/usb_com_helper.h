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

#ifndef USB_COM_HELPER_H
#define USB_COM_HELPER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

int win32_find_usb_com_port(const char* deviceId, char** port, bool wait_for_device, bool find_related_devices, bool auto_reset);

#ifdef __cplusplus
}
#endif

#endif // USB_COM_HELPER_H
