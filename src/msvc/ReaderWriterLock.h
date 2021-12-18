//
// ReaderWriterLock.h
// Copyright (C) 2019 Marius Greuel. All rights reserved.
//

#pragma once

class ReaderWriterLock
{
public:
    class ReaderLock
    {
    public:
        ReaderLock(ReaderWriterLock& lock) noexcept : m_lock(lock)
        {
            Acquire();
        }

        ~ReaderLock()
        {
            Release();
        }

    private:
        void Acquire() noexcept
        {
            AcquireSRWLockShared(&m_lock.m_srwlock);
        }

        void Release() noexcept
        {
            ReleaseSRWLockShared(&m_lock.m_srwlock);
        }

    private:
        ReaderWriterLock& m_lock;
    };

    class WriterLock
    {
    public:
        WriterLock(ReaderWriterLock& lock) noexcept : m_lock(lock)
        {
            Acquire();
        }

        ~WriterLock()
        {
            Release();
        }

    private:
        void Acquire() noexcept
        {
            AcquireSRWLockExclusive(&m_lock.m_srwlock);
        }

        void Release() noexcept
        {
            ReleaseSRWLockExclusive(&m_lock.m_srwlock);
        }

    private:
        ReaderWriterLock& m_lock;
    };

public:
    ReaderWriterLock() noexcept
    {
        InitializeSRWLock(&m_srwlock);
    }

    ReaderWriterLock(const ReaderWriterLock&) = delete;
    ReaderWriterLock& operator=(const ReaderWriterLock&) = delete;
    ReaderWriterLock(ReaderWriterLock&&) = delete;
    ReaderWriterLock& operator=(ReaderWriterLock&&) = delete;

private:
    SRWLOCK m_srwlock{};
};
