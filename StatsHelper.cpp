#include <fstream>
#include <sstream>

#include "StatsHelper.h"

/*
Log file has structure -> [LEVEL] EVENT SSN "event length in ms"

Example Log:
    [INFO] ARRIVE 0 2.661
*/

const string ARRIVE = "ARRIVE";
const string CHECK_IN = "CHECK_IN";
const string START_VAC = "START_VAC";
const string END_VAC = "END_VAC";
const string FINISH = "FINISH";

StatsHelper::StatsHelper(string file) : logFile(file) {}

int StatsHelper::getNumberOfCusotmersServed() {
  fstream f(logFile);
  string line, level, event;
  stringstream ss;
  int ssn;
  double time;

  int count = 0;
  if (f.is_open()) {
    while (getline(f, line)) {
      ss << line << endl;
      ss >> level >> event >> ssn >> time;

      if (event == ARRIVE) {
        count++;
      }
    }
  }

  return count;
}

double StatsHelper::getAverageTime(string eventString) {
  fstream f(logFile);
  string line, level, event;
  stringstream ss;
  int ssn;
  double time;

  int count = 0;
  double tot = 0;

  if (f.is_open()) {
    while (getline(f, line)) {
      ss << line << endl;
      ss >> level >> event >> ssn >> time;

      if (event == eventString) {
        count++;
        tot += time;
      }
    }
  }

  return tot / double(count);
}
