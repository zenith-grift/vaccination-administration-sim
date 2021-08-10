//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_UNIFORM_DISTRIBUTION_H
#define PROJECT2_JFRANDSEN_UNIFORM_DISTRIBUTION_H

#include <random>

#include "Distribution.h"

using namespace std;

const unsigned int PRECISSION = 100;

class UniformDistribution : public Distribution {
private:
  unsigned int low, high;
  uniform_int_distribution<unsigned int> distribution;
  default_random_engine engine;

public:
  UniformDistribution(unsigned int l, unsigned int h);
  double pullSample();
  void setRange(unsigned int l, unsigned int h);
  unsigned int getLow();
  unsigned int getHigh();
};

#endif // PROJECT2_JFRANDSEN_UNIFORM_DISTRIBUTION_H
