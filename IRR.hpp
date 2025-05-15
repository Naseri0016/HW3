#ifndef IRR_HPP
#define IRR_HPP
#include<iostream>
#include"currency.hpp"

class irr : public Currency
{

    public :

        irr(double);
        irr(){};


        double Change();
        void get_inventory();
        double Change(double);


};
#endif
