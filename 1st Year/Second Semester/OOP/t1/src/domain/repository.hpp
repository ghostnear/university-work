#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include <vector>
#include "domain.hpp"

class Repository
{
private:
    std::vector<School> data;

public:
    void add(School school);
    void remove(School school);
    bool exists(School school);
    

    std::vector<School> get_all();
};

#endif