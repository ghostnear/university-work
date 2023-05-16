#pragma once

#include "domain/time.hpp"
#include "time.h"
#include <string>

class Event
{
private:
    std::string title, description, link;
    std::size_t peopleCount;
    Date date;
    Time time;

public:
    Event();
    Event(const Event& event);
    Event(std::string newTitle, std::string newDescription, std::string newLink, Date newDate, Time newTime);

    bool operator==(const Event& event);

    void set_title(std::string newTitle) { title = newTitle; }
    void set_link(std::string newLink) { link = newLink; }
    void set_description(std::string newDescription) { description = newDescription; }
    void set_date(Date newDate) { date = newDate; }
    void set_time(Time newTime) { time = newTime; }

    std::string get_link() { return link; }
    std::string get_title() { return title; }
    std::string get_description() { return description; }
    Date get_date() { return date; }
    Time get_time() { return time; }

    void increment_participant_count() { peopleCount++; }
    void decrement_participant_count() { peopleCount--; }

    std::string to_string();
};

std::ostream &operator<<(std::ostream & output, Event& s);
std::istream &operator>>(std::istream & input, Event& s);