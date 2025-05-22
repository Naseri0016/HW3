#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item
{
    public:
    
        virtual void setPrice(double price) = 0;
        virtual void setAmount(double amount) = 0;
        virtual void setName(const std::string &name) = 0;
        virtual ~Item() {}
};

#endif
