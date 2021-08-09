#include <chrono>
#include <thread>

#include "Clerk.h"
#include "Logger.h"
#include "VaccinationStation.h"

using namespace std;

VaccinationStation::VaccinationStation(Clerk *c, Logger *l, unsigned int id,
                                       ExponentialDistribution *dist)
    : clerk(c), logger(l), expoDist(dist), id(id) {}

void VaccinationStation::vaccinate(Customer cust) {
  chrono::system_clock::time_point start = chrono::system_clock::now();

  // sample the time it takes to vaccinate
  std::chrono::milliseconds timespan(int(expoDist->pullSample() * 1000));

  chrono::duration<double, milli> t = (chrono::system_clock::now() - start);
  cust.setStartVaccinationTime(t.count());

  logger->log(START_VAC, cust);
  this_thread::sleep_for(timespan);

  t = (chrono::system_clock::now() - start);
  cust.setEndVaccinationTime(t.count());
  logger->log(END_VAC, cust);

  chrono::duration<double, milli> totalTime =
      chrono::system_clock::now() - cust.getArrivalTime();
  cust.setTotalTime(totalTime.count());
  logger->log(FINISH, cust);

  /* cout << "[vaccinate] station: " << id */
  /*      << ", check-in: " << cust.getCheckInTimeDelta() << " [ms]" */
  /*      << ", vac-start: " << cust.getStartVaccinationTimeDelta() << " [ms]"
   */
  /*      << ", vac-end: " << cust.getEndVaccinationTimeDelta() << " [ms]" */
  /*      << ", tot-time: " << totalTime.count() << " [ms]" */
  /*      << ", ssn: " << cust.getSSN() << endl; */
  signalReady();
}

void VaccinationStation::signalReady() { clerk->signalAvailible(this); }
