#ifndef COMPLEJOS_H
#define COMPLEJOS_H

#include <iostream>
#include <ostream>

using namespace std;

class Complejos {

private:
  int _r, _i;

public:
  Complejos();
  Complejos(int r, int i);

  friend ostream &operator<<(ostream &os, Complejos &comp);
  friend istream &operator>>(istream &is, Complejos &comp);
  Complejos operator+(const Complejos &c1) const;
  friend Complejos operator*(int escalar, const Complejos &c1);
  Complejos operator*(const Complejos &c1) const;
};

#endif // COMPLEJOS_H
