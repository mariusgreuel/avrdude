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

#include "pthread.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <process.h>
#include <cerrno>
#include <exception>
#include <memory>
#include "IntegerHandleMap.h"

struct ThreadContext
{
    ~ThreadContext()
    {
        if (hCancel != nullptr)
        {
            CloseHandle(hCancel);
            hCancel = nullptr;
        }

        if (hThread != nullptr)
        {
            CloseHandle(hThread);
            hThread = nullptr;
        }
    }

    using start_routine_t = void* (*)(void*);
    HANDLE hThread = nullptr;
    HANDLE hCancel = nullptr;
    start_routine_t start_routine = nullptr;
    void* arguments = nullptr;
    int canceltype = 0;
};

static IntegerHandleMap<pthread_t, std::shared_ptr<ThreadContext>> contextMap;
static thread_local pthread_t currentThread;

static unsigned __stdcall pthread_start_routine_wrapper(void* arguments)
{
    pthread_t id = reinterpret_cast<pthread_t>(arguments);
    auto context = contextMap.Lookup(id);
    if (context == nullptr)
    {
        return ESRCH;
    }

    currentThread = id;
    context->start_routine(context->arguments);
    return 0;
}

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine) (void*), void* arg)
{
    try
    {
        auto context = std::make_shared<ThreadContext>();
        context->start_routine = start_routine;
        context->arguments = arg;

        auto id = contextMap.Add(context);
        context->hThread = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, pthread_start_routine_wrapper, reinterpret_cast<void*>(id), 0, nullptr));
        if (context->hThread == nullptr)
        {
            return ENOMEM;
        }

        *thread = id;
        return 0;
    }
    catch (std::exception&)
    {
        return ENOMEM;
    }
}

void pthread_exit(void* retval)
{
    _endthreadex(static_cast<unsigned int>(reinterpret_cast<uintptr_t>(retval)));
}

int pthread_cancel(pthread_t thread)
{
    auto context = contextMap.Lookup(thread);
    if (context == nullptr)
    {
        return ESRCH;
    }

    if (context->hCancel == nullptr)
    {
        context->hCancel = CreateEventW(nullptr, TRUE, FALSE, nullptr);
        if (context->hCancel == nullptr)
        {
            return ENOMEM;
        }
    }

    if (!SetEvent(context->hCancel))
    {
        return 1;
    }

    return 0;
}

int pthread_join(pthread_t thread, void** retval)
{
    auto context = contextMap.Lookup(thread);
    if (context == nullptr)
        return ESRCH;

    DWORD dwStatus = WaitForSingleObject(context->hThread, INFINITE);
    if (dwStatus == WAIT_OBJECT_0)
    {
        if (retval != nullptr)
        {
            DWORD dwExitCode = 0;
            if (GetExitCodeThread(context->hThread, &dwExitCode))
            {
                *retval = reinterpret_cast<void*>(static_cast<uintptr_t>(dwExitCode));
            }
            else
            {
                *retval = nullptr;
            }
        }
        
        contextMap.Remove(thread);
        return 0;
    }
    else
    {
        return EINVAL;
    }
}

int pthread_setcanceltype(int type, int* oldtype)
{
    auto context = contextMap.Lookup(currentThread);
    if (context == nullptr)
        return ESRCH;

    if (oldtype != nullptr)
    {
        *oldtype = context->canceltype;
    }

    context->canceltype = type;
    return 0;
}

void pthread_testcancel(void)
{
    auto context = contextMap.Lookup(currentThread);
    if (context == nullptr)
        return;

    if (context->hCancel != nullptr)
    {
        DWORD dwStatus = WaitForSingleObject(context->hCancel, 0);
        if (dwStatus == WAIT_OBJECT_0)
        {
            pthread_exit(nullptr);
        }
    }
}
