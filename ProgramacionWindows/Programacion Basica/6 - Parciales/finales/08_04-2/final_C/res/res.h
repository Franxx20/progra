#ifndef RES_H
#define RES_H

typedef struct v {

	char dominio[8];
	int antiguedad;
	float kms_recorridos;

} tVehiculo;

typedef struct p {

	unsigned cant_vehi;
	int antiguedad;
	float promedio,
			total_kms_recorridos;

} tPromedio;

int crearLote(const char *filename);
int resolucion(const char *filename);

#endif
