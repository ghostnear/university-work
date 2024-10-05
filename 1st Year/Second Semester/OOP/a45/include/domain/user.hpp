#ifndef DOMAIN_USER_HPP
#define DOMAIN_USER_HPP

#include <string>
#include "event.hpp"
#include "dynamicarray.hpp"

class User
{
private:
    std::string name;

public:
    std::string get_name();
    void set_name(std::string name);
};

#endif