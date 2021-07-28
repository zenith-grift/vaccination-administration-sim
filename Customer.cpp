#include "Customer.h"

Customer::Customer(string n, unsigned int ssn)
    : name(n), socialSecurityNumber(ssn) {}

string Customer::getName() { return name; }

unsigned int Customer::getSSN() { return socialSecurityNumber; }
