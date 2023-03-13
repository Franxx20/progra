#ifndef FUNRES_H_INCLUDED
#define FUNRES_H_INCLUDED

#define NROCUENTA_SIZE  40

typedef struct c {
    char nroCuenta[NROCUENTA_SIZE];
    double saldo;
} tCuentas;

typedef struct m {
    char nroCuenta[NROCUENTA_SIZE];
    char tipoMov;
    double importe;
} tMovimientos;

int loteCuentas(const char *filename);
int loteMovimientos(const char *filename);
int resolucion(const char *cuentas, const char *movimientos);

#endif
