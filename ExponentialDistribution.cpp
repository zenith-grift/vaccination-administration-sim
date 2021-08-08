#include "ExponentialDistribution.h"

ExponentialDistribution::ExponentialDistribution(int r) : rate(r) {
  distribution = exponential_distribution<double>(r);
}

double ExponentialDistribution::pullSample() {
  double sample = distribution(engine);

  cout << "sample: " << sample << endl;
  return sample;
}
