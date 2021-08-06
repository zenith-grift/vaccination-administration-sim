#include "Clerk.h"

Clerk::Clerk(queue<Customer *> *senior, queue<Customer *> *nonSenior)
    : seniorQueue(senior), nonSeniorQueue(nonSenior) {}

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

void Clerk::fillVacantStation() {
  Customer nextCustomer = getNextCustomer();
  VaccinationStation *vacantStation = vacantStations.front();
  vacantStations.pop();
  vacantStation->vaccinate(&nextCustomer);
}
