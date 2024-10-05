#include "service.hpp"
#include <vector>
#include <algorithm>

Service::Service(Repository& repository) : repository(repository) {}

bool Service::add_school(School newSchool)
{
    if(!repository.exists(newSchool))
    {
        repository.add(newSchool);
        return true;
    }
    return false;
}

bool Service::remove_school(School school)
{
    if(!repository.exists(school))
        return false;

    repository.remove(school);
    return true;
}

std::vector<School> Service::get_all_sorted()
{
    std::vector<School> result = repository.get_all();

    std::sort(result.begin(), result.end());

    return result;
}