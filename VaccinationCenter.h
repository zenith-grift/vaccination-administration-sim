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

const string LOG_FILE = ".log";  // location of output logs
const int ARRIVAL_RATE = 30;     // customers arrive per hour
const int VACCINATION_RATE = 15; // vaccinations per hour
const int OPERATING_HOURS = 12;  // hours of operation per day
const int MIN_AGE = 16;          // lower bound of age distribution
const int MAX_AGE = 115;         // upper bound of age distribution

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

  void simulateCustomerArrival();
  void runCustomerArrivals();
  void runSimulation();
};

#endif // PROJECT2_JFRANDSEN_VACCINATION_CENTER_H
