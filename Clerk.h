//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_CLERK_H
#define PROJECT2_JFRANDSEN_CLERK_H

#include "Customer.h"
#include "Logger.h"
#include "SynchronizedQueue.h"
#include "UniformDistribution.h"
#include "VaccinationStation.h"

using namespace std;

const unsigned int SENIOR_AGE = 65;
const int CHECK_IN_LOWER = 1;
const int CHECK_IN_UPPER = 4;

class Clerk {
private:
  SynchronizedQueue<VaccinationStation *> vacantStations;
  Logger *logger;

  SynchronizedQueue<Customer *> *seniorQueue;
  SynchronizedQueue<Customer *> *nonSeniorQueue;

  UniformDistribution checkInDistribution;

  Customer getNextCustomer();

public:
  // VaccinationCenter owns the queues
  Clerk(SynchronizedQueue<Customer *> *senior,
        SynchronizedQueue<Customer *> *nonSenior, Logger *l);

  void checkInCustomer(Customer *cust);

  // vacantStations will call to show they are ready
  void signalAvailible(VaccinationStation *vs);
  thread fillVacantStation();
  int getNumberOfVacant();
};

#endif // PROJECT2_JFRANDSEN_CLERK_H
