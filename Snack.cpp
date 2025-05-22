#include "Snack.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

Snack::Snack(string name)
    : name(name), quantity(0), price(0)
{}

Snack::Snack(int amount, string name, double price)
    : name(name), quantity(amount), price(price)
{
    if (amount < 0)
        throw invalid_argument("Quantity must be non-negative!");

    if (price < 0)
        throw invalid_argument("Price must be non-negative!");
}

void Snack::setAmount(double amt)
{
    if (amt < 0)
        throw invalid_argument("Quantity must be non-negative!");

    quantity = static_cast<int>(amt);
}

void Snack::setPrice(double p)
{
    if (p < 0)
        throw invalid_argument("Price must be non-negative!");
    price = p;
}

void Snack::setName(const string &n)
{
    name = n;
}

int Snack::getQuantity() const
{
    return quantity;
}

double Snack::getPrice() const
{
    return price;
}

string Snack::getName() const
{
    return name;
}


ostream& operator<<(ostream &os, const vector<Snack>& snacks)
{
    for (const auto &snack : snacks)
    {
        os << "Snack Name: " << snack.getName()
           << ", Price: " << snack.getPrice()
           << ", Quantity: " << snack.getQuantity() << "\n";
    }

    return os;
}

double operator-(vector<Snack>& snacks, const Snack &s)
{
    bool find = true;
    for (auto &snack : snacks)
    {
        if (snack.getName() == s.getName())
        {
            find=false;
            if (s.getQuantity() <= snack.getQuantity())
            {
                snack.quantity -= s.getQuantity();

                return (snack.getPrice() * (s.getQuantity()-s.getQuantity()/5));
            }
            else
            {
                cerr << "There is not enough inventory in the stock !\n";
                return 0.0;
            }
        }
    }

    if(find)
    
    cerr << "This snack is not among the store's products.\n";
    return 0.0;
}

double operator+(vector<Snack>& snacks, const Snack &s)
{
    for (auto &snack : snacks) 
    {
        if (snack.getName() == s.getName())
        {
            snack.quantity += s.getQuantity();  
            snack.price = s.getPrice();           
            return snack.getPrice() * s.getQuantity();
        }
    }

    snacks.push_back(s);
    return s.getPrice() * s.getQuantity();
}
