#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <string>
#include <sstream>

template<class ElementType>
std::string integer_to_string(ElementType input)
{
    std::stringstream result;
    result << input;
    return result.str();
}

struct Address
{
    double longitude;
    double latitude;

    std::string to_string();

    bool operator==(Address& otherAddress)
    {
        return this->longitude == otherAddress.longitude && this->latitude == otherAddress.latitude;
    }
};

struct Date
{
    int day;
    int month;
    int year;
    
    std::string to_string();
};

class School
{
private:
    std::string name;
    Address address;
    Date dateOfVisit;
    bool visited;

public:
    School(std::string name = "", Address address = {0, 0}, Date dateOfVisit = {1, 1, 1970});
    std::string to_string();

    bool operator==(School otherSchool)
    {
        return this->name == otherSchool.name && this->address == otherSchool.address;
    }

    bool operator<(School otherSchool)
    {
        return this->name < otherSchool.name;
    }
};

#endif