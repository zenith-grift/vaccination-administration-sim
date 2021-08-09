//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_VACCINATION_STATION_H
#define PROJECT2_JFRANDSEN_VACCINATION_STATION_H

#include "Customer.h"
#include "ExponentialDistribution.h"
#include "Logger.h"

class Clerk;

using namespace std;

class VaccinationStation {
private:
  Clerk *clerk;
  Logger *logger;

  unsigned int id;

  ExponentialDistribution *expoDist;

public:
  VaccinationStation(Clerk *c, Logger *l, unsigned int id,
                     ExponentialDistribution *dist);
  void signalReady();
  void vaccinate(Customer cust);
};

#endif // PROJECT2_JFRANDSEN_VACCINATION_STATION_H
