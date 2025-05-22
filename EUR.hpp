#ifndef EUR_HPP
#define EUR_HPP

#include <iostream>
#include <stdexcept>
#include "currency.hpp"

class eur : public Currency
{
public:

    eur(double m)
    {
        if(m < 0)
            throw std::invalid_argument("Money must be positive !!!");
        money = m;
        l='E';
    }
    eur() : eur(0.0) {}

    double Change() override
    {
        return money * 1.04;
    }

    double getAmount()const { return money; }

    double Change(double m) { return m / 1.04; }

    double get_inventory()
    {
        std::cout << "Your balance in USD: " << money * 1.04 << std::endl;
        std::cout << "Your balance in IRR: " << money * 93.0 << std::endl;

        return 0;
    }

    void set_money(double m)
    {
        if(m < 0)
            throw std::invalid_argument("Money must be positive !!!");
        money = m;
    }
};

#endif
