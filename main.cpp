#include <iostream>

#include "Clerk.h"
#include "Customer.h"
#include "ExponentialDistribution.h"
#include "Logger.h"
#include "UniformDistribution.h"
#include "VaccinationCenter.h"
#include "VaccinationStation.h"

#include <chrono>
#include <ctime>
#include <thread>

const string LOG_FILE = ".log";

using namespace std;
int main() {
  UniformDistribution uni(1, 4);

  for (int i = 0; i < 10; ++i) {
    cout << "Uniform sample: " << uni.pullSample() << endl;
  }

  Logger logger(LOG_FILE, LogLevel::INFO);
  Customer c("josh", 66666666);

  c.enqueue();
  logger.log("Enqueue", c);

  std::chrono::milliseconds timespan(10000); // or whatever
  this_thread::sleep_for(timespan);
  c.dequeue();
  logger.log("Dequeue", c);

  cout << "name: " << c.getName() << ", ssn: " << c.getSSN()
       << ", lapsed time: " << c.getLapsedTime().count() << endl;
  return 0;
}
