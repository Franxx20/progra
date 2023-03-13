#include <stdio.h>
#include <stdlib.h>

#include "../SolucionParcialDelivery/TiposDelivery.h"
#include "../SolucionParcialDelivery/SolucionParcialDelivery.h"


int main()
{
	generarArchivoPedidos();
	generarArchivoRecetas();
	generarArchivoIngredientes();
	
	mostrarArchivoPedidos("Pedidos.txt");
	mostrarArchivoRecetas("Recetas.dat");
	
	puts("Ingredientes antes de la actualizacion");
	mostrarArchivoIngredientes("Ingredientes.dat");
	
	int resp;
	///resp = satisfacerPedidos_alu("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
	resp = satisfacerPedidos("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
	
	if(resp != TODO_OK)
	{
		puts("Error actualizando los pedidos.");
		return resp;
	}
	
	puts("Ingredientes despues de la actualizacion");
	mostrarArchivoIngredientes("Ingredientes.dat");
	
	return 0;
}


///Procesa los pedidos del archivo Pedidos.txt, actualizando el archivo Ingredientes.dat, para que éste refleje la cantidad que queda en stock luego de despachar los pedidos.
int satisfacerPedidos_alu(const char* nombreArchPedidos, const char* nombreArchRecetas, const char* nombreArchIngredientes)
{
/// Resolver.
}
