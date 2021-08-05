#include <chrono>
#include <thread>

#include "VaccinationStation.h"

using namespace std;

VaccinationStation::VaccinationStation(Clerk *c, Logger *l)
    : clerk(c), logger(l), expoDist(ExponentialDistribution(VACCINATION_RATE)) {
}

void VaccinationStation::vaccinate(Customer cust) {

  // sample the time it takes to vaccinate
  int time = expoDist.pullSample();
  std::chrono::milliseconds timespan(time);

  logger->log("VACCINATION_STARTED", cust);
  this_thread::sleep_for(timespan);
  logger->log("VACCINATION_DONE", cust);

  clerk->signalAvailible(this);
}
