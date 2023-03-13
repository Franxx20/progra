#ifndef SOLUCION1ERPARCIALARMADOPC_H
#define SOLUCION1ERPARCIALARMADOPC_H

#include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#include "../TDAArbolImplDinamica/TDAArbolImplDinamica.h"

#define TODO_OK			0
#define ERR_CARGA_IND	1


void generarArchivoStockComponentes(const char* pathComponentes);
void generarArchivoArmadosYReparaciones(const char* pathArmYRep);
void mostrarArchivoComponentes(const char* pathComponentes);
void mostrarArchivoArmadoYRep(const char* pathArm);
void cargarArmadosYRepEnLista(const char* pathArmYRep, Lista* pl);
int actualizarComponentes(const char* pathComponentes, const char* pathArmadoYRep);
void obtenerPathIdx(const char* pathComponentes, char* pathComponentesIdx);
int cargarIndiceComponentes(const char* pathComponentesIdx, Arbol* pa);


#endif // SOLUCION1ERPARCIALARMADOPC_H_INCLUDED
