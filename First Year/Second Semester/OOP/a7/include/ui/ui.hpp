#pragma once

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
    Service& service;

    void print_menu();
    void print_atmin_menu();
    void atmin_menu();
    void print_user_menu();

public:
    static Date read_date();
    static Time read_time();
    static std::string read_string(int maxlength, std::string message = "");
    static int read_integer(std::string message = "");

    UI(Service& newService);

    void main_loop();
};