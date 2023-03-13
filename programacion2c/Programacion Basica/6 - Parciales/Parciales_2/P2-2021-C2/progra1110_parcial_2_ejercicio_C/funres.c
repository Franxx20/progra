#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "funres.h"

#define ESNUMERO(X) ((X) >= '0' && (X) <= '9')

int calcularDigito(char *nroCuenta);
int validarCuenta(char *nroCuenta);
void parsearMovimientos(tMovimientos *movi, char *str);
int cmp_nroCuenta(const void *data_1, const void *data_2);
int sumMovimientos(void *data_1, const void *data_2);
void mostrarCuentas(const void *data, FILE *stream);

int loteCuentas(const char *filename)
{
    tCuentas vec[] = {
        {"123456/", 200.00},
        {"456789/", 100.00},
        {"456897/", 500.00},
        {"564321/", 300.00},
        {"654321/", 400.00},
        {"789654/", 800.00},
        {"987654/", 600.00},
    };

    FILE *lote = fopen(filename, "wb");
    size_t i;

    if(!lote) {
        return 0;
    }

    for(i = 0; i < sizeof(vec)/sizeof(vec[0]); i++) {
        char aux[100];
        sprintf(aux, "%s%d", vec[i].nroCuenta, calcularDigito(vec[i].nroCuenta));
        strcpy(vec[i].nroCuenta, aux);
        fwrite(&vec[i], sizeof(tCuentas), 1, lote);
    }

    fclose(lote);
    return 1;
}


int loteMovimientos(const char *filename)
{
    tMovimientos vec[] = {
        {"123456/4", 'D', 1200.10}, /*NoValido*/
        {"123456/3", 'C', 150.10},  /*Valido*/
        {"287896/9", 'C', 4560},    /*NoValido*/
        {"321456/9", 'D', 235},     /*NoValido*/
        {"456897/1", 'C', 245.80},  /*Valido*/
        {"456897/K", 'D', 6978.55}, /*NoValido*/
        {"654321/3", 'D', 1000}     /*Valido*/
    };
    FILE *lote = fopen(filename, "wt");
    size_t i;

    if(!lote) {
        return 0;
    }

    for(i = 0; i < sizeof(vec)/sizeof(vec[0]); i++) {
        fprintf(lote, "%8s%c%15f\n", vec[i].nroCuenta,
            vec[i].tipoMov, vec[i].importe);
    }
    fclose(lote);
    return 1;
}


int resolucion(const char *cuentas, const char *movimientos)
{
    tMovimientos moviAux;
    tCuentas cuentasAux;

    int n;
    char str[100];
    tLista list;
    FILE *fCuentas = fopen(cuentas, "rb"),
         *fMovi = fopen(movimientos, "rt");

    if(!fCuentas || !fMovi) {
        if(fCuentas) {
            fclose(fCuentas);
        }
        if(fMovi) {
            fclose(fMovi);
        }
        return 0;
    }

    crearLista(&list);

    fread(&cuentasAux, sizeof(tCuentas), 1, fCuentas);
    lista_insertar(&list, &cuentasAux, sizeof(tCuentas));

    while(!feof(fCuentas)) {
        fread(&cuentasAux, sizeof(tCuentas), 1, fCuentas);
        lista_insertar(&list, &cuentasAux, sizeof(tCuentas));
    }


    while(fgets(str, sizeof(str), fMovi)) {

        parsearMovimientos(&moviAux, str);

        if(validarCuenta(moviAux.nroCuenta) &&
           lista_buscar(&list, &moviAux, cmp_nroCuenta) != -1)
        {

            lista_insertarOrdenado(&list, &moviAux, sizeof(tCuentas),
                                    cmp_nroCuenta, sumMovimientos);
        }

    }


    do {
        printf("Ingrese los ulitmos n elementos a ver > ");
        scanf("%d", &n);

        if(n) {
            puts("nro.Cuenta\tSaldo");
        }

        if(!lista_mostrarN_Ultimos(&list, n, mostrarCuentas, stdout)) {
            printf("NO HAY %d CUENTAS\n", n);
        }

    } while( n != 0);

    fclose(fCuentas);
    fclose(fMovi);
    vaciarLista(&list);
    return 1;
}


/*    Funciones Privadas    */
int calcularDigito(char *nroCuenta)
{
    int impares = 0,
        pares = 0,
        pos = 100,
        i;

    for(i = 0; ESNUMERO(*nroCuenta); i++, nroCuenta++) {
        if(i % 2 == 0) {
            pares += (*nroCuenta - '0') * pos;
        }
        else {
            impares += (*nroCuenta - '0') * pos;
            pos /= 10;
        }
    }

    pos = pares - impares;
    if(pos < 0) {
        pos *= -1;
    }

    do {
        int rc = 0;
        while(pos) {
            rc += pos % 10;
            pos /= 10;
        }
        pos = rc;
    } while(pos > 9);

    return pos;
}


int validarCuenta(char *nroCuenta)
{
    int digitoValido = calcularDigito(nroCuenta);
    char *aux = strchr(nroCuenta, '/') + 1;

    if(ESNUMERO(*aux) && digitoValido == (*aux - '0')) {
        return 1;
    }

    return 0;
}


void parsearMovimientos(tMovimientos *movi, char *str)
{
    char *aux = str+24;
    *aux = '\0';

    aux -= 15;
    sscanf(aux, "%15lf", &movi->importe);
    *aux = '\0';

    sscanf(aux-1, "%c", &movi->tipoMov);
    aux--;
    *aux = '\0';

    strcpy(movi->nroCuenta, str);
}


int cmp_nroCuenta(const void *data_1, const void *data_2)
{
    tCuentas *_cuenta = (tCuentas *)data_1;
    tMovimientos *_movi = (tMovimientos *)data_2;
    int rc = strcmp(_cuenta->nroCuenta, _movi->nroCuenta);
    return rc;
}


int sumMovimientos(void *data_1, const void *data_2)
{
    tCuentas *_cuenta = (tCuentas *)data_1;
    tMovimientos *_movi = (tMovimientos *)data_2;

    (_movi->tipoMov == 'D')? (_cuenta->saldo -= _movi->importe):
        (_cuenta->saldo += _movi->importe);

    return 1;
}


void mostrarCuentas(const void *data, FILE *stream)
{
    tCuentas *_cuenta = (tCuentas *)data;
    fprintf(stream, "%s\t%.2f\n", _cuenta->nroCuenta, _cuenta->saldo);
}
