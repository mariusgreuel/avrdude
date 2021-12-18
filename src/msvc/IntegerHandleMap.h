//
// HandleMap.h
// Copyright (C) 2019 Marius Greuel. All rights reserved.
//

#pragma once
#include <limits>
#include <unordered_map>
#include "ReaderWriterLock.h"

#pragma push_macro("max")
#undef max

template<typename TKey, typename TValue>
class IntegerHandleMap
{
public:
    TKey Add(TValue value)
    {
        TKey key = GetNextId();

        ReaderWriterLock::WriterLock lock(m_lock);
        m_map.emplace(key, value);
        return key;
    }

    void Remove(TKey key) noexcept
    {
        ReaderWriterLock::WriterLock lock(m_lock);
        m_map.erase(key);
    }

    TValue Lookup(TKey key) noexcept
    {
        ReaderWriterLock::ReaderLock lock(m_lock);

        TValue value;
        auto result = m_map.find(key);
        return result != m_map.end() ? result->second : nullptr;
    }

private:
    TKey GetNextId() noexcept
    {
        ReaderWriterLock::ReaderLock lock(m_lock);

        TKey key = m_next;
        while (m_map.find(key) != m_map.end())
        {
            key = GetNextId(key);
        }

        m_next = GetNextId(key);
        return key;
    }

    static TKey GetNextId(TKey key) noexcept
    {
        return key < std::numeric_limits<TKey>::max() ? key + 1 : 1;
    }

private:
    ReaderWriterLock m_lock;
    std::unordered_map<TKey, TValue> m_map;
    TKey m_next = 1;
};

#pragma pop_macro("max")
