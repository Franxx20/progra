#ifndef SOLUCIONPARCIALARCHIVOCOLA_H
#define SOLUCIONPARCIALARCHIVOCOLA_H

#include <stdio.h>

#define TODO_OK		0
#define ERR_ARCHIVO 1


typedef struct
{
	char codArt[7];
	char codMatPri[7];
	int cantidad;
	float costoUnit;
}
MatPrimaArt;


int procesarArchProductos(const char* nombreArchProd, const char* nombreArchProdMas1000, const char* nombreArchProdMenos1000);
void generarArchivoProductos();
void mostrarArchivoProd(const char* nombreArchProd);
void mostrarMatPrimaArt(MatPrimaArt* matPrimaArt);


#endif // SOLUCIONPARCIALARCHIVOCOLA_H
