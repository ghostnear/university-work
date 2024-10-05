#ifndef UI_HPP
#define UI_HPP

#include "service/all.hpp"
#include "service/service.hpp"

#include <cstdio>
#include <cstring>
#include <iostream>

class UI
{
private:
    bool exited = false;
    bool atmin_mode = false;
    bool user_mode = false;
    Service* service;

    void print_menu();
    std::string read_string(int maxlength, std::string message = "");
    int read_integer(std::string message = "");
    Date read_date();
    Time read_time();

    void print_atmin_menu();
    void atmin_menu();

    void print_user_menu();

public:
    UI(Service* newService);

    void main_loop();
};

#endif