#include <iostream>

#include "Customer.h"
#include "Logger.h"

#include <chrono>
#include <ctime>
#include <thread>

const string LOG_FILE = ".log";

using namespace std;
int main() {
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
