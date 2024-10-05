#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <vector>
#include "repository/all.hpp"

class Service
{
private:
    MemoryRepository<Event>* repository;
    MemoryRepository<User>* userRepository;
    MemoryRepository<std::pair<User, Event>> userLists;
    std::size_t userIndex;

public:
    Service(MemoryRepository<Event>* newRepository, MemoryRepository<User>* newUserRepository);
    
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
};

#endif