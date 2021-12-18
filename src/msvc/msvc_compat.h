/*
 * avrdude - A Downloader/Uploader for AVR device programmers
 * Copyright (C) 2018 Marius Greuel
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

#pragma once
#include <stdio.h>
#include <string.h>
#include <io.h>

#pragma warning(disable : 4018) // signed/unsigned mismatch
#pragma warning(disable : 4244) // conversion from '...' to '...', possible loss of data
#pragma warning(disable : 4267) // conversion from '...' to '...', possible loss of data

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "setupapi.lib")

#define PATH_MAX _MAX_PATH

#define setvbuf msvc_setvbuf

static inline int msvc_setvbuf(
    FILE* const public_stream,
    char* const buffer,
    int const type,
    size_t const buffer_size_in_bytes
)
{
    // Just ignore calls to setvbuf with invalid buffer size.
    // Purpose of setvbuf calls unknown, probably in an attempt to fix broken
    // programs that capture stdout and stderr using separate stream handles?
    return 0;
}

static inline int strcasecmp(const char *s1, const char *s2) { return _stricmp(s1, s2); }
static inline int strncasecmp(const char *s1, const char *s2, size_t n) { return _strnicmp(s1, s2, n); }
