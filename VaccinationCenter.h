//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_VACCINATION_CENTER_H
#define PROJECT2_JFRANDSEN_VACCINATION_CENTER_H

#include <queue>
#include <vector>

#include "Clerk.h"
#include "Customer.h"
#include "ExponentialDistribution.h"
#include "Logger.h"
#include "VaccinationStation.h"

using namespace std;

class VaccinationCenter {
private:
  Logger logger;
  vector<VaccinationStation> stations;
  queue<Customer> seniorQueue;
  queue<Customer> nonSeniorQueue;
  Clerk clerk;
  ExponentialDistribution customerArrivalDistribution;

  unsigned int days;

public:
  VaccinationCenter();
  void addVaccinationStation(VaccinationStation vs);

  void enqueueSenior(Customer senior);
  void enqueueNonSenior(Customer nonSenior);

  void simulateCustomerArrival();
  void runSimulation();
};

#endif // PROJECT2_JFRANDSEN_VACCINATION_CENTER_H
