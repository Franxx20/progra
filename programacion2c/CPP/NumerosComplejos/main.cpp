#include "include/Complejos.h"
#include <iostream>

using namespace std;

int main() {
  Complejos c1(1, 2);
  Complejos c2(2, 1);

  Complejos c3 = c1 + c2;
  cout << c3 << " = " << c1 << " + " << c2 << endl;

  Complejos c4 = 5 * c3;
  cout << c4 << " = " << 5 << " + " << c3 << endl;

  Complejos c5 = c3 * c4;
  cout << c5 << " = " << c3 << " * " << c4 << endl;
  return 0;
}
