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
  VaccinationCenter vc(3, 1);
  vc.runSimulation();
  queue<Customer *> queue = vc.getSeniorQueue();

  cout << "senior queue: " << queue.size() << endl;

  return 0;
}
