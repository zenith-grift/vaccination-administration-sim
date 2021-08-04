//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_CLERK_H
#define PROJECT2_JFRANDSEN_CLERK_H

#include <iostream>
#include <queue>
#include <random>
#include <string>

#include "Customer.h"
#include "VaccinationStation.h"

using namespace std;

class Clerk {
private:
  queue<VaccinationStation> vacantStations;

public:
  Clerk();
  void signalAvailible(VaccinationStation &vs);
  Customer getNextCustomer(queue<Customer> &senior, queue<Customer> &nonSenior);
  void fillVacantStation();
};

#endif // PROJECT2_JFRANDSEN_CLERK_H
