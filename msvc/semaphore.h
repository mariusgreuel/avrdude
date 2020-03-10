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

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

typedef struct sem
{
    void* handle;
} sem_t;

#ifdef __cplusplus
extern "C" {
#endif

int sem_init(sem_t* sem, int pshared, unsigned int value);
int sem_destroy(sem_t* sem);
int sem_post(sem_t* sem);
int sem_wait(sem_t* sem);

#ifdef __cplusplus
}
#endif

#endif
