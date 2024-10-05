#ifndef REPOSITORY_MEMORY_HPP
#define REPOSITORY_MEMORY_HPP

#include "base.hpp"
#include "domain/dynamicarray.hpp"

template<typename TElem>
class MemoryRepository : public Repository<TElem>
{
private:
    DynamicArray<TElem> data;

public:
    std::size_t get_size() override
    {
        return data.get_length();
    }

    void add_element(TElem element) override
    {
        data.add_element(element);
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
        data.remove_element(index);
    }
};

#endif