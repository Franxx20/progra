#ifndef FUNRES_H_INCLUDED
#define FUNRES_H_INCLUDED

#include "lista/lista.h"

#define CANT_MATERIAS	50
#define APYN_SIZE			30

typedef struct a {

	int codigo_carrera,
		 cant_materias,
		 notas_materias[CANT_MATERIAS];
	size_t dni;
	char apyn[APYN_SIZE];

} alumno;

typedef struct b {

	alumno alumn;
	unsigned cant_alumnos,
				notas_sumatoria;
	float		promedio;

} materias;

void lotePrueba(const char *filename);
int resolucion(const char *filename, comparar compararOrden, int orden);

int cmp_materiasCarreras(const void *data_1, const void *data_2, void *params);
int cmp_carrerasMaterias(const void *data_1, const void *data_2, void *params);

#endif
