#include "domain.hpp"
#include <sstream>

std::string Address::to_string()
{
    return integer_to_string(latitude) + ", " + integer_to_string(longitude);
}

std::string Date::to_string()
{
    return integer_to_string(year) + "." + integer_to_string(month) + "." + integer_to_string(day);
}

School::School(std::string name, Address address, Date dateOfVisit)
{
    this->name = name;
    this->address = address;
    this->dateOfVisit = dateOfVisit;
    this->visited = false;
}

std::string School::to_string()
{
    return name + " | " + address.to_string() + " | " + dateOfVisit.to_string() + " | " + (visited ? "true" : "false");
}