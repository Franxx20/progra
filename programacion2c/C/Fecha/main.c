#include "Fecha.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  Fecha fecha;
  ingresarFecha(&fecha);

  if (esFechaValida(&fecha)) {
    printf("%d %d %d es una fecha valida\n", fecha.dia, fecha.mes, fecha.anio);
  } else {
    printf("%d %d %d no es una fecha valida\n", fecha.dia, fecha.mes,
           fecha.anio);
  }

  Fecha fechaSuma;
  int dias;
  ingresarEnteroPositivo("Ingrese un numero de dias: ", &dias);

  sumarDiasAFecha(&fecha, dias, &fechaSuma);

  printf("La fecha sumada es: ");

  mostrarFecha(&fechaSuma);

  int dif = difDiasEntreFechas(&fecha, &fechaSuma);
  printf("\nLa diferencia entre las fechas es de %d dias", dif);
  return 0;
}
