#include <chrono>
#include <future>
#include <mutex>
#include <thread>

#include "VaccinationCenter.h"

using namespace std;

const string LOG_FILE = ".log";
const int ARRIVAL_RATE = 30;     // customers arrive per hour
const int VACCINATION_RATE = 15; // vaccinations per hour
const int OPERATING_HOURS = 12;

VaccinationCenter::VaccinationCenter(unsigned int numStations,
                                     unsigned int days)
    : customerArrivalDistribution(ExponentialDistribution(ARRIVAL_RATE)),
      vaccinationDistribution(ExponentialDistribution(VACCINATION_RATE)),
      ageDist(12, 100), numDays(days), numCustomersCheckedIn(0) {

  logger = new Logger(LOG_FILE, LogLevel::INFO);
  logger->clearLog();
  clerk =
      new Clerk(&seniorQueue, &nonSeniorQueue, logger, &simulationStartTime);

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

chrono::system_clock::time_point VaccinationCenter::getSimulationStartTime() {
  return simulationStartTime;
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
  // this allows for a 5 day simulation to last less than a minute
  auto start = chrono::system_clock::now();
  chrono::duration<double> elapsedTime = start - start;

  while (elapsedTime.count() < numDays * OPERATING_HOURS) {
    simulateCustomerArrival();
    elapsedTime = chrono::system_clock::now() - start;
    cout << "elapsed time (s): " << elapsedTime.count()
         << ", minutes: " << elapsedTime.count() / 60.0
         << ", custs: " << getNumCheckedInCustomers() << endl;
  }
}

void VaccinationCenter::runSimulation() {
  simulationStartTime = chrono::system_clock::now();
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
