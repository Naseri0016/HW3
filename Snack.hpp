#ifndef SNACK_HPP
#define SNACK_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Item.hpp"  

class Snack : public Item
{
    public:

        Snack(std::string name);
        Snack(int amount, std::string name, double price);

        virtual void setAmount(double amt) override;
        virtual void setPrice(double p) override;
        virtual void setName(const std::string &n) override;

        int getQuantity() const;
        double getPrice() const;
        std::string getName() const;

        friend std::ostream& operator<<(std::ostream &os, const std::vector<Snack>& snacks);
        friend double operator-(std::vector<Snack>& snacks, const Snack &s);
        friend double operator+(std::vector<Snack>& snacks, const Snack &s);

    private:
    
        std::string name;
        int quantity;
        double price;
};

#endif
