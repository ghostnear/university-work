#pragma once

#include <vector>
#include <fstream>
#include <exception>
#include "domain/interval.hpp"

class Repository
{
private:
    std::vector<WeatherInterval> data;

public:
    std::vector<WeatherInterval> get_data() { return data; }

    void read_from_file(std::string path)
    {
        std::ifstream fin(path);

        if(!fin.is_open())
            throw std::exception();

        int start, end, temperature, precipitationProbability;
        std::string description;

        while(fin>>start>>end>>temperature>>precipitationProbability>>description)
        {
            WeatherInterval input = WeatherInterval(start, end, temperature, precipitationProbability, description);
            data.push_back(input);
        }

        fin.close();
    }
};