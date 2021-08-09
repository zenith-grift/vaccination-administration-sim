#include <iostream>

#include "Clerk.h"
#include "Customer.h"
#include "ExponentialDistribution.h"
#include "Logger.h"
#include "StatsHelper.h"
#include "UniformDistribution.h"
#include "VaccinationCenter.h"
#include "VaccinationStation.h"

#include <chrono>
#include <ctime>
#include <thread>

const string LOG_FILE = ".log";
const int NUM_STATIONS = 3;
const int NUM_DAYS = 5;

using namespace std;
int main() {

  StatsHelper sh(LOG_FILE);
  VaccinationCenter vc(NUM_STATIONS, NUM_DAYS);
  vc.runSimulation();

  SynchronizedQueue<Customer *> *sq = vc.getSeniorQueue();
  SynchronizedQueue<Customer *> *nsq = vc.getNonSeniorQueue();
  cout << "senior_size: " << sq->size() << ", non_senior_size: " << nsq->size()
       << endl;

  cout << "----------------------------------" << endl << endl;
  auto checkin_avg = sh.getAverageTime("CHECK_IN");
  auto vac_avg = sh.getAverageTime("END_VAC");
  auto tot_cust = sh.getNumberOfCusotmersServed();
  auto tot_time = sh.getAverageTime("FINISH");

  cout << "\ncheck-in: " << checkin_avg << ", vaccination: " << vac_avg
       << ", total cust: " << tot_cust
       << ", avg cust/day: " << double(tot_cust) / double(NUM_DAYS)
       << ", avg total time: " << tot_time << endl;
  return 0;
}
