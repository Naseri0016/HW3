#ifndef USD_HPP
#define USD_HPP
#include<iostream>
#include"currency.hpp"
class usd : public Currency
{
    public:

    usd(double m);
    usd(){}
    double Change();
    double Change(double);

    double get_Inventory();
};
#endif