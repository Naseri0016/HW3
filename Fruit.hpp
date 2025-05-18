#ifndef FRUIT.HPP
#define FRUIT.HPP

#include <iostream>
#include <vector>

#include "Item.hpp"

class  Fruit : public Item
{

    public:
        
        Fruit ( std :: string name ) ;
        Fruit (double amount , std :: string name , std :: string unit  , double price ) ;


        void setAmount(double , std :: string) ;
        void setPrice(double) ;

       friend double operator - (std :: vector <Fruit> &list ,Fruit a1 ) ;
       friend double operator + (std :: vector <Fruit > &list  , Fruit a1) ; 
       

        private :
                
            double quantity ; // amount of item
            double price ;
            std :: string name ;
            std :: string unit;




};

#endif