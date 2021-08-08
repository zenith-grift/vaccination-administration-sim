#include <chrono>
#include <thread>

#include "VaccinationCenter.h"

const string LOG_FILE = ".log";
const int ARRIVAL_RATE = 30; // customers arrive per hour

VaccinationCenter::VaccinationCenter(unsigned int numStations,
                                     unsigned int days)
    : customerArrivalDistribution(ExponentialDistribution(ARRIVAL_RATE)),
      numDays(days), numCustomersCheckedIn(0) {

  logger = new Logger(LOG_FILE, LogLevel::INFO);
  clerk = new Clerk(&seniorQueue, &nonSeniorQueue, logger);

  for (int i = 0; i < numStations; ++i) {
    stations.push_back(new VaccinationStation(clerk, logger, i + 1));
  }
}

VaccinationCenter::~VaccinationCenter() {
  for (auto *station : stations) {
    delete station;
  }

  delete logger;
  delete clerk;
}

void VaccinationCenter::simulateCustomerArrival() {
  // sample the time
  int time = customerArrivalDistribution.pullSample();
  std::chrono::milliseconds timespan(time * 10);
  this_thread::sleep_for(timespan);

  Customer *tmp = new Customer(67, ++numCustomersCheckedIn);
  clerk->checkInCustomer(tmp);
  logger->log("ARRIVED", *tmp);
}

queue<Customer *> VaccinationCenter::getSeniorQueue() { return seniorQueue; }
