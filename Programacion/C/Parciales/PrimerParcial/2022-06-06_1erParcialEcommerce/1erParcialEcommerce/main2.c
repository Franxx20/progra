#include <stdio.h>
#include "../Solucion1erParcialEcommerce/Solucion1erParcialEcommerce.h"


#define ARG_CLIENTES    1
#define ARG_PRODUCTOS   2
#define ARG_REGLAS      3
#define ARG_OFERTAS     4


int main(int argc, char* argv[])
{
    generarArchivoClientes(argv[ARG_CLIENTES]);
    generarArchivoProductos(argv[ARG_PRODUCTOS]);
    generarArchivoReglas(argv[ARG_REGLAS]);

    generarArchivoOfertas(argv[ARG_CLIENTES], argv[ARG_PRODUCTOS], argv[ARG_REGLAS], argv[ARG_OFERTAS]);
///    generarArchivoOfertas_ALU(argv[ARG_CLIENTES], argv[ARG_PRODUCTOS], argv[ARG_REGLAS], argv[ARG_OFERTAS]);

    if(mostrarArchivoOfertas(argv[ARG_OFERTAS]) != TODO_OK)
        printf("\n\nError al mostrar el archivo de ofertas.\n");
    
    char nombreArchivoOfertasTxt[251];
    cambiarExtension(argv[ARG_OFERTAS], nombreArchivoOfertasTxt, ".txt");
    
    generarArchivoOfertasTxt(argv[ARG_OFERTAS], nombreArchivoOfertasTxt);
///    generarArchivoOfertasTxt_ALU(argv[ARG_OFERTAS], nombreArchivoOfertasTxt);

    if(mostrarArchivoOfertasTxt(nombreArchivoOfertasTxt))
        printf("\n\nError al mostrar el archivo de ofertas txt.\n");

    return 0;
}


int generarArchivoOfertas_ALU(const char* nombreArchClientes, const char* nombreArchProductos, const char* nombreArchReglas, const char* nombreArchOfertas)
{
    return TODO_OK;    
}


int generarArchivoOfertasTxt_ALU(const char* nombreArchivoOfertas, const char* nombreArchivoOfertasTxt)
{
    return TODO_OK;
}
