#pragma once

#include "utils/hash_table.hpp"
#include <any>
#include <sstream>

class SymbolTable
{
public:
    HashTable<std::string> m_table;

    SymbolTable() : m_table(10)
    {
        add("NULL", 0);
    }

    void add(std::string key, std::any value)
    {
        m_table.add(key, value);
    }

    void remove(std::string key)
    {
        m_table.remove(key);
    }

    std::any get(std::string key)
    {
        return m_table.get(key);
    }

    std::stringstream to_stream()
    {
        return m_table.to_stream();
    }
};

int any_to_int(std::any value);
double any_to_double(std::any value);
float any_to_float(std::any value);
std::string any_to_string(std::any value);