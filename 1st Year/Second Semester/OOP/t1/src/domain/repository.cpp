#include "repository.hpp"
#include "domain.hpp"
#include <algorithm>

bool Repository::exists(School schoolToCheck)
{
    for(auto school : data)
        if(school == schoolToCheck)
            return true;
    return false;
}

void Repository::add(School school)
{
    data.push_back(school);
}

void Repository::remove(School school)
{
    auto position = std::find(data.begin(), data.end(), school);
    if (position != data.end())
    {
        std::swap(*position, data.back());
        data.pop_back();
    }
}

std::vector<School> Repository::get_all()
{
    return data;
}