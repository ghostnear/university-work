#pragma once

#include "../service/service.hpp"

class UI
{
private:
    bool isRunning = true;
    RealEstateAgency& service;

    void print_menu();

public:
    UI(RealEstateAgency& service);

    void run();
};