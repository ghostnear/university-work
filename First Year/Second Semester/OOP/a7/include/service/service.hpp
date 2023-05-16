#pragma once

#include <vector>
#include "repository/all.hpp"

enum ExportType
{
    Memory,
    CSV,
    HTML
};

class Service
{
private:
    Repository<Event>& repository;
    Repository<User>& userRepository;
    ExportType outputType;
    MemoryRepository<std::pair<User, Event>> userLists;
    std::size_t userIndex;

public:
    Service(Repository<Event>& newRepository, Repository<User>& newUserRepository, ExportType repositoryType) : repository(newRepository), userRepository(newUserRepository)
    {
        userIndex = -1;
        this->outputType = repositoryType;
    }
    
    void add_event(std::string newTitle, std::string newDescription, std::string newLink, Date newDate, Time newTime);
    void update_event(std::size_t index, std::string newTitle, std::string newDescription, std::string newLink, Date newDate, Time newTime);
    void remove_event(std::size_t index);

    std::size_t event_count();

    Event get_event(std::size_t index);
    std::vector<Event> get_events();

    std::string get_user();
    void set_user(std::string newUsername);

    std::vector<Event> get_events_by_month(std::size_t month);

    std::vector<Event> get_user_events();
    void add_user_event(Event whatEvent);
    bool check_user_event(Event whatEvent);
    void remove_user_event(Event whatEvent);

    void export_and_open_list();
};