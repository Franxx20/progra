#ifndef FECHAS_H
#define FECHAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dia,
        mes,
        anio;
} tFecha;

void ingresar_fecha(tFecha *f);
int validar_fecha(tFecha *f);
void dia_siguiente(tFecha *f);
void sum_N_dias(tFecha *f, short int N);
void res_N_dias(tFecha *f, short int N);
int diferencia(tFecha *f, tFecha *f1);
void dia_de_la_semana(tFecha *f);

#endif // FECHAS_H
