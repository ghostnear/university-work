#pragma once

#include <cstdio>
#include "base.hpp"

template<typename TElem>
class MemoryRepository : public Repository<TElem>
{
protected:
    std::vector<TElem> data;

public:
    std::size_t get_size() override
    {
        return data.size();
    }

    std::vector<TElem> get_data() override
    {
        return data;
    }

    void add_element(TElem element) override
    {
        data.push_back(element);
    }

    TElem& get_element(std::size_t index) override
    {
        return data[index];
    }

    void update_element(std::size_t index, TElem newData) override
    {
        data[index] = newData;
    }

    void delete_element(std::size_t index) override
    {
        std::swap(data[index], data.back());
        data.pop_back();
    }
};