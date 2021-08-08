#include <chrono>
#include <thread>

#include "VaccinationCenter.h"

const string LOG_FILE = ".log";
const int ARRIVAL_RATE = 30; // customers arrive per hour
const int OPERATING_HOURS = 12;

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
  int time = customerArrivalDistribution.pullSample();
  std::chrono::seconds timespan(time);
  this_thread::sleep_for(timespan);

  Customer *tmp = new Customer(67, ++numCustomersCheckedIn);
  clerk->checkInCustomer(tmp);
  logger->log("ARRIVED", *tmp);
}

queue<Customer *> VaccinationCenter::getSeniorQueue() { return seniorQueue; }

void VaccinationCenter::runSimulation() {
  // TODO: reduce the time based on the 12 hour operation window
  // currently using all 24 hours of the day

  // Simulation time: 1 hour real time === 1 second simulation time
  // this allows for a 5 day simulation to last less than a minute
  auto start = chrono::system_clock::now();
  chrono::duration<double> elapsedTime = start - start;

  while (elapsedTime.count() < numDays * OPERATING_HOURS) {
    simulateCustomerArrival();
    elapsedTime = chrono::system_clock::now() - start;
    cout << "elapsed time (s): " << elapsedTime.count()
         << ", minutes: " << elapsedTime.count() / 60.0
         << ", target: " << numDays * 24 << endl;
  }

  // TODO: after while loop accept no more people into the queue
  // but wait for all people in queue to finish being vaccinated
}
