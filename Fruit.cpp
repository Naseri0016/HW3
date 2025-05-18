#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include "Fruit.hpp"

using namespace std;



Fruit :: Fruit ( string name ) {

    this->name=name;

}
Fruit::Fruit(double amount, string name, string unit, double price) {
    this->name = name;
    
   
    while (true) {
        try {
            setAmount(amount, unit);
            break; 
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            cout << "Enter new amount: ";
            cin >> amount;
            cout << "Enter new unit: ";
            cin >> unit;
        }
    }
    
  
    while (true) {
        try {
            setPrice(price);
            break; 
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            cout << "Please enter new price: ";
            cin >> price;
        }
    }
}


  

void Fruit:: setAmount (double amount ,string u )
{

    if (amount < 0 )
    {
        throw invalid_argument("Amount most be positive !!!") ;
    }
    else
    {
        if(u=="kg"){

            unit=u;

            quantity = amount ;
        }
        if(u=="g"){

            unit ="kg";

            quantity=(amount/1000);
        }
        if(u=="ton"){

            unit = "kg";

            quantity=amount*1000;

        }

        if(  u !="kg" || u !="g" || u !="ton")
        {
            throw invalid_argument("unit most be kg or g or ton");
        }
    }

}

void Fruit :: setPrice(double money)
{
    if (money < 0 )
    {
        throw invalid_argument("price most be positive !!!") ;
    }
    else
    {
        price = money ;
    }

}