#include "Customer.h"
#include <iostream>

using namespace std;
int main() {

  Customer c("josh", 66666666);

  cout << "name: " << c.getName() << ", ssn: " << c.getSSN() << endl;
  return 0;
}
