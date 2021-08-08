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
  VaccinationCenter vc(3, 5);
  vc.simulateCustomerArrival();
  vc.simulateCustomerArrival();
  vc.simulateCustomerArrival();
  vc.simulateCustomerArrival();
  queue<Customer *> queue = vc.getSeniorQueue();

  cout << "senior queue: " << queue.size() << endl;

  return 0;
}
