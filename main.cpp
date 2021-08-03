#include "Customer.h"
#include <iostream>

#include <chrono>
#include <ctime>
#include <thread>

using namespace std;
int main() {

  Customer c("josh", 66666666);

  c.enqueue();

  std::chrono::milliseconds timespan(10000); // or whatever
  this_thread::sleep_for(timespan);
  c.dequeue();

  cout << "name: " << c.getName() << ", ssn: " << c.getSSN()
       << ", lapsed time: " << c.getLapsedTime().count() << endl;
  return 0;
}
