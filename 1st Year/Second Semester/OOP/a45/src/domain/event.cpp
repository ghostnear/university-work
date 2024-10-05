#include "domain/event.hpp"
#include <sstream>

Event::Event()
{
    title = "<unnamed>";
    description = "<empty>";
    link = "localhost";
    peopleCount = 0;

    // Unix epoch.
    date = Date(1, 1, 1970);
    time = Time(0, 0, 0);
}

Event::Event(std::string newTitle, std::string newDescription, std::string newLink, Date newDate, Time newTime)
{
    title = newTitle;
    description = newDescription;
    link = newLink;
    peopleCount = 0;
    date = newDate;
    time = newTime;
}

bool Event::operator==(const Event& event)
{
    return event.title == title && event.link == link && event.description == description;
}

Event::Event(const Event& event)
{
    title = event.title;
    description = event.description;
    link = event.link;
    peopleCount = event.peopleCount;
    date = event.date;
    time = event.time;
}

std::string Event::to_string()
{
    std::stringstream result;
    result << "Title: " << title << "\n";
    result << "Description: " << description << "\n";
    result << "Interested people: " << peopleCount << "\n";
    result << "Date: " << date.to_string() << " " << time.to_string() << "\n";
    result << "Link: " << link << "\n";

    return result.str();
}