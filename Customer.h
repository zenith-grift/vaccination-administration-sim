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
  unsigned int age;
  unsigned int socialSecurityNumber;

public:
  Customer();
  Customer(unsigned int a, unsigned int ssn);

  string getName() const;
  unsigned int getSSN() const;
  unsigned int getAge() const;
};

#endif // PROJECT2_JFRANDSEN_CUSTOMER_H
