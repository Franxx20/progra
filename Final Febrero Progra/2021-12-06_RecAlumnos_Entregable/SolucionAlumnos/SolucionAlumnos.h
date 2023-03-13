#ifndef UTILITARIAS2DOPALUMNOS_H
#define UTILITARIAS2DOPALUMNOS_H

#include <stdio.h>

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"


void generarArchivo(const char* nombreNotas);
void cargarLista(Lista* pLAlu, const char* nombreNotas);
void procesarLista(Lista* pLAlu);
void mostrarEstadoAM(void* pvd, void* datos);


#endif // UTILITARIAS2DOPALUMNOS_H
