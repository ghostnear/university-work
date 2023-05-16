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