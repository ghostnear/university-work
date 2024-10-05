#include "domain/user.hpp"

std::string User::get_name()
{
    return name;
}

void User::set_name(std::string name)
{
    this->name = name;
}