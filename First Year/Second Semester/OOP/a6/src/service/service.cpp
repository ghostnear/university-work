#include "domain/event.hpp"
#include "repository/memory.hpp"
#include "service/all.hpp"
#include "service/service.hpp"
#include <exception>
#include <algorithm>

Service::Service(MemoryRepository<Event>* newRepository, MemoryRepository<User>* newUserRepository)
{
    repository = newRepository;
    userRepository = newUserRepository;
    userIndex = -1;
}

void Service::add_event(std::string newTitle, std::string newDescription, std::string newLink, Date newDate, Time newTime)
{
    Event event = Event(newTitle, newDescription, newLink, newDate, newTime);
    std::vector<Event> data = repository->get_data();

    // If element already exists, cry about it.
    if(std::find(data.begin(), data.end(), event) != data.end())
        throw std::exception();
            
    repository->add_element(event);
}

std::vector<Event> Service::get_events_by_month(std::size_t month)
{
    std::vector<Event> result;
    std::vector<Event> source = repository->get_data();

    std::copy_if(
        source.begin(), source.end(),
        std::back_inserter(result),
        [month](Event x) { return x.get_date().get_month() == month; }
    );

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

std::vector<Event> Service::get_events()
{
    return repository->get_data();
}

std::string Service::get_user()
{
    if(userIndex == std::size_t(-1))
        return "";

    return userRepository->get_element(userIndex).get_name();
}

void Service::set_user(std::string newUsername)
{
    if(newUsername == "")
    {
        userIndex = -1;
        return;
    }

    // Range based loop not required as we don't send stuff as references.
    std::size_t index = 0;
    for(auto user : userRepository->get_data())
    {
        if(user.get_name() == newUsername)
        {
            userIndex = index;
            return;
        }
        index++;
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

    // Range based loop not required as we don't send stuff as references.
    std::size_t index = 0;
    for(auto user : userLists.get_data())
    {
        if(user.first.get_name() == get_user() && user.second == whatEvent)
        {
            userLists.delete_element(index);

            for(std::size_t eventIndex = 0; eventIndex < repository->get_size(); eventIndex++)
                if(whatEvent == repository->get_element(eventIndex))
                    repository->get_element(eventIndex).decrement_participant_count();

            return;
        }
        index++;
    }
}

void Service::add_user_event(Event whatEvent)
{
    if(userIndex == std::size_t(-1))
        return;

    userLists.add_element(std::make_pair(userRepository->get_element(userIndex), whatEvent));
    
    // Range based loop not required as we don't send stuff as references.
    for(std::size_t index = 0; index < repository->get_size(); index++)
        if(whatEvent == repository->get_element(index))
            repository->get_element(index).increment_participant_count();
}

bool Service::check_user_event(Event whatEvent)
{
    if(userIndex == std::size_t(-1))
        return false;

    for(auto listLink : userLists.get_data())
        if(listLink.first.get_name() == get_user() && listLink.second == whatEvent)
            return true;

    return false;
}

std::vector<Event> Service::get_user_events()
{
    std::vector<Event> result;

    if(userIndex == std::size_t(-1))
        return result;

    for(auto listLink : userLists.get_data())
        if(listLink.first.get_name() == get_user())
            for(auto event : repository->get_data())
                if(event == listLink.second)
                    result.push_back(event);

    return result;
} /* LCOV_EXCL_LINE */

Event Service::get_event(std::size_t index)
{
    return repository->get_element(index);
}