#include "domain.hpp"

Dwelling::Dwelling(double price, bool isProfitable)
{
    this->price = price;
    this->isProfitable = isProfitable;
}

std::string Dwelling::toString()
{
    std::string result;
    result += "Dwelling price: ";
    result += std::to_string(price);
    result += "\nIs profitable?: ";
    result += std::to_string(isProfitable);
    return result;
}

std::string Client::toString()
{
    std::string result;
    result += "Client name: ";
    result += name;
    result += "\nClient income: ";
    result += std::to_string(income);
    return result;
}

Client::Client(std::string name, double income)
{
    this->name = name;
    this->income = income;
}

double Client::totalIncome()
{
    return income;
}

std::string Client::getName()
{
    return name;
}

double Company::totalIncome()
{
    return moneyFromInvestments + Client::totalIncome();
}

bool Person::isInterested(Dwelling d)
{
    return (d.getPrice() / 1000 <= totalIncome()); 
}

bool Company::isInterested(Dwelling d)
{
    return (d.getPrice() / 100 <= totalIncome() && d.profits()); 
}

std::string Company::toString()
{
    std::string result;
    result += Client::toString();
    result += "\nClient income from investments: ";
    result += std::to_string(moneyFromInvestments);
    return result;
}