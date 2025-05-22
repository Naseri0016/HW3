#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include "USD.hpp"
#include "IRR.hpp"
#include "EUR.hpp"
#include "Item.hpp"
#include"BankAcount.hpp"
#include "Fruit.hpp"
#include "Snack.hpp"
#include "Seasoning.hpp"
#include "Ui.hpp"

using namespace std;


void buy_func(vector<Fruit>&customerCartFruit , vector<Snack>&customerCartSnack,vector<Seasoning>& customerCartseasoning){
    string type, name, unit;
    double quantity;

    cout << "Enter item type (f for Fruit, s for Snack, a for Seasoning): ";
    cin >> type;
    cout << "Enter item name: ";
    cin >> name;
    cout << "Enter quantity: ";
    cin >> quantity;

    if (type == "f") {
        cout << "Enter unit (kg/g/ton): ";
        cin >> unit;
        customerCartFruit.emplace_back(quantity, name, unit, 0);
    } else if (type == "s") {
        customerCartSnack.emplace_back(static_cast<int>(quantity), name, 0);
    } else if (type == "a") {
        cout << "Enter unit (kg/g): ";
        cin >> unit;
        customerCartseasoning.emplace_back(quantity, name, unit, 0);
    } else {
    cout << "Invalid item type!\n";
    cout<<"do you like continue if yes enter 1\n";
    int c;
    cin>>c;
    if(c==1){
        buy_func(customerCartFruit , customerCartSnack ,customerCartseasoning );
    }
    else{
        return;
    }
    }
    cout<<"do you like continue if yes enter 1\n";
    int c;
    cin>>c;
    if(c==1){
        buy_func(customerCartFruit , customerCartSnack ,customerCartseasoning );
    }
    else{
        return;
    }

}

void Ui::add_fanc(){
    char type; 
    string name, unit;
    double quantity, price;
    cout << "Enter item type (f for Fruit, s for Snack, a for Seasoning): ";
    cin >> type;
    cout << "Enter item name: ";
    cin >> name;
    cout << "Enter quantity: ";
    cin >> quantity;
    cout << "Enter price: ";
    cin >> price;
    switch (type)
    {
        case 'f':
     {
        cout << "Enter unit (kg/g/ton): ";
        cin >> unit;
        Fruit f(quantity , name , unit , price);
        fruits+f;
        break;
    }  case 's': {
        Snack s(static_cast<int>(quantity), name, price);
        snacks+s;
        break;
    } case 'a': {
        cout << "Enter unit (kg/g): ";
        cin >> unit;
        Seasoning a(quantity, name, unit, price);
        seasonings+a;
        break;
    } default:{
        cout << "Invalid item type!\n";
        cout<<"do you like continue if yes enter 1\n";
        int c;
        cin>>c;
        if(c==1){
            add_fanc();
        }
        else{
            return;
        }
    }
    break;
}
    cout << "Item added to inventory successfully!\n";
    cout<<"do you like continue if yes enter 1\n";
    int c;
    cin>>c;
    if(c==1){
        add_fanc();
    }
    else{
        return;
    }

}

void processFile(const string &filename, vector<Fruit> &fruits, vector<Snack> &snacks, vector<Seasoning> &seasonings) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << "\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        char type;
        string name;
        double price, amount;
        if (!(iss >> type))
            continue;
        if (!(iss >> name >> price >> amount))
            continue;
        switch (type) {
            case 'f':
                fruits.emplace_back(amount, name, "kg", price);
                break;
            case 's':
                snacks.emplace_back(static_cast<int>(amount), name, price);
                break;
            case 'a':
                seasonings.emplace_back(amount, name, "g", price);
                break;
            default:
                cerr << "Undefined type: " << type << "\n";
                break;
        }
    }
    file.close();
}

void writeFile(const string &filename, const vector<Fruit> &fruits, const vector<Snack> &snacks, const vector<Seasoning> &seasonings) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << "\n";
        return;
    }
    for (const auto &f : fruits)
        file << "f " << f.getName() << " " << f.getPrice() << " " << f.getQuantity() << "\n";
    for (const auto &s : snacks)
        file << "s " << s.getName() << " " << s.getPrice() << " " << s.getQuantity() << "\n";
    for (const auto &a : seasonings)
        file << "a " << a.getName() << " " << a.getPrice() << " " << a.getQuantity() << "\n";
    file.close();
}

void Ui::loadItems() {
    processFile("items.txt", fruits, snacks, seasonings);
    BankAccount::LoadFile(accounts);
}

void Ui::saveItems() {
    writeFile("items.txt", fruits, snacks, seasonings);
    BankAccount::SetFile(accounts);
}

