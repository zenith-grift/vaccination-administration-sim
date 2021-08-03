//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_ACCOUNTANT_H
#define PROJECT2_JFRANDSEN_ACCOUNTANT_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

class Customer {
private:
  string name;
  unsigned int socialSecurityNumber;

  // enqueue or dequeue of -1 not queued or dequeued respectively
  chrono::system_clock::time_point enqueueTime;
  chrono::system_clock::time_point dequeueTime;

public:
  Customer(string n, unsigned int ssn);

  string getName();
  unsigned int getSSN();
  void enqueue();
  void dequeue();
  chrono::duration<double> getLapsedTime();
};

#endif // PROJECT2_JFRANDSEN_ACCOUNTANT_H
