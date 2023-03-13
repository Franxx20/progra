#ifndef SOLUCION_FACTURACION_ELECTRO_H
#define SOLUCION_FACTURACION_ELECTRO_H

#define ERR_ARCHIVO 1

#include "../Fecha/Fecha.h"

typedef struct
{
	int nroCliente;
	char nombre[50];
	Fecha fechaUltMedicion;
	int valorMedidor;
	Mes ultMesFacturado;
	double ultConsumoMes;
}
Cliente;


typedef struct
{
	int nroFactura;
	int nroCliente;
	Fecha fechaUltMedicion;
	int valorMedidor;
	Mes mesFacturado;
	double consumoMes;
}
Factura;


typedef struct
{
	int nroCliente;
	Fecha fechaMedicion;
	int valorMedidor;
}
Medicion;


int generarArchivos();

int generarFacturas
(
	const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas,
	int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar
);

int mostrarFacturas(const char* nombreArchivoFacturas);
int mostrarClientes(const char* nombreArchivoClientes);
int mostrarMediciones(const char* nombreArchivoMediciones);


#endif // SOLUCION_FACTURACION_ELECTRO_H
