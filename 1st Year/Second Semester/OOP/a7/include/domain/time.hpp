#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <sstream>

#include "exception.hpp"

class Date
{
private:
    std::size_t day, month, year;

public:
    // Constructors.
    Date();
    Date(std::size_t newDay, std::size_t newMonth, std::size_t newYear);

    std::size_t get_day() { return day; }
    std::size_t get_month() { return month; }
    std::size_t get_year() { return year; }

    void set_day(std::size_t newDay) { day = newDay; }
    void set_month(std::size_t newMonth) { month = newMonth; }
    void set_year(std::size_t newYear) { year = newYear; }

    std::string to_string();
};

std::ostream &operator<<(std::ostream & output, Date& s);
std::istream &operator>>(std::istream & input, Date& s);

class DateValidator
{
public:
    static void validate(Date date)
    {
        if(date.get_day() >= 1 && date.get_day() <= 31 &&
               date.get_month() >= 1 && date.get_month() <= 12 &&
               date.get_year() >= 1)
            throw CustomException();
    }
};

class Time
{
private:
    std::size_t seconds, minutes, hours;

public:
    // Constructors.
    Time();
    Time(std::size_t newSeconds, std::size_t newMinutes, std::size_t newHours);

    std::size_t get_seconds() { return seconds; }
    std::size_t get_minutes() { return minutes; }
    std::size_t get_hours() { return hours; }

    void set_seconds(std::size_t newSeconds) { seconds = newSeconds; }
    void set_minutes(std::size_t newMinutes) { minutes = newMinutes; }
    void set_hours(std::size_t newHours) { hours = newHours; }

    std::string to_string();
};

std::ostream &operator<<(std::ostream & output, Time& s);
std::istream &operator>>(std::istream & input, Time& s);

class TimeValidator
{
public:
    static void validate(Time time)
    {
        if(time.get_seconds() >= 0 && time.get_seconds() <= 59 &&
               time.get_minutes() >= 0 && time.get_minutes() <= 59 &&
               time.get_hours() >= 0 && time.get_hours() <= 23)
            throw CustomException();
    }
};