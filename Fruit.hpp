#ifndef FRUIT_HPP
#define FRUIT_HPP

#include <string>
#include <vector>

#include "Item.hpp"

class Fruit : public Item
{
    public:

        Fruit(std::string name);
        Fruit(double amount, std::string name, std::string unit, double price);

        void setAmount(double amount, std::string u);
        virtual void setAmount(double amount) override;
        virtual void setPrice(double p) override;
        virtual void setName(const std::string &n) override;

        double getQuantity() const;
        double getPrice() const;
        std::string getName() const;

        friend std::ostream& operator << (std::ostream& os, const std::vector<Fruit>& fruits);
        friend double operator - (std::vector<Fruit>& fruits, const Fruit& f);
        friend void operator + (std::vector<Fruit>& fruits, const Fruit& f);

    private:

        double quantity;
        double price;
        std::string name;
        std::string unit;
};

#endif
