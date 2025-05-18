#ifndef ITEM.HPP
#define ITEM.HPP

#include <iostream>

class Item
{
    public:

      virtual void setPrice()= 0 ;
       virtual void setAmount()= 0 ;
       virtual void setName()= 0 ;
       virtual void setPrice(double)=0 ;

};

#endif
