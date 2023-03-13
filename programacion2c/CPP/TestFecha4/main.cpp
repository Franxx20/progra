#include "../Fecha4/include/Fecha.h"
#include <iostream>
#include <locale.h>
#define ERR_FECHA -1
#define ERR_MEMORIA -2
#define ERR_DESCONOCIDO -3
using namespace std;

int main() {
  setlocale(LC_CTYPE, "spanish");
  Fecha fDefault;
  Fecha fecha1;
  // objeto temporal dura para hacer la asignacion y lueg se destruye
  // fecha1 = Fecha(1, 1, 2022);
  cout << "Ingrese una fecha (dd mm aaaa)";
  cin >> fecha1;
  Fecha fecha2(3, 3, 2025);
  Fecha fecha3(3, 3, 2025);
  Fecha diaDelProgramador(13, 9, 2022);

  /*
  int a=0, b=1;
  a = ++b; // a = 2 ; b = 2
  a = b++; // a = 1 ; b = 2
  */

  Fecha fecha4 = fecha2 + 100;
  cout << "Fecha4: " << fecha4 << endl;

  int dif = fecha1 - diaDelProgramador;

  cout << "Diferencia en dias (Debe ser -255): " << dif << endl;

  Fecha fSuma2 = fecha1 + 60;
  cout << "fSuma2: " << fSuma2 << endl;

  fecha1.setDMA(1, 8, 2020);
  int dia, mes, anio;
  int dia2, mes2, anio2;
  int dia3, mes3, anio3;

  fecha1.getDMA(dia, mes, anio);
  fecha2.getDMA(dia2, mes2, anio2);
  fecha3.getDMA(dia3, mes3, anio3);
  cout << "fecha1 es: " << dia << '/' << mes << '/' << anio << endl;
  cout << "fecha2 es: " << dia2 << '/' << mes2 << '/' << anio2 << endl;
  cout << "fecha3 es: " << dia3 << '/' << mes3 << '/' << anio3 << endl;

  cout << "El dia del programador es: " << diaDelProgramador << endl;

  cout << "Posincremento (13/9/2022): " << diaDelProgramador++ << endl;
  cout << "Preincremento (15/9/2022): " << ++diaDelProgramador << endl;
  bool resultado = fecha1 < fecha2;
  cout << "Fecha 1 < Fecha 2(1 si verdad)" << resultado << endl;
  resultado = fecha1 > fecha2;
  cout << "fecha 1 > fecha 2 (0 si falso)" << resultado << endl;
  resultado = fecha3 >= fecha2;
  cout << "Fecha 3 >= fecha 2(1 si verdad)" << resultado << endl;
  resultado = fecha3 <= fecha2;
  cout << "Fecha 3 <= fecha 2(1 si verdad)" << resultado << endl;
  resultado = fecha3 == fecha2;
  cout << "Fecha 3 == fecha 2(1 si verdad)" << resultado << endl;
  resultado = fecha3 != fecha2;
  cout << "Fecha 3 != fecha 2(0 si falso)" << resultado << endl;
  fecha3--;
  fecha3--;
  fecha3--;
  fecha3.setDMA(28, 2, 2025);
  cout << "Fecha 3:" << fecha3 << endl;
  fecha3 -= 28;
  cout << "Fecha 3 - 28 dias ==" << fecha3 << endl;
  fecha3 += 5;
  cout << "Fecha 3 + 5 dias == " << fecha3 << endl;
  return 0;
}
