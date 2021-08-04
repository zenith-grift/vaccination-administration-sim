//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_EXPONENTIAL_DISTRIBUTION_H
#define PROJECT2_JFRANDSEN_EXPONENTIAL_DISTRIBUTION_H

#include <iostream>
#include <random>
#include <string>

#include "Distribution.h"

using namespace std;

class ExponentialDistribution : public Distribution {
private:
  int rate;
  exponential_distribution<double> distribution;
  default_random_engine engine;

public:
  ExponentialDistribution(int r);
  double pullSample();
  void setRate(int r);
  int getRate();
};

#endif // PROJECT2_JFRANDSEN_EXPONENTIAL_DISTRIBUTION_H
