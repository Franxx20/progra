#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

typedef enum { FALSO, VERDADERO } Booleano;
typedef struct {
  int dia, mes, anio;
} Fecha;

void ingresarFecha(Fecha *f);
int esFechaValida(Fecha *f);
int esBisiesto(int anio);
int cantDiasMes(int mes, int anio);

void sumarDiasAFecha(const Fecha *fecha, int dias, Fecha *fechaSuma);
void ingresarEnteroPositivo(const char *mensaje, int *numero);

void mostrarFecha(Fecha *f);

int difDiasEntreFechas(const Fecha *f1, const Fecha *f2);

#endif // FECHA_H_INCLUDED
