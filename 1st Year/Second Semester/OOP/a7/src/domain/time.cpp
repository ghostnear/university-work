#include "domain/time.hpp"

Date::Date() { day = month = year = 0; }
Date::Date(std::size_t newDay, std::size_t newMonth, std::size_t newYear)
{
    day = newDay;
    month = newMonth;
    year = newYear;
}

std::string Date::to_string()
{
    std::stringstream result;
    result << day << "." << month << "." << year;
    return result.str();
}

std::ostream &operator<<(std::ostream & output, Date& s)
{
    output << s.get_day() << "\n";
    output << s.get_month() << "\n";
    output << s.get_year();
    return output;
}

std::istream &operator>>(std::istream & input, Date& s)
{
    int inputData;
    input >> inputData;
    s.set_day(inputData);
    input >> inputData;
    s.set_month(inputData);
    input >> inputData;
    s.set_year(inputData);
    return input;
}

Time::Time() { seconds = minutes = hours = 0; }
Time::Time(std::size_t newSeconds, std::size_t newMinutes, std::size_t newHours)
{
    seconds = newSeconds;
    minutes = newMinutes;
    hours = newHours;
}

std::string Time::to_string()
{
    std::stringstream result;
    result << hours << ":" << minutes << ":" << seconds;
    return result.str();
}

std::ostream &operator<<(std::ostream & output, Time& s)
{
    output << s.get_seconds() << "\n";
    output << s.get_minutes() << "\n";
    output << s.get_hours();
    return output;
}

#include <iostream>
std::istream &operator>>(std::istream & input, Time& s)
{
    int inputData;
    input >> inputData;
    s.set_seconds(inputData);
    input >> inputData;
    s.set_minutes(inputData);
    input >> inputData;
    s.set_hours(inputData);
    std::string dummy;
    std::getline(input, dummy);
    return input;
}