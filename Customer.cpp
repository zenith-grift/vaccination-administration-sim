#include "Customer.h"

Customer::Customer() : age(18), socialSecurityNumber(-1) {}
Customer::Customer(unsigned int a, unsigned int ssn)
    : age(a), socialSecurityNumber(ssn) {}

unsigned int Customer::getSSN() const { return socialSecurityNumber; }

unsigned int Customer::getAge() const { return age; }

/* void Customer::enqueue() { enqueueTime = chrono::system_clock::now(); } */
/*  */
/* void Customer::dequeue() { dequeueTime = chrono::system_clock::now(); } */
/*  */
/* chrono::duration<double> Customer::getLapsedTime() { */
/*   return dequeueTime - enqueueTime; */
/* } */
