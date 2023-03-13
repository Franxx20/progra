#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define N 4 //Equipos 1-4
#define EQUIPOS 3 //Equipos 0-3 aplicable para vectores y matrices
#define TOTAL 2

void carga(int m[][N], int partido);
void puntaje(int m[][N], int v[N]);
void inspeccionar(int m[][N]);

#endif // MAIN_H_INCLUDED
