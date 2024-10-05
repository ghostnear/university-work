#pragma once

#include <vector>
#include <fstream>
#include "../domain/domain.hpp"

class RealEstateAgency
{
private:
    std::vector<Person> people;
    std::vector<Company> companies;
    std::vector<Dwelling> dwellings;

public:
    RealEstateAgency();

    Dwelling& addDwelling(double price, bool isProfitable);
    void removeClient(std::string name);
    std::vector<Dwelling> getAllDwellings();
    std::vector<Client> getAllClients();
    std::vector<Client> getInterestedClients(Dwelling d);
    void writeToFile(std::string fileName);
};