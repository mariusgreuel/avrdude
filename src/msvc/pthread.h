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

#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <stdint.h>

#define PTHREAD_CANCEL_ASYNCHRONOUS 1

typedef uintptr_t pthread_t;
typedef int pthread_attr_t;

#ifdef __cplusplus
extern "C" {
#endif

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine) (void*), void* arg);
int pthread_cancel(pthread_t thread);
int pthread_join(pthread_t thread, void** retval);
int pthread_setcanceltype(int type, int* oldtype);
void pthread_testcancel(void);

#ifdef __cplusplus
}
#endif

#endif
