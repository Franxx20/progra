#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Tipos.h"

void crearCola_res(t_cola* cola);
int aColar_res(t_cola* cola, const t_dato* dato);
int deColar_res(t_cola* cola, t_dato* dato);
int verTope_res(t_cola* cola, t_dato* dato);
void vaciarCola_res(t_cola* cola);

void crearCola(t_cola* cola);
int aColar(t_cola* cola, const t_dato* dato);
int deColar(t_cola* cola, t_dato* dato);
int verTope(t_cola* cola, t_dato* dato);
void vaciarCola(t_cola* cola);
void vaciarCola1(t_cola* cola);
#endif // COLA_H_INCLUDED
