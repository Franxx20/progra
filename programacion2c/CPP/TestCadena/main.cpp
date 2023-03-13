#include "../Cadena/include/Cadena.h"
#include <cstdio>
#include <iostream>
using namespace std;

void funcionQueRecibeCopia(Cadena &copia);

int main() {
  Cadena c1("Hola");
  Cadena c5 = "Hola Mundo!";
  Cadena c6;
  c6 = c1;
  funcionQueRecibeCopia(c6);

  cout << c1 << endl;
  printf("Cadena C1 %s\n", c1.getCadena());
  cout << c5 << endl;

  cout << "Caracter: " << c1[2] << endl;

  if (c1 == c6) {
    cout << "C1 es igual a C6" << endl;
  } else
    cout << "C1 no es igual a C6" << endl;
  return 0;
}

void funcionQueRecibeCopia(Cadena &copia) {
  cout << "Comiendo de funcion " << endl;
  cout << copia << endl;
  Cadena c2(" Mundo Concat!");
  Cadena c3;
  c3 = copia + c2;

  cout << c3 << endl;
  cout << "Fin de funcion" << endl;
}
