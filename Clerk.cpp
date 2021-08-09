#include <chrono>
#include <thread>

#include "Clerk.h"

const unsigned int SENIOR_AGE = 65;

Clerk::Clerk(SynchronizedQueue<Customer *> *senior,
             SynchronizedQueue<Customer *> *nonSenior, Logger *l,
             chrono::system_clock::time_point *time)
    : seniorQueue(senior), nonSeniorQueue(nonSenior), logger(l),
      checkInDistribution(1, 4), simulationStartTime(time) {}

void Clerk::signalAvailible(VaccinationStation *vs) { vacantStations.push(vs); }

Customer Clerk::getNextCustomer() {
  Customer nextCustomer;
  if (!seniorQueue->empty()) {
    nextCustomer = *seniorQueue->pop();
    return nextCustomer;
  }

  nextCustomer = *nonSeniorQueue->pop();
  return nextCustomer;
}

void Clerk::checkInCustomer(Customer *cust) {
  chrono::system_clock::time_point start = chrono::system_clock::now();

  double sampleTimeMinutes = checkInDistribution.pullSample();
  std::chrono::milliseconds timespan(int(sampleTimeMinutes / 60.0 * 1000.0));
  this_thread::sleep_for(timespan);

  if (cust->getAge() > SENIOR_AGE) {
    seniorQueue->push(cust);
  } else {
    nonSeniorQueue->push(cust);
  }

  chrono::duration<double, std::milli> time =
      (chrono::system_clock::now() - start);
  cust->setCheckInTime(time.count());
  logger->log(CHECK_IN, *cust);
}

int Clerk::getNumberOfVacant() { return vacantStations.size(); }
chrono::system_clock::time_point *Clerk::getSimulationStartTime() {
  return simulationStartTime;
};

thread Clerk::fillVacantStation() {
  // this should block if empty
  VaccinationStation *vacantStation = vacantStations.pop();
  Customer nextCustomer = getNextCustomer();

  thread th(&VaccinationStation::vaccinate, vacantStation, nextCustomer);
  return th;
}
