#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <vector>
#include <string>
#include"BankAcount.hpp"
#include "Fruit.hpp"
#include "Snack.hpp"
#include "Seasoning.hpp"

class Ui {
public:
    friend void buy_func(std::vector<Fruit>&customerCartFruit ,std::vector<Snack>&customerCartSnack,std::vector<Seasoning>& customerCartseasoning);
    void add_fanc();

    void run(); 
    void CustomerMenu(); 
    void CashierMenu(); 
    void Customer(); 
    void Cashier(); 
    void displayBalance(BankAccount& account); 
    void loadItems(); 
    void saveItems(); 

private:
    double totalUSD = 0.0;
    std::vector<Fruit> fruits;
    std::vector<Snack> snacks;
    std::vector<Seasoning> seasonings;
    std::vector<BankAccount> accounts;
    
    std::vector<Fruit> customerCartFruit;
    std::vector<Snack> customerCartSnack;
    std::vector<Seasoning> customerCartSeasoning;
};

#endif
