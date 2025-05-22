#ifndef SEASONING_HPP
#define SEASONING_HPP

#include <string>
#include <vector>
#include "Item.hpp"  

class Seasoning : public Item
{
    public:

        Seasoning(std::string name);
        Seasoning(double amount, std::string name, std::string unit, double price);

        void setAmount(double amount, std::string u);
        virtual void setAmount(double amount) override;
        virtual void setPrice(double p) override;
        virtual void setName(const std::string &n) override;

        double getQuantity() const;
        double getPrice() const;
        std::string getName() const;

        friend std::ostream& operator<<(std::ostream& os, const std::vector<Seasoning>& seasonings);
        friend double operator-(std::vector<Seasoning>& seasonings, const Seasoning& s);
        friend void operator+(std::vector<Seasoning>& seasonings, const Seasoning& s);

    private:
    
        double quantity;
        double price;
        std::string name;
        std::string unit;
};

#endif
