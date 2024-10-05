#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "../domain/repository.hpp"

class Service
{
private:
    Repository& repository;

public:
    Service(Repository& repository);

    bool add_school(School newSchool);
    bool remove_school(School school);

    std::vector<School> get_all_sorted();
};

#endif