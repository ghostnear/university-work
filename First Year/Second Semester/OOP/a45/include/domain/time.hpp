#ifndef DOMAIN_TIME_HPP
#define DOMAIN_TIME_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <sstream>

class Date
{
private:
    std::size_t day, month, year;

public:
    // Constructors.
    Date();
    Date(std::size_t newDay, std::size_t newMonth, std::size_t newYear);

    std::size_t get_month() { return month; }

    std::string to_string();
};

class Time
{
private:
    std::size_t seconds, minutes, hours;

public:
    // Constructors.
    Time();
    Time(std::size_t newSeconds, std::size_t newMinutes, std::size_t newHours);

    std::string to_string();
};

#endif