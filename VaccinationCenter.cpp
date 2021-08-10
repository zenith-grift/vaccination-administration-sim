#include <chrono>
#include <future>
#include <mutex>
#include <thread>

#include "VaccinationCenter.h"

using namespace std;

VaccinationCenter::VaccinationCenter(unsigned int numStations,
                                     unsigned int days)
    : customerArrivalDistribution(ExponentialDistribution(ARRIVAL_RATE)),
      vaccinationDistribution(ExponentialDistribution(VACCINATION_RATE)),
      ageDist(MIN_AGE, MAX_AGE), numDays(days), numCustomersCheckedIn(0) {

  logger = new Logger(LOG_FILE, LogLevel::INFO);
  logger->clearLog();
  clerk = new Clerk(&seniorQueue, &nonSeniorQueue, logger);

  for (int i = 0; i < numStations; ++i) {
    stations.push_back(
        new VaccinationStation(clerk, logger, i + 1, &vaccinationDistribution));
    stations[i]->signalReady();
  }
}

VaccinationCenter::~VaccinationCenter() {
  for (auto *station : stations) {
    delete station;
  }

  delete logger;
  delete clerk;
}

void VaccinationCenter::incrementNumCheckedInCustomers() {
  mutex mut;
  lock_guard<mutex> lock(mut);
  numCustomersCheckedIn++;
}

unsigned int VaccinationCenter::getNumCheckedInCustomers() {
  mutex mut;
  lock_guard<mutex> lock(mut);
  return numCustomersCheckedIn;
}

void VaccinationCenter::simulateCustomerArrival() {

  double sampleTime = customerArrivalDistribution.pullSample();
  chrono::milliseconds timespan(int(sampleTime * 1000));
  this_thread::sleep_for(timespan);

  chrono::system_clock::time_point startTime = chrono::system_clock::now();
  Customer *tmp =
      new Customer(ageDist.pullSample(), getNumCheckedInCustomers());

  tmp->setArrivalTime(startTime);
  logger->log(ARRIVE, *tmp);
  incrementNumCheckedInCustomers();
  clerk->checkInCustomer(tmp);
}

SynchronizedQueue<Customer *> *VaccinationCenter::getSeniorQueue() {
  return &seniorQueue;
}

SynchronizedQueue<Customer *> *VaccinationCenter::getNonSeniorQueue() {
  return &nonSeniorQueue;
}

void VaccinationCenter::runCustomerArrivals() {
  // Simulation time: 1 hour real time === 1 second simulation time
  auto start = chrono::system_clock::now();
  chrono::duration<double> elapsedTime = start - start;

  while (elapsedTime.count() < numDays * OPERATING_HOURS) {
    simulateCustomerArrival();
    elapsedTime = chrono::system_clock::now() - start;
  }
}

void VaccinationCenter::runSimulation() {
  vector<thread> vaccinationThreads;

  packaged_task<void()> arrivalsTask(
      bind(&VaccinationCenter::runCustomerArrivals, this));
  auto arrivalFuture = arrivalsTask.get_future();
  thread arrivalsThread(move(arrivalsTask));

  while (!seniorQueue.empty() || !nonSeniorQueue.empty() ||
         arrivalFuture.wait_for(0ms) != future_status::ready) {

    if (arrivalFuture.wait_for(0ms) != future_status::ready &&
        seniorQueue.empty() && nonSeniorQueue.empty()) {
      continue;
    }

    if (clerk->getNumberOfVacant() > 0) {
      vaccinationThreads.push_back(clerk->fillVacantStation());
    }
  }

  arrivalsThread.join();
  for (thread &t : vaccinationThreads) {
    if (t.joinable())
      t.join();
  }
}
