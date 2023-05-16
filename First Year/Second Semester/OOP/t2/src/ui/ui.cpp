#include "ui.hpp"

UI::UI(RealEstateAgency& service) : service(service) {}

void UI::print_menu()
{
    std::cout << "1. Remove a client.\n";
    std::cout << "2. Show all clients and dwellings.\n";
    std::cout << "3. Add a dwelling.\n";
    std::cout << "4. Save all clients to file.\n";
    std::cout << "5. Exit.\n";
    std::cout << "\nAction > ";
}

void UI::run()
{
    while(isRunning)
    {
        print_menu();

        int choice = 0;
        std::cin >> choice;

        switch(choice)
        {
        case 1:
        {
            std::string clientName;
            std::cout << "Give client name: ";
            std::cin >> clientName;

            service.removeClient(clientName);
            break;
        }

        case 2:
        {
            for(auto client : service.getAllClients())
                std::cout << client.toString() << "\n";
            for(auto dwelling : service.getAllDwellings())
                std::cout << dwelling.toString() << "\n";
            break;
        }

        case 3:
        {
            double price;
            bool profitable;
            
            std::cout << "Price: ";
            std::cin >> price;
            std::cout << "Is it profitable (1 = yes, 0 = no): ";
            std::cin >> profitable;

            service.addDwelling(
                price,
                profitable
            );

            std::cout << "Interested clients: \n";
            for(auto client : service.getInterestedClients(Dwelling(price, profitable)))
                std::cout << client.toString() << "\n";

            break;
        }

        case 4:
        {
            std::string fileName;

            std::cout << "Filename: ";
            std::cin >> fileName;
            
            service.writeToFile(fileName);

            break;
        }

        case 5:
            isRunning = false;
            break;
        }
    }
}