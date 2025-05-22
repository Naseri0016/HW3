#ifndef IRR_HPP
#define IRR_HPP

#include <iostream>
#include <stdexcept>

#include "currency.hpp"

class irr : public Currency
{
public:

    irr(double m)
    {
        if(m < 0)
            throw std::invalid_argument("Money must be positive !!!");
        money = m;
        l='R';
    }

    irr() : irr(0.0) {}

    double Change() override
    {
        return money / 85.0;
    }

    double getAmount() const { return money; }

    void get_inventory()
    {
        std::cout << "Your balance in USD: " << money / 85.0 << std::endl;
        std::cout << "Your balance in EUR: " << money / 93.0 << std::endl;
    }

    double Change(double m) { return m * 85.0; } 

    void set_money(double m)
    {
        if(m < 0)
        
            throw std::invalid_argument("Money must be positive!");
        money = m;
    }
};

#endif
