#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include "../service/service.hpp"

class UI
{
private:
    bool is_running = false;
    Service& service;

public:
    UI(Service& service);

    void run();
    void print_menu();

    static int read_integer(std::string message = "");
    static double read_double(std::string message = "");
    static std::string read_string(std::string message = "");
};

#endif