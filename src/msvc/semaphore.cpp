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

#include "semaphore.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int sem_init(sem_t* sem, int pshared, unsigned int value)
{
    if (sem == nullptr)
        return -1;

    sem->handle = nullptr;

    auto handle = CreateSemaphoreW(nullptr, value, MAXLONG32, nullptr);
    if (handle == nullptr)
        return -1;

    sem->handle = handle;
    return 0;
}

int sem_destroy(sem_t* sem)
{
    if (sem == nullptr)
        return -1;

    if (sem->handle != nullptr)
    {
        CloseHandle(sem->handle);
        sem->handle = nullptr;
    }
    
    return 0;
}

int sem_post(sem_t* sem)
{
    if (sem == nullptr)
        return -1;

    BOOL bStatus = ReleaseSemaphore(sem->handle, 1, nullptr);
    return bStatus ? 0 : -1;
}

int sem_wait(sem_t* sem)
{
    if (sem == nullptr)
        return -1;

    DWORD dwStatus = WaitForSingleObject(sem->handle, INFINITE);
    return dwStatus == WAIT_OBJECT_0 ? 0 : -1;
}
