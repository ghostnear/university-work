#pragma once

#include <iostream>
#include <sstream>
#include <string>

class WeatherInterval
{
public:
    int startHour, endHour, precipitationProbability, temperature;
    std::string description;

    WeatherInterval(int startHour, int endHour, int temperature, int precipitationProbability, std::string description);

    std::string to_string();
};