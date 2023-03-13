#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define ERR_MEM -1
#define ERR_NODO -2
#define ERR_ARCHIVO -3
#define ERR -4
#define TODO_OK 0

typedef struct sNodo
{
    void *dato;
    unsigned tamDato;
    struct sNodo * sig;

} Nodo;
typedef Nodo *Lista;

typedef int (*Cmp)(const void * d1, const void * d2);
typedef int (*Condicion) (const void* d);
typedef void (*Mostrar) (const void * dato, FILE * stream);

Nodo * crearNodo(const void * dato,unsigned tamDato);
void vaciarNodo(Nodo * nae, void * dato,unsigned tamDato);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

int insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato);
int mostrarEnOrdenInversoConCondRec(Lista *l, Mostrar mostrar, Condicion condicion, FILE * stream);

int compararEnteros(const void * d1,const void * d2);
int condicionEnteros(const void * dato);
void mostrarEnteros(const  void * dato, FILE * stream);


int main()
{
    int num []= {0,1,2,3,4,5,6,7,8,9,10};
    int i=0;
    Lista l;

    crearLista(&l);
    for (; i<sizeof(num)/sizeof(num[0]) ; i++ )
    {
        insertarEnListaAlFinal(&l,&num[i],sizeof(int));

    }
    mostrarEnOrdenInversoConCondRec(&l,mostrarEnteros,condicionEnteros,stdout);

    vaciarLista(&l);

    return 0;
}


Nodo * crearNodo(const void * dato,unsigned tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;
    return nue;
}
void vaciarNodo(Nodo * nae, void * dato,unsigned tamDato)
{
    if(!nae)
        return;

    if(dato)
        memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));

    free(nae->dato);
    free(nae);
}

void crearLista(Lista *l)
{
    *l = NULL;
}
void vaciarLista(Lista *l)
{
    Nodo * nae;
    if(!*l)
        return;

    while(*l)
    {
        nae = *l;
        *l = nae->sig;

        free(nae->dato);
        free(nae);
    }

    *l = NULL;

}

int insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return ERR_NODO;

    while(*l)
        l = &(*l)->sig;

    *l = nue;

    return TODO_OK;

}
int mostrarEnOrdenInversoConCondRec(Lista *l, Mostrar mostrar, Condicion condicion, FILE*stream)
{
    if(!*l)
        return 0;

    mostrarEnOrdenInversoConCondRec(&(*l)->sig,mostrar,condicion,stream);
    if(condicion((*l)->dato)==0)
    {
        if(mostrar)
            mostrar((*l)->dato,stream);
    }

    return TODO_OK;
}


int compararEnteros(const void * d1,const void * d2)
{
    int * num1 = (int *)d1;
    int * num2 = (int * )d2;

    return *num1 - *num2;

}
int condicionEnteros(const void * dato)
{
    int * num = (int *)dato;

    return !(*num%2 == 0);
}
void mostrarEnteros(const  void * dato, FILE * stream)
{
    int * num = (int *)dato;

    fprintf(stream,"num %d \n",*num );
}
