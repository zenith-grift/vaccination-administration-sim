//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_STATS_HELPER_H
#define PROJECT2_JFRANDSEN_STATS_HELPER_H

#include <iostream>
#include <string>

using namespace std;

class StatsHelper {
private:
  string logFile;

public:
  StatsHelper(string file);

  double getAverageTime(string eventString);
  double getAverageCustomersPerDay();
  double getAverageTotalTime();
  double getAverageCheckInTime();
  int getNumberOfCusotmersServed();
};

#endif // PROJECT2_JFRANDSEN_STATS_HELPER_H
