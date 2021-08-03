#include "Customer.h"

Customer::Customer(string n, unsigned int ssn)
    : name(n), socialSecurityNumber(ssn) {}

string Customer::getName() { return name; }

unsigned int Customer::getSSN() { return socialSecurityNumber; }

void Customer::enqueue() { enqueueTime = chrono::system_clock::now(); }

void Customer::dequeue() { dequeueTime = chrono::system_clock::now(); }

chrono::duration<double> Customer::getLapsedTime() {
  return dequeueTime - enqueueTime;
}
