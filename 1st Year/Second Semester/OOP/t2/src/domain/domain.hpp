#pragma once

#include <sstream>
#include <iostream>

class Dwelling
{
private:
    double price;
    bool isProfitable;
public:
    double getPrice() { return price; }
    bool profits() { return isProfitable; }

    std::string toString();

    Dwelling(double price, bool isProfitable);
};

class Client
{
protected:
    std::string name;
    double income;
public:
    Client(std::string name, double income);

    double totalIncome();
    virtual std::string toString();
    std::string getName();
    virtual bool isInterested(Dwelling d) { return false; };
};

class Person : public Client
{
public:
    Person(std::string name, double income) : Client(name, income) {};
    bool isInterested(Dwelling d) override;
};

class Company : public Client
{
private:
    double moneyFromInvestments;

public:
    Company(std::string name, double income, double investments) : Client(name, income) { moneyFromInvestments = investments; };

    double totalIncome();
    std::string toString() override;
    bool isInterested(Dwelling d) override;
};