#include <chrono>
#include <ctime>
#include <fstream>
#include <mutex>
#include <sstream>

#include "Logger.h"

using namespace std;

Logger::Logger(string f, LogLevel lvl) : file(f), logLevel(lvl) {}

void Logger::log(LogEvent event, const Customer &cust) {
  // [level] event customer time [ms from start]

  string eventString;
  double time;

  switch (event) {
  case ARRIVE:
    eventString = "ARRIVE";
    time = 0;
    break;
  case CHECK_IN:
    time = cust.getCheckInTimeDelta();
    eventString = "CHECK_IN";
    break;
  case START_VAC:
    time = cust.getStartVaccinationTimeDelta();
    eventString = "START_VAC";
    break;
  case END_VAC:
    time = cust.getEndVaccinationTimeDelta();
    eventString = "END_VAC";
    break;
  case FINISH:
    time = cust.getTotalTimeDelta();
    eventString = "FINISH";
    break;
  }

  mutex mut;
  lock_guard<mutex> lock(mut);
  fstream ofs(file, ios_base::app);
  if (ofs.is_open()) {
    ofs << " [" << getLogLevel() << "] " << eventString << " " << cust.getSSN()
        << " " << time << endl;
  }

  ofs.close();
}

string Logger::getFile() { return file; }

void Logger::setFile(string f) { file = f; }

string Logger::getLogLevel() {
  switch (logLevel) {
  case INFO:
    return "INFO";
    break;
  case WARNING:
    return "WARNING";
    break;
  case ERROR:
    return "ERROR";
    break;
  case NONE:
    return "NONE";
    break;
  }
}

void Logger::setLogLevel(LogLevel lvl) { logLevel = lvl; }

string Logger::dumpLog() {
  stringstream os;

  fstream f(file);
  string buffer;
  if (f.is_open()) {
    while (f) {
      getline(f, buffer);
      os << buffer;
    }
  }

  f.close();
  return os.str();
};

void Logger::clearLog() {
  std::ofstream f;
  f.open(file, std::ofstream::out | std::ofstream::trunc);
  f.close();
}
