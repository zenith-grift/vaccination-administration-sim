#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>

#include "Logger.h"

using namespace std;

Logger::Logger(string f, LogLevel lvl) : file(f), logLevel(lvl) {}

void Logger::log(string event, const Customer &cust) {
  // [level] event customer time
  fstream ofs(file, ios_base::app);

  auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());

  if (ofs.is_open()) {
    cout << "file is open..." << endl;
    ofs << " [" << getLogLevel() << "] " << event << " " << cust.getSSN() << " "
        << ctime(&time);
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
