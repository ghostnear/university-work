#ifndef DOMAIN_DYNAMICVECTOR_HPP
#define DOMAIN_DYNAMICVECTOR_HPP

#include <cstddef>
#include <cstdint>
#include <exception>

template<class TElem>
class DynamicArray
{
private:
    std::size_t size, capacity;
    TElem* data = nullptr;

    void resize(std::size_t newCapacity)
    {
        TElem* newData = new TElem[newCapacity];
        for(std::size_t index = 0; index < size; index++)
            newData[index] = data[index];
        if(data != nullptr)
            delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray()
    {
        size = 0;
        capacity = 1;
        data = new TElem[capacity];
    }

    ~DynamicArray()
    {
        if(data != nullptr)
            delete[] data;
    }

    // Getters.
    inline std::size_t get_length()
    {
        return size;
    }

    inline std::size_t get_capacity()
    {
        return capacity;
    }

    TElem& operator[](std::size_t index)
    {
        if(index >= size)
            throw std::exception();
        return data[index];
    }

    void remove_element(std::size_t index)
    {
        if(index >= size)
            throw std::exception();
        
        for(size_t position = index; position < size; position++)
            data[position] = data[position + 1];
        size--;

        if(size < capacity / 4)
            resize(capacity / 2);
    }

    // Setters.
    void add_element(TElem value)
    {
        data[size++] = value;
        if(size == capacity)
            resize(capacity * 2);
    }
};

#endif