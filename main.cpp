#include <iomanip>
#include <iostream>
#include <string>

#include "StatsHelper.h"
#include "VaccinationCenter.h"

const int NUM_STATIONS = 3;
const int NUM_DAYS = 5;

const double CONVERSION_TO_MINUTES = 1.0 / 1000.0 * 60.0;

using namespace std;
int main() {

  StatsHelper sh(LOG_FILE);
  VaccinationCenter vc(NUM_STATIONS, NUM_DAYS);

  cout << "Starting Simulation...." << endl;
  vc.runSimulation();
  cout << "Finished Simulation....\n" << endl;

  int colWidth = 22;
  int numCols = 5;
  int barWidth = colWidth * numCols + numCols + 1;
  auto checkin_avg = sh.getAverageTime("CHECK_IN") * CONVERSION_TO_MINUTES;
  auto vac_avg = sh.getAverageTime("END_VAC") * CONVERSION_TO_MINUTES;
  auto tot_time = sh.getAverageTime("FINISH") * CONVERSION_TO_MINUTES;
  auto tot_cust = sh.getNumberOfCusotmersServed();

  cout << "Results: days = " << NUM_DAYS << ", #stations = " << NUM_STATIONS
       << endl;
  cout << string(barWidth, '-') << endl;
  cout << "|" << setw(colWidth) << "Check-In-Avg [min]"
       << "|" << setw(colWidth) << "Vaccination-Avg [min]"
       << "|" << setw(colWidth) << "Total-Time-Avg [min]"
       << "|" << setw(colWidth) << "Customers-Served"
       << "|" << setw(colWidth) << "Customers-Per-Day-Avg"
       << "|" << endl;

  cout << "|" << setw(colWidth) << setprecision(4) << checkin_avg << "|"
       << setw(colWidth) << setprecision(4) << vac_avg << "|" << setw(colWidth)
       << setprecision(4) << tot_time << "|" << setw(colWidth)
       << setprecision(4) << tot_cust << "|" << setw(colWidth)
       << setprecision(4) << double(tot_cust) / double(NUM_DAYS) << "|" << endl;
  cout << string(barWidth, '-') << endl;

  return 0;
}
