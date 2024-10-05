#include "service.hpp"

RealEstateAgency::RealEstateAgency()
{
    people.push_back(
        Person(
            "Georgel",
            1000
        )
    );

    people.push_back(
        Person(
            "Marcel",
            10000
        )
    );

    companies.push_back(
        Company(
            "Evil_Inc",
            10000,
            20000
        )
    );

    companies.push_back(
        Company(
            "Marcel_corp",
            30000,
            10000
        )
    );

    addDwelling(
        1,
        true
    );
}

Dwelling& RealEstateAgency::addDwelling(double price, bool isProfitable)
{
    dwellings.push_back(
        Dwelling(
            price,
            isProfitable
        )
    );
    return dwellings.back();
}

void RealEstateAgency::removeClient(std::string name)
{
    int index = 0;
    int size = people.size();
    for(index = 0; index < size; index++)
    {
        if(people[index].getName() == name)
        {
            people.erase(people.begin() + index);
            return;
        }
    }

    size = companies.size();
    for(index = 0; index < size; index++)
    {
        if(companies[index].getName() == name)
        {
            companies.erase(companies.begin() + index);
            return;
        }
    }
}

std::vector<Dwelling> RealEstateAgency::getAllDwellings()
{
    return dwellings;
}

std::vector<Client> RealEstateAgency::getAllClients()
{
    std::vector<Client> result;
    for(auto client : people)
        result.push_back(client);

    for(auto client : companies)
        result.push_back(client);

    return result;
}

std::vector<Client> RealEstateAgency::getInterestedClients(Dwelling d)
{
    std::vector<Client> result;
    for(auto client : people)
        if(client.isInterested(d))
            result.push_back(client);

    for(auto client : companies)
        if(client.isInterested(d))
            result.push_back(client);

    return result;
}

void RealEstateAgency::writeToFile(std::string fileName)
{
    std::ofstream fout(fileName);
    for(Person client : people)
        fout << client.toString() << "\n";
    for(Company client : companies)
        fout << client.toString() << "\n";
    fout.close();
}