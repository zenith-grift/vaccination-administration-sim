#include "UniformDistribution.h"

const unsigned int PRECISSION = 100;

UniformDistribution::UniformDistribution(unsigned int l, unsigned int h)
    : low(l), high(h) {
  distribution =
      uniform_int_distribution<unsigned int>(l * PRECISSION, h * PRECISSION);
}

double UniformDistribution::pullSample() {
  unsigned int sample = distribution(engine);
  double scaled = (float)sample / (float)PRECISSION;
  return scaled;
}
