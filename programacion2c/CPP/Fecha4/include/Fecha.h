#ifndef FECHA_H
#define FECHA_H

#include <iostream>

#define ANIO_BASE 1601

using namespace std;

class Fecha {
private:
  int diaRel;

  static const int acumDiasMes[14];
  static const int acumDiasMesBis[14];
  static const int diasMes[13];
  static const int diasMesBis[13];
  static int diaDelAnio(int dia, int mes, int anio);
  static bool esBisiesto(int anio);
  static bool esFechaValida(int dia, int mes, int anio);

public:
  Fecha();
  Fecha(int dia, int mes, int anio);
  Fecha(const Fecha &otraFecha);

  Fecha operator+(int dias) const;
  Fecha &operator+=(int);
  Fecha operator++(int); // postincremento fecha++
  Fecha &operator++();   // preincremento ++fecha
  int operator+(const Fecha &otraFecha) const;

  Fecha operator-(int dias) const;
  Fecha &operator-=(int);
  Fecha operator--(int); // posdecremento fecha--
  Fecha &operator--();   // predecrement --fecha
  int operator-(const Fecha &otraFecha)
      const; // const al final indica que no se modifica el objeto llamador

  void setDMA(int dia, int mes, int anio);
  void getDMA(int &dia, int &mes, int &anio) const;
  // métodos de comparación (< > <= >= == !=)
  bool operator<(const Fecha &otraFecha) const;
  bool operator<=(const Fecha &otraFecha) const;
  bool operator>(const Fecha &otraFecha) const;
  bool operator>=(const Fecha &otraFecha) const;
  bool operator==(const Fecha &otraFecha) const;
  bool operator!=(const Fecha &otraFecha) const;

  // TODO: Investigar uso de cin
  // TODO: Investigar funciones friends

  // Funcion friend
  friend ostream &operator<<(ostream &os, const Fecha &f);
};

istream &operator>>(istream &is, Fecha &f);

#endif // FECHA_H
