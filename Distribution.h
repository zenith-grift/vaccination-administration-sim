//
// Created by Josh Frandsen on 7/27/21.
//

#ifndef PROJECT2_JFRANDSEN_DISTRIBUTION_H
#define PROJECT2_JFRANDSEN_DISTRIBUTION_H

#include <iostream>
#include <random>
#include <string>

using namespace std;

class Distribution {
public:
  virtual double pullSample() = 0;
};

#endif // PROJECT2_JFRANDSEN_DISTRIBUTION_H
