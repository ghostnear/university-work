#include "domain/interval.hpp"

WeatherInterval::WeatherInterval(int startHour, int endHour, int temperature, int precipitationProbability, std::string description)
{
    this->startHour = startHour;
    this->endHour = endHour;
    this->temperature = temperature;
    this->description = description;
    this->precipitationProbability = precipitationProbability;
}

std::string WeatherInterval::to_string()
{
    std::ostringstream result;
    result << this->startHour;
    result << "-";
    result << this->endHour;
    result << " ";
    result << this->temperature;
    result << "C ";
    result << this->precipitationProbability;
    result << "% ";
    result << this->description;
    return  result.str();
}