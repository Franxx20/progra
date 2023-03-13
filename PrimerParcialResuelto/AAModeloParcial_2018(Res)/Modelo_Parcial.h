#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef MODELO_PARCIAL_H_INCLUDED
#define MODELO_PARCIAL_H_INCLUDED
#define FMOVIMIENTOS "movimientos.txt"
#define FCUENTAS "cuentas.bin"
#define LISTA_LLENA 0
#define LISTA_VACIA 0
#define TODO_BIEN 1
#define DUPLICADO 0

typedef int (*t_cmp)(const void*,const void*);
typedef void(*t_act)(void*,const void*);

/// Para CUENTA
typedef struct
{
    char nrocuenta[9];
    char nombre[10];
    float saldo;
} t_cuenta;

///HORA

typedef struct
{
    int h;
    int m;
} t_hora;

/// FECHA
typedef struct
{
    int di;
    int me;
    int an;
} t_fecha;

/// Para MOVIMIENTOS
typedef struct
{
    t_fecha fecha;
    t_hora hora;
    char nrocuenta[9];
    char movimiento[2];
    float importe;
}t_movimiento;

typedef struct s_nodo
{
    struct s_nodo *sig;
    t_movimiento info;
} t_nodo;

typedef t_nodo*t_lista;



/// FUNCIONES
FILE *abrirArch (char *nombre, char* modo);
void crearLista(t_lista *l);
int comparar(const void *dato1,const void *dato2);
int ponerListaOrdenada(t_lista *l,const t_movimiento *info,t_cmp comparar,t_act actualizar);
void copiarListaEnArchivo(FILE* pm,t_lista* l);
void actualizaCuentas(FILE*pc,t_lista *l);
int sacarPrimeroLista(t_lista *l,t_movimiento *info);
void mostrar_archivo(FILE* pc);
void actualizar(void*datoact, const void*datonue);

#endif // MODELO_PARCIAL_H_INCLUDED
