#include <stdio.h>
#include <string.h>
#include "../lista/lista_simple.h"
#include "res.h"

#define ABS(X)	((X) < 0? (X) * -1 : (X))

int cmpAntiguedad(const void *data_1, const void *data_2);
int promediarKms(void *data_1, const void *data_2);
void mostrarProm(const void *data, FILE *stream);

int crearLote(const char *filename)
{
	tVehiculo vec[] = {
		{"AAA111", 10, 200},
		{"BBB111", 5, 100.12},
		{"AAA222", 10, 300},
		{"CCC111", 1, 100},
		{"DDD111", 5, -505.54},
	};

	FILE *lote = fopen(filename, "wb");
	size_t i;

	if(!lote) {
		return 0;
	}

	for(i = 0; i < sizeof(vec)/sizeof(vec[0]); i++) {
		fwrite(&vec[i], sizeof(tVehiculo), 1, lote);
	}

	fclose(lote);
	return 1;
}


int resolucion(const char *filename)
{
	FILE *archivo;
	tVehiculo vehi;
	tPromedio prom;
	tLista listProd;

	if(!(archivo = fopen(filename, "rb"))) {
		return 0;
	}

	crearLista(&listProd);

	fread(&vehi, sizeof(tVehiculo), 1, archivo);
	while(!feof(archivo)) {

		prom.antiguedad = vehi.antiguedad;
		prom.cant_vehi = 1;
		prom.total_kms_recorridos = vehi.kms_recorridos;
		prom.promedio = prom.total_kms_recorridos / prom.cant_vehi;

		lista_insertarOrdenado(&listProd, &prom, sizeof(tPromedio),
										cmpAntiguedad, promediarKms);
		fread(&vehi, sizeof(tVehiculo), 1, archivo);
	}

	fclose(archivo);

	lista_mostrar(&listProd, mostrarProm, stdout);
	vaciarLista(&listProd);

	return 1;
}


/** Funciones Privadas **/
int cmpAntiguedad(const void *data_1, const void *data_2)
{
	tPromedio *prom_1 = (tPromedio *)data_1,
				 *prom_2 = (tPromedio *)data_2;

	return prom_1->antiguedad - prom_2->antiguedad;
}


int promediarKms(void *data_1, const void *data_2)
{
	tPromedio *prom_1 = (tPromedio *)data_1,
				 *prom_2 = (tPromedio *)data_2;

	prom_1->cant_vehi++;
	prom_1->total_kms_recorridos += ABS(prom_2->total_kms_recorridos);
	prom_1->promedio = prom_1->total_kms_recorridos / prom_1->cant_vehi;

	return 1;
}


void mostrarProm(const void *data, FILE *stream)
{
	tPromedio *prom = (tPromedio *)data;
	fprintf(stream, "%d\t%.2f\n", prom->antiguedad, prom->promedio);
}
