#include "Fecha.h"
#include <stdio.h>

void ingresarFecha(Fecha *f) {
  puts("Ingrese una fecha (D/M/A): ");
  fflush(stdin);
  scanf("%d %d %d", &f->dia, &f->mes, &f->anio);

  while (!esFechaValida(f)) {
    puts("Fecha invalida. Ingrese una fecha (D/M/A): ");
    fflush(stdin);
    scanf("%d %d %d", &f->dia, &f->mes, &f->anio);
  }
}

int esFechaValida(Fecha *f) {
  if (f->anio >= 1601)
    if (f->mes >= 1 && f->mes <= 12)
      if (f->dia >= 1 && f->dia <= cantDiasMes(f->mes, f->anio))
        return VERDADERO;
  return FALSO;
}

int esBisiesto(int anio) {
  return anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0);
}

int cantDiasMes(int mes, int anio) {
  static int cmd[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (mes == 2 && esBisiesto(anio))
    return 29;

  return cmd[mes];
}
void sumarDiasAFecha(const Fecha *fecha, int dias, Fecha *fechaSuma) {
  *fechaSuma = *fecha;

  fechaSuma->dia += dias;

  int cdm;
  while (fechaSuma->dia >
         (cdm = cantDiasMes(fechaSuma->mes, fechaSuma->anio))) {
    fechaSuma->dia -= cdm;
    // fechaSuma->mes++;

    // if (fechaSuma->mes > 12) {
    //   fechaSuma->mes = 1;
    //   fechaSuma->anio++;
    // }

    fechaSuma->anio = fechaSuma->anio + fechaSuma->mes / 12;
    fechaSuma->mes = fechaSuma->mes % 12 + 1;
  }
}

void ingresarEnteroPositivo(const char *mensaje, int *numero) {
  puts(mensaje);
  fflush(stdin);
  scanf("%d", numero);

  while (*numero <= 0) {
    printf("Numero invalido. Ingrese nuevamente: ");
    fflush(stdin);
    scanf("%d", numero);
  }
}
void mostrarFecha(Fecha *f) { printf("%d %d %d\n", f->dia, f->mes, f->anio); }

int difDiasEntreFechas(const Fecha *f1, const Fecha *f2) {
  int difDias = f2->dia - f1->dia;

  for (int mActual = f1->mes, aActual = f1->anio;
       aActual * 100 + mActual < f2->anio * 100 + f2->mes;
       aActual = aActual + mActual / 12, mActual %= 12, mActual++)
    difDias += cantDiasMes(mActual, aActual);
  return difDias;
}
