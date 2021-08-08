#include <chrono>
#include <thread>

#include "Clerk.h"

const unsigned int SENIOR_AGE = 65;

Clerk::Clerk(queue<Customer *> *senior, queue<Customer *> *nonSenior, Logger *l)
    : seniorQueue(senior), nonSeniorQueue(nonSenior), logger(l),
      checkInDistribution(1, 4) {}

void Clerk::signalAvailible(VaccinationStation *vs) { vacantStations.push(vs); }

Customer Clerk::getNextCustomer() {
  Customer nextCustomer;
  if (seniorQueue->empty()) {
    nextCustomer = *nonSeniorQueue->front();
    nonSeniorQueue->pop();
    return nextCustomer;
  }

  nextCustomer = *seniorQueue->front();
  seniorQueue->pop();
  return nextCustomer;
}

void Clerk::checkInCustomer(Customer *cust) {
  // use uniform distribution here
  double time = checkInDistribution.pullSample();
  std::chrono::milliseconds timespan((int)time);
  this_thread::sleep_for(timespan);

  if (cust->getAge() > SENIOR_AGE) {
    seniorQueue->push(cust);
  } else {
    nonSeniorQueue->push(cust);
  }

  logger->log("CHECKED_IN", *cust);
}

void Clerk::fillVacantStation() {
  Customer nextCustomer = getNextCustomer();
  VaccinationStation *vacantStation = vacantStations.front();
  vacantStations.pop();
  vacantStation->vaccinate(&nextCustomer);
}
