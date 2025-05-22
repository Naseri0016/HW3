#include "Fruit.hpp"
#include <stdexcept>
#include <iostream>

Fruit::Fruit(std::string name)
    : name(name), quantity(0), price(0), unit("kg")
{}

Fruit::Fruit(double amount, std::string name, std::string unit, double price)
    : name(name), price(price), unit(unit)
{
    setAmount(amount, unit);
}

void Fruit::setAmount(double amount, std::string u)
{
    if (amount < 0)
        throw std::invalid_argument("Amount must be positive!!!");

    if (u != "kg" && u != "g" && u != "ton")
        throw std::invalid_argument("Unit must be kg, g, or ton !!!");

    if (u == "kg")
    {
        quantity = amount;
        unit = u;
    }
    else if (u == "g")
    {
        quantity = amount / 1000.0;
        unit = "kg";
    }
    else if (u == "ton")
    {
        quantity = amount * 1000.0;
        unit = "kg";
    }
}

void Fruit::setAmount(double amount)
{
    setAmount(amount, "kg");
}

void Fruit::setPrice(double p)
{
    if (p < 0)
        throw std::invalid_argument("Price must be positive!");
    price = p;
}

void Fruit::setName(const std::string &n)
{
    name = n;
}

double Fruit::getQuantity() const
{
    return quantity;
}

double Fruit::getPrice() const
{
    return price;
}

std::string Fruit::getName() const
{
    return name;
}


std::ostream& operator<<(std::ostream& os, const std::vector<Fruit>& fruits)
{
    for (const auto & fruit : fruits)
    {
        os << "Fruit Name: " << fruit.getName() 
           << ", Price: $" << fruit.getPrice() 
           << ", Quantity (kg): " << fruit.getQuantity() << "\n";
    }

    return os;
}

double operator-(std::vector<Fruit>& fruits, const Fruit& f1)
{
    bool find=true;
    for (auto & fruit : fruits)
    {
        
        if (fruit.getName() == f1.getName())
        {
            find=false;

            if (f1.getQuantity() <= fruit.getQuantity())
            {
                fruit.quantity -= f1.getQuantity();
                return (fruit.getPrice() * (f1.getQuantity()-(int)f1.getQuantity()/5));
            }
            else
            {
                std::cerr << "Insufficient inventory!\n";
                return 0.0;
            }
        }
    }
    if(find)
    std::cerr << "Item not found !!!\n";

    return 0.0;
}

void operator+(std::vector<Fruit>& fruits, const Fruit& f1)
{
    bool found = false;
    for (auto & fruit : fruits)
    {
        if (fruit.getName() == f1.getName())
        {
            fruit.quantity += f1.getQuantity();
            fruit.price = f1.getPrice();
            found = true;
            
            break;
        }
    }
    if (!found)
    {
        fruits.push_back(f1);
    }
}
