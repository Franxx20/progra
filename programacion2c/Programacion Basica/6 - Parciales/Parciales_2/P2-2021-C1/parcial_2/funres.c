#include <stdio.h>
#include <string.h>
#include "funres.h"

#define ES_DIGITO(n)	((n) >= '0' && (n) <= '9')

unsigned sumatoria(int *vec, int tam);
void string_toArray(char *str, int *vec);
void parsearAlumno(alumno *alumn, char *str);
void _mostrar(const void *data, FILE *stream);
int acumularAlumn(void *data_1, const void *data_2);


void lotePrueba(const char *filename)
{
	alumno alum_vec[] = {
		{801, 7, {7,4,5,8,9,7,6}, 44111222, "Hakurei Reimu"},
		{745, 24, {7,4,5,8,5,8,5,7,8,9,4,5,6,3,2,7,8,9,8,4,7,9,7,6}, 33999777, "Kirisame Marisa"},
		{801, 7, {5,7,8,9,5,6,3}, 22666999, "Cirno"},
		{902, 7, {9,7,8,9,8,10,7}, 99888333, "Udongei Inaba Reisen"},
		{745, 4, {7,8,9,5}, 66444888, "Eiki Shiki"},
	};

	FILE *lote = fopen(filename, "wt");
	size_t i, j;

	for(i = 0; i < sizeof(alum_vec)/sizeof(alum_vec[0]); i++) {

		fprintf(lote, "%lu|%s|%d|{", alum_vec[i].dni, alum_vec[i].apyn,
					alum_vec[i].cant_materias);

		for(j = 0; j < (size_t)alum_vec[i].cant_materias - 1; j++) {
			fprintf(lote, "%d,", alum_vec[i].notas_materias[j]);
		}

		fprintf(lote, "%d}|%d\n", alum_vec[i].notas_materias[j],
					alum_vec[i].codigo_carrera);
	}

	fclose(lote);
}


int resolucion(const char *filename, comparar compararOrden, int orden)
{
	alumno alumn;
	materias mat;

	tLista list;
	char str[400];
	FILE *lote = fopen(filename, "rt");

	if(!lote) {
		return 0;
	}
	crearLista(&list);

	while(fgets(str, sizeof(str), lote)) {
		parsearAlumno(&alumn, str);

		mat.alumn = alumn;
		mat.cant_alumnos = 1;
		mat.notas_sumatoria = sumatoria(alumn.notas_materias, alumn.cant_materias);
		mat.promedio = (float)mat.notas_sumatoria / (alumn.cant_materias * mat.cant_alumnos);

		lista_insertarOrdenado(&list, &mat, sizeof(materias),
					compararOrden, acumularAlumn, &orden);
	}

	puts("cant.Materias | cod.Carrera | promedio | cant.Alumnos");
	lista_mostrar(&list, _mostrar, stdout);

	vaciarLista(&list);
	fclose(lote);

	return 1;
}


int cmp_materiasCarreras(const void *data_1, const void *data_2, void *params)
{
	int *orden = (int *)params;
	materias *mat_1 = (materias *)data_1,
			   *mat_2 = (materias *)data_2;

	int rc = (mat_1->alumn.cant_materias - mat_2->alumn.cant_materias) * (*orden);

	if(!rc && mat_1->alumn.codigo_carrera != mat_2->alumn.codigo_carrera) {
		rc = (mat_1->alumn.codigo_carrera - mat_2->alumn.codigo_carrera) * (*orden);
	}

	return rc;
}


int cmp_carrerasMaterias(const void *data_1, const void *data_2, void *params)
{
	int *orden = (int *)params;
	materias *mat_1 = (materias *)data_1,
			   *mat_2 = (materias *)data_2;

	int rc = (mat_1->alumn.codigo_carrera - mat_2->alumn.codigo_carrera) * (*orden);

	if(!rc && mat_1->alumn.cant_materias != mat_2->alumn.cant_materias) {
		rc = (mat_1->alumn.cant_materias - mat_2->alumn.cant_materias) * (*orden);
	}

	return rc;
}

/* Funciones Privadas */
void parsearAlumno(alumno *alumn, char *str)
{
	char *aux = &str[strcspn(str, "\n")];
	*aux = '\0';

	/*Cod. Carrera*/
	aux = strrchr(str, '|');
	sscanf(aux + 1, "%d", &alumn->codigo_carrera);
	*aux = '\0';

	/*Notas Materias*/
	aux = strrchr(str, '|');
	string_toArray(aux+1, alumn->notas_materias);
	*aux = '\0';

	/*Cant. Materias*/
	aux = strrchr(str, '|');
	sscanf(aux + 1, "%d", &alumn->cant_materias);
	*aux = '\0';

	/*APYN*/
	aux = strrchr(str, '|');
	strcpy(alumn->apyn, aux+1);
	*aux = '\0';

	/*DNI*/
	sscanf(str, "%lu", &alumn->dni);
}


void string_toArray(char *str, int *vec)
{
	unsigned i = 0;

	while(*str) {
		if(ES_DIGITO(*str)) {
			vec[i++] = (*str) - '0';
		}
		str++;
	}
}


int acumularAlumn(void *data_1, const void *data_2)
{
	materias *mat_1 = (materias *)data_1,
			   *mat_2 = (materias *)data_2;

	mat_1->cant_alumnos++;

	mat_1->notas_sumatoria += sumatoria(mat_2->alumn.notas_materias, mat_2->alumn.cant_materias);
	mat_1->promedio = (float)mat_1->notas_sumatoria / (mat_1->alumn.cant_materias * mat_1->cant_alumnos);

	return 1;
}


unsigned sumatoria(int *vec, int tam)
{
	int i;
	unsigned sum = 0;

	for(i = 0; i < tam; i++) {
		sum += vec[i];
	}

	return sum;
}


void _mostrar(const void *data, FILE *stream)
{
	materias *mat = (materias *)data;
	fprintf(stream, " %*d | %*d | %*.2f | %*u\n", 12, mat->alumn.cant_materias,
			11, mat->alumn.codigo_carrera, 8, mat->promedio, 12, mat->cant_alumnos);
}

