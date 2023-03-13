#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define FILA 4
#define COLUMNA 4

typedef struct sNodoLista
{
    void *info;
    unsigned taminfo;
    struct sNodoLista *sig;
}tNodoLista;
typedef tNodoLista *tLista;

typedef struct
{
    int fila;
    int columna;
    int valor;
}tMatriz;
int InsertarEnLista(tLista *p,const void *d,unsigned cantbytes);
void CrearLista(tLista *p);
int PasarMatrizALista(tLista *p,int Mat[][COLUMNA],int fila,int columna);
void VerNodoLista(const void *a);
void MostrarLista(tLista *p,void (*mostrar)(const void *));
tMatriz BuscarNodoMayor(tLista *p);
void Diagonal(const void *a);
void PasarValores(const void *a,const void *b);


#endif // FUNCIONES_H_INCLUDED
