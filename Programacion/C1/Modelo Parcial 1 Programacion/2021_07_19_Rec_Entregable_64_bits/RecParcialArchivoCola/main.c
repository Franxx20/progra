#include <stdio.h>
#include <stdlib.h>

///*************************************************************************************
///********************** DESCOMENTAR EL QUE CORRESPONDA *******************************
#include "../TDAColaImplDinamicaCircular/TDAColaImplDinamicaCircular.h"
///#include "../TDAColaImplEstatica/TDAColaImplEstatica.h"
///*************************************************************************************

#include "../TDACola/TDACola.h"
#include "../SolucionParcialArchivoCola/SolucionParcialArchivoCola.h"


int procesarArchProductos_alu(const char* nombreArchProd, const char* nombreArchProdMas1000, const char* nombreArchProdMenos1000);


int main()
{
	generarArchivoProductos();
    
 	puts("Archivo de Productos");
	mostrarArchivoProd("productos.dat");
	
    ///int ret = procesarArchProductos_alu("productos.dat", "ProductosMas1000.dat", "ProductosMenos1000.dat");
    int ret = procesarArchProductos("productos.dat", "ProductosMas1000.dat", "ProductosMenos1000.dat");
    
    if(ret != TODO_OK)
    {
        puts("Hubo un error en el proceso.");
        return ret;
    }
    
    puts("\nArchivo de productos de costo mayor a $1000");
	mostrarArchivoProd("ProductosMas1000.dat");
    
    puts("\nArchivo de productos de costo menor a $1000");
    mostrarArchivoProd("ProductosMenos1000.dat");
    
    return 0;
}


int procesarArchProductos_alu(const char* nombreArchProd, const char* nombreArchProdMas1000, const char* nombreArchProdMenos1000)
{
/// Resolver.
}
