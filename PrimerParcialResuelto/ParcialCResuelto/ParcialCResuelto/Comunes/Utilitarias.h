#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED

#include <stdio.h>
#define PATH_ARCH "simulacion.dat"
#define TAM 3;
int CrearLoteSimulacion();
int sim_cola_res();
int ciclos_espera_paquete_res();
void ver_archivo();
int sim_cola(t_cola* cola, int* tam_max);
int ciclos_espera_paquete();
#endif // UTILITARIAS_H_INCLUDED
