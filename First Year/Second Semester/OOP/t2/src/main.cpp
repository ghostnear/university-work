#include "ui/ui.hpp"

int main()
{
    RealEstateAgency service;
    UI ui(service);

    ui.run();

    return 0;
}