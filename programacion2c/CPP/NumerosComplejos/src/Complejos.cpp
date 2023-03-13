#include "../include/Complejos.h"

using namespace std;

Complejos::Complejos() {
  this->_i = 0;
  this->_r = 0;
}

Complejos::Complejos(int i, int r) {
  this->_i = i;
  this->_r = r;
}

ostream &operator<<(ostream &os, Complejos &comp) {
  os << "(" << comp._i << "," << comp._r << ")";
  return os;
}
istream &operator>>(istream &is, Complejos &comp) {
  is >> comp._i >> comp._r;
  return is;
}

Complejos Complejos::operator+(const Complejos &c1) const {
  Complejos complejoResultado;
  complejoResultado._r = this->_r + c1._r;
  complejoResultado._i = this->_i + c1._i;

  return complejoResultado;
}

Complejos operator*(int escalar, const Complejos &c1) {
  Complejos complejoResultado;
  complejoResultado._i = c1._i * escalar;
  complejoResultado._r = c1._r * escalar;

  return complejoResultado;
}
Complejos Complejos::operator*(const Complejos &c1) const {
  Complejos complejoResultado;
  complejoResultado._r = this->_r * c1._r - this->_i * c1._i;
  complejoResultado._i = this->_r * c1._i - this->_i * c1._r;

  return complejoResultado;
}
