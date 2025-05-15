#include<iostream>
#include"EUR.hpp"
#include"IRR.hpp"
#include"USD.hpp"
#include<stdexcept>

using namespace std;


irr:: irr( double m)
{
    if(m>0)
    {
        money = m;
    }
    else
    {
        throw invalid_argument("The money most be posetive");
    }

}

double irr:: Change()
{
    return money/85;
}

void irr :: get_inventory()
{
    cout<<"Your balance in dollars will be: \t";
    cout<<money/85<<endl;

    cout<<"Your balance in will be in euros: \t";
    cout<<money/93<<endl;
}


eur :: eur(double m)
{
    if(m>0)
    {
        money = m;
    }
    else
    {
        throw invalid_argument("The money most be posetive");
    }
}

double eur:: Change()
{
    return money*1.04;
}

double eur:: get_inventory()
{

    cout<<"Your balance in dollars will be: \t";
    cout<<money*1.04<<endl;

    cout<<"Your balance in will be in Roals: \t";
    cout<<money*93<<endl;
}

usd:: usd(double m)
{
    if(m>0)
    {
        money = m ;
    }
    else
    {
        throw invalid_argument("The money most be posetive");
    }
}

double usd:: Change()
{
    return money;
}


double usd:: get_Inventory()
{

    cout<<"Your balance in EURS will be: \t";
    cout<<money/1.04<<endl;
    
    cout<<"Your balance in will be in Roals: \t";
    cout<<money*85<<endl;
}

double usd:: Change(double m){
    return m;
}

double irr:: Change(double m){
    return m*85;
}

double eur:: Change(double m){
    return m/1.04;
}




