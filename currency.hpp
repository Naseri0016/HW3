#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <iostream>
#include <stdexcept>

class Currency {
public:
    virtual double Change() = 0;
    virtual ~Currency() {}
protected:
    double money;
    char l;
};

#endif
