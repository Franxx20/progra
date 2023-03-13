#ifndef FECHAS_H
#define FECHAS_H

typedef struct
{
	int dia;
	int mes;
	int anio;
}
Fecha;

int cmpFechas(const Fecha* f1, const Fecha* f2);


#endif // FECHAS_H
