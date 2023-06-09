#ifndef FECHAS_H
#define FECHAS_H


typedef struct
{
	int dia;
	int mes;
	int anio;
}
Fecha;


int esFechaValida(const Fecha* f);
Fecha sumarDiasAFecha(const Fecha* f, unsigned dias);
void sumarDiasAFechaInSitu(Fecha* f, unsigned dias);
int difEnDiasEntreFechas(const Fecha* f1, const Fecha* f2);
int diaDelAnio(const Fecha* f);
int cmpFechas(const Fecha* f1, const Fecha* f2);


#endif // FECHAS_H
