/*Marco_Agustin_Marcelo_42572925*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cuentas.h"
#include "../include/pila.h"

#define ESPAR(X) ((X) % 2 == 0)

/* Funciones Privadas */
void parsearMovimientos(char *str, movimiento *mov);
void realizarImporte(cuenta *c, char op, float imp);
int validacionDeCuenta(char *numeroDeCuenta);
int verificarCuenta(const char *str_1, const char *str_2);


int crearCuentas(const char *filename)
{
    size_t i;
    FILE *fp = fopen(filename, "wb");

    cuenta Cuentas[] = {
        {"321789", 654.486},
        {"340376", 456.68},
        {"425867", 325.48},
        {"637043", 5000.45},
        {"987123", 9875.25},
		{"999999", 42.25}
    };

    if(!fp) {
        return 0;
    }

    for(i = 0; i < sizeof(Cuentas)/sizeof(Cuentas[0]); i++) {

		char _aux[SIZE];
    	int _val = validacionDeCuenta(Cuentas[i].numeroDeCuenta);

		sprintf(_aux, "/%d", _val);
		strncat(Cuentas[i].numeroDeCuenta, _aux, strlen(_aux));

        fwrite(&Cuentas[i], sizeof(cuenta), 1, fp);
    }

    fclose(fp);
    return 1;
}


int mostrarCuentas(const char *filename)
{
    cuenta aux;
    FILE *fp = fopen(filename, "rb");

    if(!fp) {
        return 0;
    }

    fread(&aux, sizeof(cuenta), 1, fp);
    while(!feof(fp)) {
        printf("%s | %f\n", aux.numeroDeCuenta, aux.saldo);
        fread(&aux, sizeof(cuenta), 1, fp);
    }

    fclose(fp);
    return 1;
}


int crearMovimientos(const char *filename)
{
    size_t i;
    FILE *fp = fopen(filename, "wt");

    movimiento Movimientos[] = {
        {"340376/5", 'C', 258.50},
        {"425867/3", 'D', 100.00},
    	{"425867/7", 'D', 100.00},
    	{"425867/7", 'C', 200.00},
    	{"425867/9", 'D', 100.00},
        {"525667/8", 'D', 999.69},
        {"987123/6", 'C', 500.50},
		{"999999/0", 'D', 500.50}
    };

    if(!fp) {
        return 0;
    }

    for(i = 0; i < sizeof(Movimientos)/sizeof(Movimientos[0]); i++) {
        fprintf(fp, "%s|%c|%f\n", Movimientos[i].numeroDeCuenta,
				Movimientos[i].operacion, Movimientos[i].importe);
    }

    fclose(fp);
    return 1;
}


int actualizarCuentas(const char *cuentas_file, const char* movimientos_file,
					  const char *error_file)
{
	int rc;
	char str[100];
	char *cuentas_temp = "_cuentas_temp.dat";

	movimiento mov;
	tPila cuentasInvalidas;
	cuenta cuentaModificar;

	FILE *fError = fopen(error_file, "wt"),
		 *fCuentas = fopen(cuentas_file, "r+b"),
		 *fCuentas_temp = fopen(cuentas_temp, "wb"),
		 *fMovimientos = fopen(movimientos_file, "rt");

    if(!fCuentas || !fMovimientos || !fError || !fCuentas_temp) {
        return 0;
    }

	crearPila(&cuentasInvalidas);

    fread(&cuentaModificar, sizeof(cuenta), 1, fCuentas);
    if(fgets(str, sizeof(str), fMovimientos) && !feof(fCuentas)) {
		parsearMovimientos(str, &mov);
    }

    while(!feof(fMovimientos) && !feof(fCuentas)) {

        rc = verificarCuenta(mov.numeroDeCuenta, cuentaModificar.numeroDeCuenta);

		if(rc == 0) {
			realizarImporte(&cuentaModificar, mov.operacion, mov.importe);

			/* Pasamos al siguiente movimiento */
			if(fgets(str, sizeof(str), fMovimientos)) {
				parsearMovimientos(str, &mov);
			}
		}
		else if(rc < 0) {
			/* La cuenta no se encontraba en el archivo */
			if(!pilaLlena(&cuentasInvalidas, sizeof(movimiento))) {
				ponerEnPila(&cuentasInvalidas, &mov, sizeof(movimiento));
			}

			/* Pasamos al siguiente movimiento */
			if(fgets(str, sizeof(str), fMovimientos)) {
				parsearMovimientos(str, &mov);
			}
		}
		else {
			fwrite(&cuentaModificar, sizeof(cuenta), 1, fCuentas_temp);
			/* El numero de cliente en movimiento es mayor */
			/* Pasamos al siguiente cliente */
			fread(&cuentaModificar, sizeof(cuenta), 1, fCuentas);
		}
    }

    while(!feof(fCuentas)) {
		fwrite(&cuentaModificar, sizeof(cuenta), 1, fCuentas_temp);
		fread(&cuentaModificar, sizeof(cuenta), 1, fCuentas);
    }


    fprintf(fError, "Nro. Cuenta:\tDigito Verificador Correcto:\n");
    while(!pilaVacia(&cuentasInvalidas)) {
		char _str_aux[SIZE] = "";

		sacarDePila(&cuentasInvalidas, &mov, sizeof(movimiento));
		/* Removemos el '/digitoVerificador' de la cadena */
		strncpy(_str_aux, mov.numeroDeCuenta, strcspn(mov.numeroDeCuenta, "/"));
		fprintf(fError, "%s\t\t%d\n", _str_aux, validacionDeCuenta(_str_aux));
    }

    fclose(fError);
    fclose(fCuentas);
    fclose(fMovimientos);
    fclose(fCuentas_temp);

    remove(cuentas_file);
    rename(cuentas_temp, cuentas_file);

    return 1;
}


int verificarCuenta(const char *str_1, const char *str_2)
{
	return strncmp(str_1, str_2, strlen(str_2));
}


void realizarImporte(cuenta *c, char op, float imp)
{
	if(op == 'D') {
		c->saldo -= imp;
	}
	else if(op == 'C') {
		c->saldo += imp;
	}
}


void parsearMovimientos(char *str, movimiento *mov)
{
	char *aux = &str[strcspn(str, "\n")];
	*aux = '\0';

	/*Importe*/
	aux = strrchr(str, '|');
	sscanf(aux + 1, "%f", &mov->importe);
	*aux = '\0';

	/*Operacion*/
	aux = strrchr(str, '|');
	sscanf(aux + 1, "%c", &mov->operacion);
	*aux = '\0';

	/*Nro. Cuenta*/
	strncpy(mov->numeroDeCuenta, str, SIZE - 1);
}


int validacionDeCuenta(char *numeroDeCuenta)
{
	int resultado;
	size_t  pares = 0,
			pos = 100; /* Acomoda la posicion de los digitos */
			impares = 0,
			vueltas = 1;

	while(*numeroDeCuenta) {

		if(vueltas > 2) {
			vueltas = 1;
			pos /= 10;
		}

		if(ESPAR(vueltas)) {
			pares += (*numeroDeCuenta - '0') * pos;
		}
		else  {
			impares += (*numeroDeCuenta - '0') * pos;
		}

		numeroDeCuenta++;
		vueltas++;
	}

	resultado = impares - pares;

	do {
		int res = 0;
		while(resultado > 0) {
			res += (resultado % 10);
			resultado /= 10;
		}
		resultado = res;
	} while(resultado > 9);

	return (int)resultado;
}
