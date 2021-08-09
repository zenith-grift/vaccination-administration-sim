//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_VACCINATION_CENTER_H
#define PROJECT2_JFRANDSEN_VACCINATION_CENTER_H

#include <chrono>
#include <vector>

#include "Clerk.h"
#include "Customer.h"
#include "ExponentialDistribution.h"
#include "Logger.h"
#include "VaccinationStation.h"

using namespace std;

class VaccinationCenter {
private:
  Logger *logger;
  vector<VaccinationStation *> stations;
  SynchronizedQueue<Customer *> seniorQueue;
  SynchronizedQueue<Customer *> nonSeniorQueue;
  Clerk *clerk;
  ExponentialDistribution customerArrivalDistribution;
  ExponentialDistribution vaccinationDistribution;
  UniformDistribution ageDist;

  unsigned int numDays;
  chrono::system_clock::time_point simulationStartTime;

  // needs to be thread safe if make multi-threaded
  unsigned int numCustomersCheckedIn;

public:
  VaccinationCenter(unsigned int numStations, unsigned int days);
  ~VaccinationCenter();

  SynchronizedQueue<Customer *> *getSeniorQueue();
  SynchronizedQueue<Customer *> *getNonSeniorQueue();

  void addVaccinationStation(VaccinationStation vs);

  void incrementNumCheckedInCustomers();
  unsigned int getNumCheckedInCustomers();

  chrono::system_clock::time_point getSimulationStartTime();

  void simulateCustomerArrival();
  void runCustomerArrivals();
  void runSimulation();
};

#endif // PROJECT2_JFRANDSEN_VACCINATION_CENTER_H