void Ui::displayBalance(BankAccount &account) {
    try {
        cout << "\nAccount Balance (Serial: " << account.getSerialnum() << "):\n";
        if(account.getSerialnum()!=0){
        switch (account.getLabel()) {
            case 'R': {
                irr rial = account.getRial();
                cout << "Balance: " << rial.getAmount() << " IRR\n";
                break;
            }
            case 'D': {
                usd dollar = account.getDollar();
                cout << "Balance: " << dollar.getAmount() << " USD\n";
                break;
            }
            case 'E': {
                eur euro = account.getEuro();
                cout << "Balance: " << euro.getAmount() << " EUR\n";
                break;
            }
            default:
                throw invalid_argument("Unknown currency type!");
        }
    }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
    if(account.getSerialnum()==0){
        cout<<account.get_my_money();
    }

}

void Ui::Customer() {
    int choice;
    unsigned int serial;
    BankAccount* customerAccount = nullptr;
    BankAccount* Cashiers=nullptr;

    try {
        cout << "Enter your account serial number: ";
        cin >> serial;

        for (auto &account : accounts) {
            if (account.getSerialnum() == serial) {
                customerAccount = &account;}
                if(account.getSerialnum()==0){
                    Cashiers=&account;
                }
            
        }

        if (!customerAccount) {
            cout<<"you dont have accont plaese make new accont\n";
            cout<<"do you like continue enter 1 \n";
            int c;
            cin>>c;
            if(c)
            Customer();
            else{
                exit(0);
            }
        }

        if (customerAccount != nullptr) {
            while (true) {
                CustomerMenu();
                cin >> choice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number.\n";
                    continue;
                }



                switch (choice) {
                    case 0:{
                        saveItems();
                        exit(0);
                    }
                    case 1:
                        cout << "\nList Of Available Fruits:\n" << fruits;
                        cout << "\nList Of Available Snacks:\n" << snacks;
                        cout << "\nList Of Available Seasonings:\n" << seasonings;
                        break;

                    case 2: {
                        buy_func(customerCartFruit ,customerCartSnack , customerCartSeasoning);
                        break;
                    }

                    case 3: {
                        for (auto &fruit : customerCartFruit) {
                            totalUSD += (fruits - fruit);
                        }

                        for (auto &snack : customerCartSnack) {
                            totalUSD += (snacks - snack);
                        }

                        for (auto &seasoning : customerCartSeasoning) {
                            totalUSD += (seasonings - seasoning);
                        }

                        cout << "\n\t\tReceipt\n";
                        cout << "Fruits:\n" << customerCartFruit;
                        cout << "Snacks:\n" << customerCartSnack;
                        cout << "Seasonings:\n" << customerCartSeasoning;
                        cout << "Total (USD): " << totalUSD << endl;

                        try {
                            customerAccount->transaction(totalUSD , Cashiers );
                            totalUSD=0;
                            customerCartFruit.clear();
                            customerCartSnack.clear();
                            customerCartSeasoning.clear();
                            saveItems();
                        } catch (invalid_argument &e) {
                            cerr << e.what() << endl;
                        }
                        break;
                    }

                    case 4:
                        displayBalance(*customerAccount);
                        break;

                    default:
                        cout << "Invalid choice!\n";
                        break;
                }
            }
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}



void Ui::Cashier() {
    int choice;
    unsigned int serial;
    BankAccount* shopAccount = nullptr;
    try {
        cout << "Enter shop account serial number: ";
        cin >> serial;
        for (auto &account : accounts) {
            if (account.getSerialnum() == serial) {
                cout << "Welcome!\n";
                shopAccount = &account;
                break;
            }
        }
        if (!shopAccount)
            throw invalid_argument("Account not found!");
        
        while (true) {
            CashierMenu();
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            if (choice == 0){
                saveItems();
                exit(0);
            }
            switch (choice) {
                case 1:
                    cout << "\n\t\tInventory\n";
                    cout << "Fruits:\n" << fruits;
                    cout << "Snacks:\n" << snacks;
                    cout << "Seasonings:\n" << seasonings;
                    break;
                case 2: {
                    add_fanc();
                    saveItems();
                    break;
                }
                case 3:
                    displayBalance(*shopAccount);
                    break;
                default:
                    cout << "Invalid choice!\n";
                    break;
            }
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void Ui::run() {
    loadItems();
    int role;
    while (true) {
        try {
            cout << "\n\n\t\t*** Welcome to Marklar's Shop ***\n";
            cout << "Select role:\n";
            cout << "1. Customer\n";
            cout << "2. Cashier\n";
            cout << "3. Exit\n";
            cin >> role;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            if (role == 3)
                break;
            switch (role) {
                case 1:
                    Customer();
                    break;
                case 2:
                    Cashier();
                    break;
                default:
                    cout << "Invalid role!\n";
                    break;
            }
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    saveItems();
    exit(0);
}

void Ui::CustomerMenu() {
    cout << "\t\t*** Customer Menu ***\n";
    cout << "Enter your choice:\n";
    cout << "1. View Available Items\n";
    cout << "2. Add Item to Shopping Cart\n";
    cout << "3. Checkout\n";
    cout << "4. View Account Balance\n";
    cout << "0. Exit\n";
}

void Ui::CashierMenu() {
    cout << "\t\t*** Cashier Menu ***\n";
    cout << "Enter your choice:\n";
    cout << "1. View Inventory\n";
    cout << "2. Add Item to Inventory\n";
    cout << "3. View Shop Account Balance\n";
    cout << "0. Exit\n";
}
