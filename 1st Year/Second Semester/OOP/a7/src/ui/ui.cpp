#include "ui/ui.hpp"
#include "domain/time.hpp"
#include <cstdio>
#include <exception>

UI::UI(Service& newService) : service(newService){}

std::string UI::read_string(int maxlength, std::string message)
{
    char* result = (char*)calloc(maxlength, sizeof(char));
    
    if(message != "")
        printf("%s", message.c_str());

    std::cin.getline(result, maxlength);

    std::string stringResult(result);

    free(result);

    return stringResult;
}

int UI::read_integer(std::string message)
{
    static int result;

    if(message != "")
        printf("%s", message.c_str());

    std::string text = read_string(50);

    char* end;
    result = strtol(text.c_str(), &end, 10);
    if(end == text)
    {
        printf("\nNon-integer input entered!\n\n");
        return read_integer(message);
    }

    return result;
}

Date UI::read_date()
{
    Date result = Date(
        read_integer("Day: "),
        read_integer("Month: "),
        read_integer("Year: ")
    );
    try
    {
        DateValidator::validate(result);
    }
    catch(CustomException const&)
    {
        printf("\nInvalid date entered!\nTry again.\n\n");
        return read_date();
    }
    return result;
}

Time UI::read_time()
{
    Time result = Time(
        read_integer("Seconds: "),
        read_integer("Minutes: "),
        read_integer("Hours: ")
    );
    try
    {
        TimeValidator::validate(result);
    }
    catch(CustomException const&)
    {
        printf("\nInvalid time entered!\nTry again.\n\n");
        return read_time();
    }
    return result;
}

void UI::print_menu()
{
    printf("\nWelcome to Event Manager Simulator!\n\n");
    printf("Please select the mode in which you wish to start the application:\n");
    printf("1. Administrator Mode.\n");
    printf("2. User mode.\n");
    printf("3. Exit.\n\n");
}

void UI::print_atmin_menu()
{
    printf("\nEvent Manager Simulator (Administrator Mode)\n\n");
    printf("1. View all events.\n");
    printf("2. Add a new event.\n");
    printf("3. Delete an event.\n");
    printf("4. Update existing event.\n");
    printf("5. Exit administrator mode.\n\n");
}

void UI::print_user_menu()
{
    printf("\nEvent Manager Simulator (User Mode: %s)\n\n", service.get_user().c_str());
    printf("1. See all the events for a given month.\n");
    printf("2. See all events from your list.\n");
    printf("3. Export your list (also opens it for preview).\n");
    printf("4. Exit user mode.\n\n");
}

