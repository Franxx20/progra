#ifndef ERPARCIALUTILITARIASDELIVERY_H
#define ERPARCIALUTILITARIASDELIVERY_H

#include <stdio.h>

#include "../TDAColaImplDinamicaCircular/TDAColaImplDinamicaCircular.h"
#include "../TDACola/TDACola.h"

#define TODO_OK						0
#define ERR_ARCHIVO					1
#define ERR_RECETA_NO_ENCONTRADA	2


void generarArchivoPedidos();
void generarArchivoRecetas();
void generarArchivoIngredientes();
void mostrarArchivoPedidos(const char* archPedidos);
void mostrarArchivoRecetas(const char* archRecetas);
void mostrarArchivoIngredientes(const char* archIngredientes);
void mostrarReceta(Receta* receta);
void mostrarIngrediente(Ingrediente* ingrediente);

///Procesa los pedidos del archivo Pedidos.txt, actualizando el archivo Ingredientes.dat, para que éste refleje la cantidad que queda en stock luego de despachar los pedidos.
int satisfacerPedidos_alu(const char* nombreArchPedidos, const char* nombreArchRecetas, const char* nombreArchIngredientes);
int satisfacerPedidos(const char* nombreArchPedidos, const char* nombreArchRecetas, const char* nombreArchIngredientes);


#endif // 1ERPARCIALUTILITARIASDELIVERY_H
