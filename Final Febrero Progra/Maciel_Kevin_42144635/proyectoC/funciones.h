#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
///Maciel_Kevin_42144635
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    char dominio[7];
    int antiguedad;
    int kilometros;
} tVehiculo;

typedef struct
{
    char dominio[7];
    int antiguedad;
    int kilometros;
    int cantVehiculos;
} tVehiculoProm;

typedef struct
{
    int antiguedad;
    float promedio;
} tPromXAntig;

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

void crearLista(tLista *p);
int insertarAcumulandoEnLista( tLista *p, void *d, unsigned cantBytes, int (*cmp)(const void*, const void*),
                               void (*acum)(void**,unsigned tam, const void*, unsigned cantBytes));

int insertarArchivoEnLista(tLista *p, unsigned cantBytes, const char *path,
                           int (*cmp)(const void*, const void*),
                           void (*acum)(void**,unsigned tam, const void*, unsigned cantBytes)
                          );
int grabarListaEnArchivo(tLista *p,const char *path);
int sacarPrimeroDeLista(tLista *p,void *d,unsigned cantBytes);



#endif // FUNCIONES_H_INCLUDED
