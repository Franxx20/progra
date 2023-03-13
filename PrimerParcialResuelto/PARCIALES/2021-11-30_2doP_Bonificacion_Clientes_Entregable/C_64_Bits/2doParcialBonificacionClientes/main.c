#include <stdio.h>

#include "../Solucion2doParcialBonificacionClientes/Utilitarias2doParcialBonificacionClientes.h"
#include "../Solucion2doParcialBonificacionClientes/Solucion2doParcialBonificacionClientes.h"
#include "../Solucion2doParcialBonificacionClientes/TiposArchivos.h"

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"


void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas);
void listarClientesOrdXBonifDesc_ALU(const char* clientes);


int main()
{
	generarArchivoClientes();
	generarIndiceArchivoClientes();
	generarArchivoVentas();
	
	mostrarArchivoClientes();
	puts("\n");
	
	mostrarArchivoVentas();
	puts("\n");
	
	///bonificarClientes_ALU("Clientes.dat", "Clientes.idx", "Ventas.dat");
	bonificarClientes("Clientes.dat", "Clientes.idx", "Ventas.dat");
	
	puts("Clientes Bonificados");
	mostrarArchivoClientes();
	puts("\n");
	
	///listarClientesOrdXBonifDesc_ALU("Clientes.dat");
	listarClientesOrdXBonifDesc("Clientes.dat");
	
	return 0;
}


void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas)
{
/// Resuelva esta función y todas las que invoque. Coloque el sufijo _ALU a todas ellas. Resuelva todo en este archivo main.c. No modifique ningún otro.
/// main.c es el único archivo que deberá entregar del proyecto C.
}


void listarClientesOrdXBonifDesc_ALU(const char* clientes)
{
/// Resuelva esta función y todas las que invoque. Coloque el sufijo _ALU a todas ellas. Resuelva todo en este archivo main.c. No modifique ningún otro.
/// main.c es el único archivo que deberá entregar del proyecto C.
}
