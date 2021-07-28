//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_ACCOUNTANT_H
#define PROJECT2_JFRANDSEN_ACCOUNTANT_H

#include <iostream>
#include <string>

using namespace std;

class Customer {
private:
  string name;
  unsigned int socialSecurityNumber;

public:
  Customer(string n, unsigned int ssn);

  string getName();
  unsigned int getSSN();
};

#endif // PROJECT2_JFRANDSEN_ACCOUNTANT_H
