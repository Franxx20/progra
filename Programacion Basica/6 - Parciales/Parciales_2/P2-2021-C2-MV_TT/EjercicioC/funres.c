#include <stdio.h>
#include <string.h>
#include "funres.h"
#include "lista/lista.h"

#define TAM_STRING 24

#define SECTOR 4
#define NO_EXISTE -1

#define REPORTAR_ERROR(X, Y, Z)    fprintf((X), "Error %01d - Sector %c - Vehiculo %10s\n", (Y), (Z).sector, (Z).dominio)

/* Funciones privadas */
void parsearLote(tEntradaSalida *io, char *str);
void contarSectores(const void* data, void *params);
int cmp_salida(const void *vehi_1, const void *vehi_2);
int cmp_duplicados(const void *vehi_1, const void *vehi_2);
int cmp_sectorEntrada(const void *vehi_1, const void *vehi_2);
int cmp_vehiculo(const void *vehi_1, const void *vehi_2);


int crearLotePrueba_alumn(const char* filename)
{
    tEntradaSalida vec[] = {
        {1625766103, "GKM925",'E','A'}, /*Error 05*/
        {1625766704, "KAL663",'E','B'},
        {1625767305, "MNJ996",'E','A'},
        {1625767745, "ARR111",'E','B'}, /*Error 05*/
        {1625767778, "ARR111",'S','B'},
        {1625767788, "BCC333",'E','B'}, /*Error 02 y 05*/
        {1625767888, "GKM925",'E','A'}, /*Error 01*/
        {1625767906, "MNJ996",'S','A'},
        {1625768124, "KAL663",'E','D'}, /*Error 03 y 05*/
        {1625768507, "KAL663",'S','B'},
        {1625769999, "ABC999",'S','C'}, /*Error 04*/
    };

    size_t i, tam = sizeof(vec)/sizeof(vec[0]);
    FILE *lote = fopen(filename, "wt");
    if(!lote) {
        return 0;
    }

    for(i = 0; i < tam; i++) {
        fprintf(lote, "%12ld%10s%c%c\n", vec[i].timestamp, vec[i].dominio, vec[i].tipo, vec[i].sector);
    }

    fclose(lote);
    return 1;
}


int generarInforme_alumn(const char* filename, const char* output, const tSector* secs)
{
    int i, rc;
    tLista list;
    unsigned tam;
    char str[100];
    tEntradaSalida io;

    FILE *lote = fopen(filename, "rt"),
         *info = fopen(output, "wt");

    if(!lote || !info) {
        (lote)? fclose(lote) : fclose(info);
        return 0;
    }

    crearLista(&list);

    while(fgets(str, sizeof(str), lote)) {
        parsearLote(&io, str);
        rc = lista_insertar(&list, &io, sizeof(tEntradaSalida),
                            cmp_duplicados, NULL);
        if(rc == DUPLICADO) {
            REPORTAR_ERROR(info, 1, io);
        }
    }


    for(i = 0; i < SECTOR; i++) {
        io.sector = secs[i].code;
        tam = lista_contarDuplicados(&list, &io, sizeof(tEntradaSalida), cmp_sectorEntrada);
        if(tam > secs[i].cantMuelles) {
            REPORTAR_ERROR(info, 2, io);
        }
        printf("%c : %d\n", secs[i].code, tam);
    }


    io.tipo = 'S';
    rc = lista_buscar(&list, &io, cmp_salida);
    while(rc != NO_EXISTE) {
        lista_removerPosicion(&list, &io, sizeof(tEntradaSalida), rc);

        /*Buscamos su entrada*/
        io.tipo = 'E';
        rc = lista_buscar(&list, &io, cmp_duplicados);

        if(rc != NO_EXISTE) {
            lista_removerPosicion(&list, &io, sizeof(tEntradaSalida), rc);

            /*Revisamos que no hayan otras copias del mismo vehiculo en otro sector*/
            if(lista_contarDuplicados(&list, &io, sizeof(tEntradaSalida), cmp_vehiculo) != 0) {
                REPORTAR_ERROR(info, 3, io);
            }
        }
        else {
            REPORTAR_ERROR(info, 4, io);
        }

        io.tipo = 'S';
        rc = lista_buscar(&list, &io, cmp_salida);
    }

    while(!listaVacia(&list)) {
        lista_removerPrimero(&list, &io, sizeof(tEntradaSalida));
        REPORTAR_ERROR(info, 5, io);
    }

    fclose(lote);
    fclose(info);

    return 1;
}




/* Funciones privadas */
int cmp_duplicados(const void *vehi_1, const void *vehi_2)
{
    tEntradaSalida *_vehi_1 = (tEntradaSalida *)vehi_1,
                   *_vehi_2 = (tEntradaSalida *)vehi_2;

    return !(_vehi_1->sector == _vehi_2->sector && _vehi_1->tipo == _vehi_2->tipo
             && !strcmp(_vehi_1->dominio, _vehi_2->dominio));
}


int cmp_sectorEntrada(const void *vehi_1, const void *vehi_2)
{
    tEntradaSalida *_vehi_1 = (tEntradaSalida *)vehi_1,
                   *_vehi_2 = (tEntradaSalida *)vehi_2;

    return !(_vehi_1->sector == _vehi_2->sector && _vehi_1->tipo == 'E');
}


int cmp_salida(const void *vehi_1, const void *vehi_2)
{
    tEntradaSalida *_vehi_1 = (tEntradaSalida *)vehi_1,
                   *_vehi_2 = (tEntradaSalida *)vehi_2;

    return !(_vehi_1->tipo == _vehi_2->tipo);
}


int cmp_vehiculo(const void *vehi_1, const void *vehi_2)
{
    tEntradaSalida *_vehi_1 = (tEntradaSalida *)vehi_1,
                   *_vehi_2 = (tEntradaSalida *)vehi_2;

    return strcmp(_vehi_1->dominio, _vehi_2->dominio);
}


void parsearLote(tEntradaSalida *io, char *str)
{
    char *aux = str + TAM_STRING;
    *aux = '\0';

    /*Sector*/
    aux -= 1;
    sscanf(aux, "%c", &io->sector);
    *aux = '\0';

    /*Sentido*/
    aux -= 1;
    sscanf(aux, "%c", &io->tipo);
    *aux = '\0';

    /*Dominio*/
    aux -= 10;
    strcpy(io->dominio, aux);
    *aux = '\0';

    /*Fecha/Hora*/
    aux -= 12;
    sscanf(aux, "%ld", &io->timestamp);
    *aux = '\0';
}
