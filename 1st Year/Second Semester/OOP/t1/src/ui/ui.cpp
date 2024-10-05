#include "ui.hpp"

UI::UI(Service& service) : service(service)
{
    
}

int UI::read_integer(std::string message)
{
    if(message != "")
        std::cout << message;
    
    int result = 0;
    std::cin >> result;

    return result;
}

double UI::read_double(std::string message)
{
    if(message != "")
        std::cout << message;
    
    double result = 0;
    std::cin >> result;

    return result;
}

std::string UI::read_string(std::string message)
{
    if(message != "")
        std::cout << message;
    
    std::string result = "";
    std::cin >> result;

    return result;
}

void UI::print_menu()
{
    std::cout << "\nSchool management simulator\n\n";
    std::cout << "1. Remove a school.\n";
    std::cout << "2. Show all schools sorted.\n";
    std::cout << "3. Mark schools as visited.\n";
    std::cout << "4. Exit.\n";
}

void UI::run()
{
    is_running = true;

    while(is_running)
    {
        print_menu();
        int choice = UI::read_integer("\nAction > ");

        switch(choice)
        {
            case 1:
            {
                std::string name = UI::read_string("Insert school name: ");
                double latitude = UI::read_double("Insert latitude: ");
                double longitude = UI::read_double("Insert longitude: ");
                School querrySchool = School(
                    name,
                    Address{longitude, latitude},
                    {1, 1, 1970}
                );

                if(!service.remove_school(querrySchool))
                    std::cout << "\nInput school does not exist!\n";
                else
                    std::cout << "\nInput school removed successfully!\n";

                break;
            }

            case 2:
                std::cout << "\n";
                for(auto school : service.get_all_sorted())
                    std::cout << school.to_string() << "\n";
                break;

            case 4:
                is_running = false;
                break;

            default:
                std::cout << "Unknown input detected.\n";
                break;
        }
    }
}
