#ifndef CADENA_H
#define CADENA_H
#include <iostream>
using namespace std;

class Cadena {
private:
  char *cadena;

public:
  Cadena();
  Cadena(const char *cadena);

  Cadena(const Cadena &otra);
  ~Cadena();
  Cadena &operator=(const Cadena &otra);

  Cadena operator+(const Cadena &otra) const;
  Cadena &operator+=(const Cadena &otra);

  bool operator==(const Cadena &otra) const;
  bool operator!=(const Cadena &otra) const;
  bool operator<(const Cadena &otra) const;
  bool operator<=(const Cadena &otra) const;
  bool operator>(const Cadena &otra) const;
  bool operator>=(const Cadena &otra) const;
  char &operator[](int subindice);
  const char &operator[](int subindice) const;

  const char *getCadena() const;
  int getLongitud() const;

  friend ostream &operator<<(ostream &os, const Cadena &cadena);
};

#endif // CADENA_H
