#ifndef REPOSITORY_BASE_HPP
#define REPOSITORY_BASE_HPP

#include <vector>
#include "domain/all.hpp"

template<typename TElem>
class Repository
{
public:
    virtual std::size_t get_size() = 0;
    virtual std::vector<TElem> get_data() = 0;
    virtual void add_element(TElem element) = 0;
    virtual void delete_element(std::size_t index) = 0;
    virtual TElem& get_element(std::size_t index) = 0;
    virtual void update_element(std::size_t index, TElem newData) = 0;
};

#endif