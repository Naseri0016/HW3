#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <stdexcept>
#include "USD.hpp"
#include "IRR.hpp"
#include "EUR.hpp"

// ساختار نگهداری محدودیت‌ها
struct limit {
    time_t time;
    double mahdod;
};

class BankAccount {
public:
    // سازنده‌های مختلف بر اساس نوع حساب (ریال، دلار، یورو، فروشگاه)
    BankAccount(unsigned int serial, const irr &i, double m, time_t t);
    BankAccount(unsigned int serial, const usd &u, double m, time_t t);
    BankAccount(unsigned int serial, const eur &e, double m, time_t t);
    BankAccount(int s, double my_money, double m, time_t t);
    BankAccount(){};

    unsigned int getSerialnum() const { return Serialnum; }
    char getLabel() const { return label; }
    irr getRial() const { return Rial; }
    usd getDollar() const { return Dollar; }
    eur getEuro() const { return Euro; }
    double get_my_money() const { return my_money; }

    void limitAccount(unsigned int s);

    void transaction(double price , BankAccount * cashiers); 

    static void SetFile( std::vector<BankAccount>& accounts);
    static void LoadFile(std::vector<BankAccount>& accounts);
private:
    irr Rial;
    usd Dollar;
    eur Euro;

    char label;                
    time_t accountTime;        
    double mahdod;             
     double my_mahdod;
    double my_money;
    
    static std::chrono::system_clock::time_point my_time;

    unsigned int Serialnum;    
};

#endif
