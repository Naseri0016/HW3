#include "Seasoning.hpp"
#include <stdexcept>
#include <iostream>

Seasoning::Seasoning(std::string name)
    : name(name), quantity(0), price(0)
{}

Seasoning::Seasoning(double amount, std::string name, std::string unit, double price)
    : name(name), price(price), unit(unit)
{
    setAmount(amount, unit);
}

void Seasoning::setAmount(double amount, std::string u)
{
    if (amount < 0)
        throw std::invalid_argument("Amount must be positive !!!");

    if(u != "g" && u != "kg")
        throw std::invalid_argument("Unit must be g or kg !!!");
    
    if(u == "g")
    {
        quantity = amount;
        unit = u;
    }
    else if(u == "kg")
    {
        quantity = amount * 1000.0; 
        unit = "g";
    }
}

void Seasoning::setAmount(double amount)
{
    setAmount(amount, "g");
}

void Seasoning::setPrice(double p)
{
    if (p < 0)
        throw std::invalid_argument("Price must be positive!");
    price = p;
}

void Seasoning::setName(const std::string &n)
{
    name = n;
}

double Seasoning::getQuantity() const
{
    return quantity;
}

double Seasoning::getPrice() const
{
    return price;
}

std::string Seasoning::getName() const
{
    return name;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Seasoning>& seasonings)
{
    for (const auto &s : seasonings)
    {
        os << "Seasoning Name: " << s.getName() 
           << ", Price: $" << s.getPrice() 
           << ", Quantity (g): " << s.getQuantity() << "\n";
    }

    return os;
}

double operator-(std::vector<Seasoning>& seasonings, const Seasoning& s)
{
    bool find =true;
    for (auto &seasoning : seasonings)
    {
        if (seasoning.getName() == s.getName())
        {
            find=false;
            
            if (s.getQuantity() <= seasoning.getQuantity())
            {
                seasoning.quantity -= s.getQuantity();

                return (seasoning.getPrice() * (s.getQuantity() -(int)s.getQuantity()/5));
            }
            else
            {
                std::cerr << "There is not enough inventory in the stock !!!\n";
                return 0.0;
            }
        }
    }
    if(find)
    std::cerr << "This seasoning is not among the store's products.\n";
    return 0.0;
}

void operator+(std::vector<Seasoning>& seasonings, const Seasoning& s)
{
    bool found = false;
    for (auto &seasoning : seasonings)
    {
        if (seasoning.getName() == s.getName())
        {
            seasoning.quantity += s.getQuantity(); 
            seasoning.price = s.getPrice();  

            found = true;

            break;
        }
    }

    if (!found)
    {
        seasonings.push_back(s);
    }
}
