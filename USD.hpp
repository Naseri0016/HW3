#ifndef USD_HPP
#define USD_HPP

#include <iostream>
#include <stdexcept>
#include"currency.hpp"

class usd : public Currency
{
public:

    usd(double m)
    {
        if(m < 0)
            throw std::invalid_argument("Money must be positive !!!");
        money = m;
    }
    usd() : usd(0.0) {} 
       
    double Change() override
    {
        
        return money;
        l='D';
    }

    double getAmount() const { return money; }

    double Change(double m) { return m; }

    void set_money(double m)
    {
        if(m < 0)

            throw std::invalid_argument("Money must be positive !!!");
        money = m;
    }

    double getInventory() { return money; } 
};

#endif
