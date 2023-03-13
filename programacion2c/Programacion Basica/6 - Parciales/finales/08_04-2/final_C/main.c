#include <stdio.h>
#include <stdlib.h>
#include "res/res.h"

int main()
{
	const char *archivo = "vehiculos.dat";

	if(!crearLote(archivo)) {
		printf("[ERROR] - No se pudo crear el archivo %s\n", archivo);
	}

	if(!resolucion(archivo)) {
		printf("[ERROR] - No se pudo abrir el archivo %s\n", archivo);
	}

	return 0;
}
