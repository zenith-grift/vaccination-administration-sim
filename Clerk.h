//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_CLERK_H
#define PROJECT2_JFRANDSEN_CLERK_H

#include <queue>
#include <string>

#include "Customer.h"
#include "Logger.h"
#include "UniformDistribution.h"
#include "VaccinationStation.h"

using namespace std;

class Clerk {
private:
  queue<VaccinationStation *> vacantStations;
  Logger *logger;

  queue<Customer *> *seniorQueue;
  queue<Customer *> *nonSeniorQueue;

  UniformDistribution checkInDistribution;

  // used by fillVacantStation
  Customer getNextCustomer();

public:
  // VaccinationCenter owns the queues
  Clerk(queue<Customer *> *senior, queue<Customer *> *nonSenior, Logger *l);

  // VaccinationCenter will own the customers
  // VaccinationCetner will control the frequency of check-ins
  void checkInCustomer(Customer *cust);

  // vacantStations will call to show they are ready
  void signalAvailible(VaccinationStation *vs);
  void fillVacantStation();
};

#endif // PROJECT2_JFRANDSEN_CLERK_H
