#ifndef EUR_HPP
#define EUR_HPP
#include<iostream>
#include"currency.hpp"

class eur : public Currency
{

    public :

        eur(double);
        eur(){}

        double Change();
        double Change(double);
        double get_inventory();

}; 

#endif