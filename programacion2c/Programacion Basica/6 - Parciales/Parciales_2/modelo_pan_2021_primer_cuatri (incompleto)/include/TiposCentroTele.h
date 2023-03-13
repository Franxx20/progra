#ifndef TIPOSCENTROTELE
#define TIPOSCENTROTELE

#include <Fecha.h>


typedef struct
{
	int nroCliente;
	char nombre[201];
}
t_cliente;


typedef struct
{
	int nroCliente;
	char nroFactura[14];
	t_fecha fechaVencimiento;
	t_fecha fechaPago;
	double importe;
}
t_pago;


typedef struct
{
	int nroCliente;
	int cantFactImpagasFueraTerm;
}
t_facturasImpagasFueraTerm;


typedef struct
{
	int nroCliente;
	int nroReg;
}
t_indice;


#endif // TIPOSCENTROTELE
