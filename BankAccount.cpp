#include"BankAcount.hpp"
#include <fstream>
#include <limits>
#include <stdexcept>

using namespace std;
using namespace chrono;

chrono::system_clock::time_point BankAccount::my_time = chrono::system_clock::now();

BankAccount::BankAccount(unsigned int serial, const irr &i, double m, time_t t)
    : Rial(i), Serialnum(serial), mahdod(m), my_mahdod(0), accountTime(t), label('R') {}

BankAccount::BankAccount(unsigned int serial, const usd &u, double m, time_t t)
    : Dollar(u), Serialnum(serial), mahdod(m), my_mahdod(0), accountTime(t), label('D') {}

BankAccount::BankAccount(unsigned int serial, const eur &e, double m, time_t t)
    : Euro(e), Serialnum(serial), mahdod(m), my_mahdod(0), accountTime(t), label('E') {}

BankAccount::BankAccount(int s, double my_money, double m, time_t t)
    : Serialnum(s), my_money(my_money), my_mahdod(m) {
    my_time = chrono::system_clock::from_time_t(t);
}


void BankAccount::limitAccount(unsigned int s) {
    auto now = system_clock::now();
    auto now_time_t = system_clock::to_time_t(now);
    tm now_tm = *localtime(&now_time_t);
    
    now_tm.tm_hour = 0;
    now_tm.tm_min = 0;
    now_tm.tm_sec = 0;

    auto midnight_tp = system_clock::from_time_t(mktime(&now_tm));

    if (s == 0) {
        my_time = midnight_tp;
        my_mahdod = 10000.0;
    } else {
        accountTime = system_clock::to_time_t(midnight_tp);
        mahdod = 1000.0;
    }
}

void BankAccount::transaction(double price, BankAccount* cashiers) {
    try {
        if (!cashiers) { 
            throw runtime_error("Invalid cashier pointer!");
        }

        if (price + mahdod > 1000.0)
            throw invalid_argument("Your transactions were limited!");
        if (price + cashiers->my_mahdod > 10000.0)
            throw invalid_argument("Shopping account was limited!");

        double priceInAccountCurrency = 0;
        switch (label) {
            case 'R':{
                if(Rial.getAmount()>=Rial.Change(price))
                priceInAccountCurrency = Rial.Change(price);
                else{
                    throw runtime_error("Insufficient wallet balance!");
                }
            }
                break;
            case 'D':{ 
                if(Dollar.getAmount()>=Dollar.Change(price))
                priceInAccountCurrency = Dollar.Change(price);
                else{
                    throw runtime_error("Insufficient wallet balance!");
                }
            }
                break;
            case 'E':{ 
                if(Euro.getAmount()>=Euro.Change(price))
                priceInAccountCurrency = Euro.Change(price);
                else{
                    throw runtime_error("Insufficient wallet balance!");
                }
            }                
            break;
            default:
                throw invalid_argument("Unknown currency type!");
        }

        try {
            cashiers->my_money += price;
            switch (label) {
                case 'R': Rial.set_money(Rial.getAmount() -Rial.Change(price)); break;
                case 'D': Dollar.set_money(Dollar.getAmount() - price); break;
                case 'E': Euro.set_money(Euro.getAmount() -Euro.Change( price) ); break;
            }
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }

        mahdod += priceInAccountCurrency;
        if (mahdod > 1000.0) limitAccount(Serialnum);

        cashiers->my_mahdod += price;
        if (cashiers->my_mahdod >= 10000.0) limitAccount(0);
    } catch (const exception& ex) {
        cerr << "Transaction Error: " << ex.what() << endl;
    }
}


void BankAccount::SetFile(vector<BankAccount>& accounts) {
    ofstream outFile("bank_accounts.txt", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }

    for (auto& account : accounts) {
        time_t accountLimitTime = account.accountTime;

        tm midnight_tm = *localtime(&accountLimitTime);
        midnight_tm.tm_hour = 0;
        midnight_tm.tm_min = 0;
        midnight_tm.tm_sec = 0;
        accountLimitTime = mktime(&midnight_tm);

        if (account.getSerialnum() == 0) {
            account.my_time = chrono::system_clock::now();
            time_t t_my_time = chrono::system_clock::to_time_t(account.my_time);
            outFile << 0 << " " << account.my_money << " " << account.my_mahdod << " " << t_my_time << endl;
        } else {
            account.accountTime = accountLimitTime;

            outFile << account.Serialnum << " " << account.label << " ";
            switch (account.label) {
                case 'R': outFile << account.Rial.getAmount(); break;
                case 'D': outFile << account.Dollar.getAmount(); break;
                case 'E': outFile << account.Euro.getAmount(); break;
            }
            outFile << " " << account.mahdod << " " << account.accountTime << endl;
        }
    }

    outFile.close();
}

void BankAccount::LoadFile(vector<BankAccount>& accounts) {
   ifstream inFile("bank_accounts.txt");
    if (!inFile.is_open()) {
        cerr << "Error: Could not open file for reading!" << endl;
        return;
    }

    accounts.clear();
    auto now = chrono::system_clock::now();
   time_t  current_time = chrono::system_clock::to_time_t(now);

    unsigned int shop_serial;
    double shop_money, shop_mahdod;
    time_t shop_time;

    if (!(inFile >> shop_serial >> shop_money >> shop_mahdod >> shop_time)) {
        cerr << "Error: Could not read shop account data!" << endl;
        inFile.close();
        return;
    }

    if (current_time > shop_time) {
        shop_mahdod = 0.0; 
    }

    accounts.emplace_back(BankAccount(shop_serial, shop_money, shop_mahdod, shop_time));

    unsigned int serial;
    char currencyType;
    double amount, mahdod;
    time_t acc_time;

    while (inFile >> serial >> currencyType >> amount >> mahdod >> acc_time) {
        tm midnight_tm = *localtime(&acc_time);
        midnight_tm.tm_hour = 0;
        midnight_tm.tm_min = 0;
        midnight_tm.tm_sec = 0;
        time_t midnight_time = mktime(&midnight_tm);

        if (current_time > midnight_time) {
            mahdod=0.0;
        }

        switch (currencyType) {
            case 'R':
                accounts.emplace_back(BankAccount(serial, irr(amount), mahdod, acc_time));
                break;
            case 'D':
                accounts.emplace_back(BankAccount(serial, usd(amount), mahdod, acc_time));
                break;
            case 'E':
                accounts.emplace_back(BankAccount(serial, eur(amount), mahdod, acc_time));
                break;
            default:
              cerr << "Warning: Unknown currency type '" << currencyType << "', skipping entry." << endl;
                break;
        }
    }

    inFile.close();
}
