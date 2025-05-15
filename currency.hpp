#ifndef CURRENCY_HPP
#define CURRENCY_HPP


#include<iostream>


 class Currency
 {
  public:
  
   virtual double Change()=0;
   protected:

   double money;
   

 };

 #endif