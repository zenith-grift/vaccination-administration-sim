#include "Customer.h"

Customer::Customer() : age(18), socialSecurityNumber(-1) {}
Customer::Customer(unsigned int a, unsigned int ssn)
    : age(a), socialSecurityNumber(ssn) {}

unsigned int Customer::getSSN() const { return socialSecurityNumber; }

unsigned int Customer::getAge() const { return age; }

chrono::system_clock::time_point Customer::getArrivalTime() const {
  return arrivalTime;
}
void Customer::setArrivalTime(chrono::system_clock::time_point time) {
  arrivalTime = time;
}

double Customer::getCheckInTimeDelta() const { return checkInTime; }
double Customer::getStartVaccinationTimeDelta() const {
  return startVaccinationTime;
}
double Customer::getEndVaccinationTimeDelta() const {
  return endVaccinationTime;
}
double Customer::getTotalTimeDelta() const { return totalTime; }
void Customer::setCheckInTime(double time) { checkInTime = time; }
void Customer::setStartVaccinationTime(double time) {
  startVaccinationTime = time;
}
void Customer::setEndVaccinationTime(double time) { endVaccinationTime = time; }
void Customer::setTotalTime(double time) { totalTime = time; }

/* void Customer::enqueue() { enqueueTime = chrono::system_clock::now(); } */
/*  */
/* void Customer::dequeue() { dequeueTime = chrono::system_clock::now(); } */
/*  */
/* chrono::duration<double> Customer::getLapsedTime() { */
/*   return dequeueTime - enqueueTime; */
/* } */
