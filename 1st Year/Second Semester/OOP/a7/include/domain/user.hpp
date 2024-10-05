#pragma once

#include <string>
#include "event.hpp"

class User
{
private:
    std::string name;

public:
    std::string get_name();
    void set_name(std::string name);
};