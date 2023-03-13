#ifndef SOLUCION1ERPARCIALARMADOPC_H
#define SOLUCION1ERPARCIALARMADOPC_H

#include <Lista.h>


void generarArchivoStockComponentes(const char* pathComponentes);
void generarArchivoArmadosYReparaciones(const char* pathArmYRep);
void mostrarArchivoComponentes(const char* pathComponentes);
void mostrarArchivoArmadoYRep(const char* pathArm);
void cargarArmadosYRepEnLista(const char* pathArmYRep, t_lista* pl);

void actualizarComponentes_res(const char* pathComponentes, const char* pathArmadoYRep);
void actualizarComponentes(const char* pathComponentes, const char* pathArmadoYRep);

void obtenerPathIdx_res(const char* pathComponentes, char* pathComponentesIdx);
void obtenerPathIdx(const char* pathComponentes, char* pathComponentesIdx);


t_indComponente* cargarIndiceComponentes_res(const char* pathComponentesIdx, int* ceInd);
t_indComponente* cargarIndiceComponentes(const char* pathComponentesIdx, int* ceInd);

int buscarEnIndice_res(t_indComponente* indice, int ce, const char* codigo);
int buscarEnIndice(t_indComponente* indice, int ce, const char* codigo);


int comparacion(const void* dato1, const void* dato2);
void actualizar(void* dato1, const void* dato2);

#endif // SOLUCION1ERPARCIALARMADOPC_H_INCLUDED
