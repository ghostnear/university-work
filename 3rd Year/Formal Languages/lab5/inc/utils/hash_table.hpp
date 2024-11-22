#pragma once

#include <any>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <list>

// Simplest hashtable implementation.

template<typename TKey>
class HashTable
{
private:
    size_t m_bucketCount;
    std::vector<std::list<std::pair<TKey, std::any>>> m_table;

    std::size_t hashFunction(const TKey& key) {
        std::hash<TKey> hasher;
        std::size_t hash = hasher(key);
        return hash % m_bucketCount;
    }

public:
    HashTable(size_t bucketCount) : m_bucketCount(bucketCount), m_table(bucketCount) {}

    void add(TKey key, std::any value)
    {
        auto index = hashFunction(key);
        m_table[index].push_back(std::make_pair(key, value));
    }

    std::any get(TKey key)
    {
        auto index = hashFunction(key);
        for (auto it = m_table[index].begin(); it != m_table[index].end(); ) {
            if (it->first == key) {
                return it->second;
            } else {
                ++it;
            }
        }
        return nullptr;
    }

    void remove(TKey key)
    {
        auto index = hashFunction(key);
        for (auto it = m_table[index].begin(); it != m_table[index].end(); ) {
            if (it->first == key) {
                it = m_table[index].erase(it);
                return;
            } else {
                ++it;
            }
        }
    }

    std::stringstream to_stream()
    {
        std::stringstream result;
        for(auto index = 0u; index < m_bucketCount; index++)
        {
            if(m_table[index].size() == 0)
                continue;

            for (auto x : m_table[index])
            {
                result << "(" << x.first << ", ";

                if (x.second.type() == typeid(int))
                    result << std::any_cast<int>(x.second);
                else if (x.second.type() == typeid(std::string))
                    result << std::any_cast<std::string>(x.second);
                else if (x.second.type() == typeid(float))
                    result << std::any_cast<float>(x.second);
                else if (x.second.type() == typeid(double))
                    result << std::any_cast<double>(x.second);

                result << ") ";
            }
                
            result << '\n';
        }
        return result;
    }
};