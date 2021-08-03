//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_LOGGER_H
#define PROJECT2_JFRANDSEN_LOGGER_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

#include "Customer.h"

using namespace std;

enum LogLevel { INFO, WARNING, ERROR, NONE };

class Logger {
private:
  string file;
  LogLevel logLevel;

public:
  Logger(string f, LogLevel lvl);

  void log(string event, const Customer &cust);
  string getFile();
  void setFile(string f);
  string getLogLevel();
  void setLogLevel(LogLevel lvl);
  string dumpLog();
  void clearLog();
};

#endif // PROJECT2_JFRANDSEN_LOGGER_H
