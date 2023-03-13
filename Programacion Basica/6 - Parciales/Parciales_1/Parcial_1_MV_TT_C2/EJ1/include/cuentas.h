/*Marco_Agustin_Marcelo_42572925*/

#ifndef CUENTAS_H_INCLUDED
#define CUENTAS_H_INCLUDED

#define SIZE 12

typedef struct c {

	char numeroDeCuenta[SIZE];
	float saldo;

} cuenta;

typedef struct m {

	char numeroDeCuenta[SIZE];
	char operacion;
	float importe;

} movimiento;


int crearCuentas(const char *filename);
int mostrarCuentas(const char *filename);
int crearMovimientos(const char *filename);
int actualizarCuentas(const char *cuentas_file, const char* movimientos_file,
					  const char *error_file);

#endif
