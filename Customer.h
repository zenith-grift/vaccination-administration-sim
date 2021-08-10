//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_CUSTOMER_H
#define PROJECT2_JFRANDSEN_CUSTOMER_H

#include <chrono>
#include <string>

using namespace std;

class Customer {
private:
  unsigned int age;
  unsigned int socialSecurityNumber;
  chrono::system_clock::time_point arrivalTime;
  double checkInTime, startVaccinationTime, endVaccinationTime, totalTime;

public:
  Customer();
  Customer(unsigned int a, unsigned int ssn);

  unsigned int getSSN() const;
  unsigned int getAge() const;

  // arrivalTime is an absolute time that is used to calculate
  // total duration of process at the end of simulation
  chrono::system_clock::time_point getArrivalTime() const;
  void setArrivalTime(chrono::system_clock::time_point time);

  double getCheckInTimeDelta() const;
  double getStartVaccinationTimeDelta() const;
  double getEndVaccinationTimeDelta() const;
  double getTotalTimeDelta() const;
  void setCheckInTime(double time);
  void setStartVaccinationTime(double time);
  void setEndVaccinationTime(double time);
  void setTotalTime(double time);
};

#endif // PROJECT2_JFRANDSEN_CUSTOMER_H
