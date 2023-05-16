#include "domain/dynamicarray.hpp"
#include "domain/event.hpp"
#include "repository/memory.hpp"
#include "service/all.hpp"
#include "service/service.hpp"
#include <exception>

Service::Service(MemoryRepository<Event>* newRepository, MemoryRepository<User>* newUserRepository)
{
    repository = newRepository;
    userRepository = newUserRepository;
    userIndex = -1;
}

void Service::add_event(std::string newTitle, std::string newDescription, std::string newLink, Date newDate, Time newTime)
{
    Event event = Event(newTitle, newDescription, newLink, newDate, newTime);
    for(std::size_t index = 0; index < event_count(); index++)
        if(get_event(index) == event)
            throw std::exception();
    repository->add_element(event);
}

DynamicArray<Event> Service::get_events_by_month(std::size_t month)
{
    DynamicArray<Event> result;

    for(std::size_t index = 0; index < repository->get_size(); index++)
        if(repository->get_element(index).get_date().get_month() == month)
            result.add_element(repository->get_element(index));

    return result;
}

void Service::update_event(std::size_t index, std::string newTitle, std::string newDescription, std::string newLink, Date newDate, Time newTime)
{
    if(index >= event_count())
        throw std::exception();

    Event oldEvent = repository->get_element(index);
    oldEvent.set_title(newTitle);
    oldEvent.set_description(newDescription);
    oldEvent.set_link(newLink);
    oldEvent.set_date(newDate);
    oldEvent.set_time(newTime);

    repository->update_element(index, oldEvent);
}

void Service::remove_event(std::size_t index)
{
    if(index >= event_count())
        throw std::exception();
    repository->delete_element(index);
}

std::size_t Service::event_count()
{
    return repository->get_size();
}

DynamicArray<Event> Service::get_events()
{
    DynamicArray<Event> result;
    for(std::size_t index = 0; index < repository->get_size(); index++)
        result.add_element(repository->get_element(index));
    return result;
}

std::string Service::get_user()
{
    if(userIndex == std::size_t(-1))
        return "";

    return userRepository->get_element(userIndex).get_name();
}

void Service::set_user(std::string newUsername)
{
    for(std::size_t index = 0; index < userRepository->get_size(); index++)
        if(userRepository->get_element(index).get_name() == newUsername)
        {
            userIndex = index;
            return;
        }

    User newUser;
    newUser.set_name(newUsername);
    userRepository->add_element(newUser);
    userIndex = userRepository->get_size() - 1;
}

void Service::remove_user_event(Event whatEvent)
{
    if(userIndex == std::size_t(-1))
        return;

    for(std::size_t index = 0; index < userLists.get_size(); index++)
        if(userLists.get_element(index).first.get_name() == get_user() && userLists.get_element(index).second == whatEvent)
        {
            userLists.delete_element(index);

            for(std::size_t index = 0; index < repository->get_size(); index++)
                if(whatEvent == repository->get_element(index))
                    repository->get_element(index).decrement_participant_count();

            return;
        }
}

void Service::add_user_event(Event whatEvent)
{
    if(userIndex == std::size_t(-1))
        return;

    userLists.add_element(std::make_pair(userRepository->get_element(userIndex), whatEvent));

    for(std::size_t index = 0; index < repository->get_size(); index++)
        if(whatEvent == repository->get_element(index))
            repository->get_element(index).increment_participant_count();
}

bool Service::check_user_event(Event whatEvent)
{
    if(userIndex == std::size_t(-1))
        return false;

    for(std::size_t index = 0; index < userLists.get_size(); index++)
        if(userLists.get_element(index).first.get_name() == get_user() && userLists.get_element(index).second == whatEvent)
            return true;
    return false;
}

DynamicArray<Event> Service::get_user_events()
{
    DynamicArray<Event> result;

    if(userIndex == std::size_t(-1))
        return result;

    for(std::size_t index = 0; index < userLists.get_size(); index++)
        if(userLists.get_element(index).first.get_name() == get_user())
            for(std::size_t elementIndex = 0; elementIndex < repository->get_size(); elementIndex++)
                if(repository->get_element(elementIndex) == userLists.get_element(index).second)
                    result.add_element(repository->get_element(elementIndex));

    return result;
}

Event Service::get_event(std::size_t index)
{
    return repository->get_element(index);
}