void UI::main_loop()
{
    while(!exited)
    {
        if(!atmin_mode && !user_mode)
        {
            print_menu();

            int choice = read_integer("Action > ");

            enum ModeChoice
            {
                ATMIN = 1,
                USER,
                EXIT
            };

            switch(choice)
            {
            case ModeChoice::ATMIN:
                atmin_mode = true;
                break;

            case ModeChoice::USER:
                user_mode = true;
                break;

            case ModeChoice::EXIT:
                exited = true;
                break;

            default:
                printf("\nYou did not input a valid choice, dumbass!\n\n");
                break;
            }
        }
        else if(atmin_mode)
        {
            print_atmin_menu();

            int choice = read_integer("Action > ");

            enum AtminMenuChoices
            {
                VIEW_EVENTS = 1,
                ADD_EVENT,
                DELETE_EVENT,
                UPDATE_EVENT,
                EXIT
            };

            switch(choice)
            {
            case AtminMenuChoices::VIEW_EVENTS:
            {
                std::vector<Event> events = service.get_events();
                if(events.size() == 0)
                    printf("\nNo events registered in the database.\n");
                else
                    for(std::size_t index = 0; index < events.size(); index++)
                        printf("Index %lu\n%s\n", index, events[index].to_string().c_str());
                break;
            }

            case AtminMenuChoices::ADD_EVENT:
            {
                // Need to be read as variables because the reading order becomes wrong because of stdcall.
                std::string title = read_string(50, "New title (max 50 characters): ");
                std::string description = read_string(500, "New description (max 500 characters): ");
                std::string link = read_string(500, "New link (max 500 characters): ");
                Date date = read_date();
                Time time = read_time();
                try
                {
                    service.add_event(title,  description, link, date, time);
                    printf("\nEvent added successfully!\n");
                }
                catch(CustomException const&) { printf("\nEvent already exists.\n"); }
                break;
            }

            case AtminMenuChoices::DELETE_EVENT:
                try
                {
                    service.remove_event(read_integer("\nIndex to remove the element from: "));
                    printf("\nEvent removed successfully!\n");
                }
                catch(CustomException const&) { printf("\nCould not remove the event at the specified index.\n"); }
                break;

            case AtminMenuChoices::UPDATE_EVENT:
            {
                std::size_t index = read_integer("Index: ");
                std::string title = read_string(50, "New title (max 50 characters): ");
                std::string description = read_string(500, "New description (max 500 characters): ");
                std::string link = read_string(500, "New link (max 500 characters): ");
                Date date = read_date();
                Time time = read_time();
                try
                {
                    service.update_event(index, title,  description, link, date, time);
                    printf("\nEvent updated successfully!\n");
                }
                catch(CustomException const&) { printf("\nCould not update the event at the specified index.\n"); }
                break;
            }

            case AtminMenuChoices::EXIT:
                atmin_mode = false;
                break;

            default:
                printf("\nYou did not input a valid choice, dumbass!\n\n");
                break;
            }
        }
        else if(user_mode)
        {
            if(service.get_user() == "")
                service.set_user(read_string(50, "\nUsername to use: "));

            print_user_menu();

            int choice = read_integer("Action > ");

            enum UserMenuChoices
            {
                SEE_GIVEN_MONTH = 1,
                SEE_LIST,
                EXPORT_LIST,
                EXIT
            };

            switch(choice)
            {
            case UserMenuChoices::SEE_GIVEN_MONTH:
            {
                int result = read_integer("\nMonth: ");

                std::vector<Event> events = service.get_events_by_month(result);

                if(events.size() == 0)
                    printf("\nNo events registered in the database for the specified month.\n");
                else
                {
                    std::size_t index = 0;
                    bool exitedInnerLoop = false;

                    while(!exitedInnerLoop)
                    {
                        printf("\nCurrent event:\n\n%s\n", events[index].to_string().c_str());
                        printf("1. Go to next event.\n");
                        printf("2. Open event in browser.\n");
                        printf("3. Add the event to your list.\n");
                        printf("4. Exit.\n\n");

                        choice = read_integer("Action > ");

                        switch(choice)
                        {
                        case 1:
                            index++;
                            if(index == events.size())
                                index = 0;
                            break;

                        case 2:
                            system(("librewolf " + events[index].get_link()).c_str());
                            break;
                        
                        case 3:
                            if(service.check_user_event(events[index]))
                                printf("\nEvent was already added to the list!\n");
                            else
                            {
                                service.add_user_event(events[index]);
                                printf("\nEvent added to the list!\nBringing you back to the previous menu...\n");
                                exitedInnerLoop = true;
                            }
                            break;

                        case 4:
                            exitedInnerLoop = true;
                            break;

                        default:
                            printf("\nYou did not input a valid choice, dumbass!\n\n");
                            break;
                        }
                    }
                }
                break;
            }

            case UserMenuChoices::SEE_LIST:
            {
                std::vector<Event> events = service.get_user_events();

                if(events.size() == 0)
                    printf("\nNo events registered in the database for the current user.\n");
                else
                {
                    std::size_t index = 0;
                    bool exitedInnerLoop = false;

                    while(!exitedInnerLoop)
                    {
                        printf("\nCurrent event:\n\n%s\n", events[index].to_string().c_str());
                        printf("1. Go to next event.\n");
                        printf("2. Open event in browser.\n");
                        printf("3. Delete the event from your list.\n");
                        printf("4. Exit.\n\n");

                        choice = read_integer("Action > ");

                        switch(choice)
                        {
                        case 1:
                            index++;
                            if(index == events.size())
                                index = 0;
                            break;

                        case 2:
                            system(("librewolf " + events[index].get_link()).c_str());
                            break;
                        
                        case 3:
                            if(!service.check_user_event(events[index]))
                                printf("\nEvent doesn't exist in the list!\n");
                            else
                            {
                                service.remove_user_event(events[index]);
                                printf("\nEvent removed from the list!\nBringing you back to the previous menu...\n");
                                exitedInnerLoop = true;
                            }
                            break;

                        case 4:
                            exitedInnerLoop = true;
                            break;

                        default:
                            printf("\nYou did not input a valid choice, dumbass!\n\n");
                            break;
                        }
                    }
                }
                break;
            }

            case UserMenuChoices::EXPORT_LIST:
                service.export_and_open_list();
                break;

            case UserMenuChoices::EXIT:
                user_mode = false;
                service.set_user("");
                break;

            default:
                printf("\nYou did not input a valid choice, dumbass!\n\n");
                break;
            }
        }
    }
}