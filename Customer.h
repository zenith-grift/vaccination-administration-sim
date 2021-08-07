//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_CUSTOMER_H
#define PROJECT2_JFRANDSEN_CUSTOMER_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

class Customer {
private:
  string name;
  unsigned int socialSecurityNumber;

public:
  Customer();
  Customer(string n, unsigned int ssn);

  string getName() const;
  unsigned int getSSN() const;
};

#endif // PROJECT2_JFRANDSEN_CUSTOMER_H
