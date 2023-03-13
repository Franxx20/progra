#include "../include/Cadena.h"
#include <string.h>

Cadena::Cadena() {
  this->cadena = new char[1];
  cadena[0] = '\0';
}

Cadena::Cadena(const char *cadena) {
  this->cadena = new char[strlen(cadena) + 1];
  strcpy(this->cadena, cadena);
}

Cadena::Cadena(const Cadena &otra) {
  this->cadena = new char[strlen(otra.cadena) + 1];
  strcpy(this->cadena, otra.cadena);
}

Cadena::~Cadena() {
  cout << "Ejecutando Destructor ..." << endl;
  delete[] cadena;
}

Cadena &Cadena::operator=(const Cadena &otra) {
  if (this == &otra)
    return *this;

  if (strlen(this->cadena) != strlen(otra.cadena)) {
    delete[] this->cadena;
    this->cadena = new char[strlen(otra.cadena) + 1];
  }

  strcpy(this->cadena, otra.cadena);

  return *this;
}

Cadena Cadena::operator+(const Cadena &otra) const {
  Cadena concat;
  delete[] concat.cadena;

  concat.cadena = new char[strlen(this->cadena) + strlen(otra.cadena) + 1];
  strcpy(concat.cadena, this->cadena);
  strcat(concat.cadena, otra.cadena);

  return concat;
}

ostream &operator<<(ostream &os, const Cadena &otra) {
  os << otra.cadena;
  return os;
}

bool Cadena::operator==(const Cadena &otra) const {
  return strlen(this->cadena) == strlen(otra.cadena);
}

bool Cadena::operator!=(const Cadena &otra) const {
  return strlen(this->cadena) != strlen(otra.cadena);
}
bool Cadena::operator<(const Cadena &otra) const {
  return strlen(this->cadena) < strlen(otra.cadena);
}

bool Cadena::operator<=(const Cadena &otra) const {
  return strlen(this->cadena) <= strlen(otra.cadena);
}

bool Cadena::operator>(const Cadena &otra) const {
  return strlen(this->cadena) > strlen(otra.cadena);
}

bool Cadena::operator>=(const Cadena &otra) const {
  return strlen(this->cadena) >= strlen(otra.cadena);
}

char &Cadena::operator[](int subindice) {
  char *aux = this->cadena;
  // aca creo que se puede implementar un try catch
  if (subindice < (int)strlen(this->cadena))
    for (int i = 0; i < subindice; i++) {
      aux++;
    }
  return *aux;
}
const char *Cadena::getCadena() const { return this->cadena; }

int Cadena::getLongitud() const {
  // yes i know i am being lazy yes i know i am being lazy yes i know i am being
  // lazy yes i know i am being lazy yes i know i am being lazy
  return strlen(this->cadena);
}
