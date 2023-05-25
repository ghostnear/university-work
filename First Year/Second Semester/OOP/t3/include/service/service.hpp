#pragma once

#include "repository/all.hpp"

class Service
{
private:
    Repository& repository;

    static bool compare_by_interval(WeatherInterval a, WeatherInterval b)
    {
        return a.startHour < b.startHour || (a.startHour == b.startHour && a.endHour < b.endHour);
    }

public:
    Service(Repository& repository) : repository(repository) {}

    std::vector<WeatherInterval> sort_by_interval(std::vector<WeatherInterval> input)
    {
        std::sort(input.begin(), input.end(), Service::compare_by_interval);

        return input;
    }

    std::vector<WeatherInterval> get_all_data_filtered(int parameter)
    {
        auto result = std::vector<WeatherInterval>();
        for(auto data : repository.get_data())
            if(data.precipitationProbability < parameter)
                result.push_back(data);

        return sort_by_interval(result);
    }

    std::vector<WeatherInterval> get_all_data()
    {
        return sort_by_interval(repository.get_data());
    }
};