//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_CLERK_H
#define PROJECT2_JFRANDSEN_CLERK_H

#include <future>
#include <string>

#include "Customer.h"
#include "Logger.h"
#include "SynchronizedQueue.h"
#include "UniformDistribution.h"
#include "VaccinationStation.h"

using namespace std;

class Clerk {
private:
  SynchronizedQueue<VaccinationStation *> vacantStations;
  Logger *logger;

  SynchronizedQueue<Customer *> *seniorQueue;
  SynchronizedQueue<Customer *> *nonSeniorQueue;

  UniformDistribution checkInDistribution;

  chrono::system_clock::time_point *simulationStartTime;

  // used by fillVacantStation
  Customer getNextCustomer();

public:
  // VaccinationCenter owns the queues
  Clerk(SynchronizedQueue<Customer *> *senior,
        SynchronizedQueue<Customer *> *nonSenior, Logger *l,
        chrono::system_clock::time_point *time);

  // VaccinationCenter will own the customers
  // VaccinationCetner will control the frequency of check-ins
  void checkInCustomer(Customer *cust);
  chrono::system_clock::time_point *getSimulationStartTime();

  // vacantStations will call to show they are ready
  void signalAvailible(VaccinationStation *vs);
  thread fillVacantStation();
  int getNumberOfVacant();
};

#endif // PROJECT2_JFRANDSEN_CLERK_H
