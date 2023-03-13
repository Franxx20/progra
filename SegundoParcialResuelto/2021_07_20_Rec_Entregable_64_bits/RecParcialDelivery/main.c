

//#define P1
#define P2

//#define SOLUCION_DOC
#define SOLUCION_ALU

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <string.h>
#include <memory.h>
#define ERR_REPETIDO 5
#ifdef P1
#define TDA_COLA_IMPL_DINAMICA
#define TDA_LISTA_IMPL_DINAMICA
#endif

#ifdef P2
#define TDA_COLA_IMPL_DINAMICA_CIRCULAR
#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#endif

#include "../TDAColaImplDinamicaCircular/TDAColaImplDinamicaCircular.h"
#include "../TDACola/TDACola.h"

#include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#include "../TDALista/TDALista.h"

#include "../SolucionParcialDelivery/TiposDelivery.h"
#include "../SolucionParcialDelivery/SolucionParcialDelivery.h"
#include "../Utilitarias/Utilitarias.h"

#define MIN(x,y) ((x) <= (y)? (x) : (y))
#define ERR_MEM -6


// FUNCIONES LISTA
NodoD * crearNodoD_ALU(void *dato, size_t tamDato);
void vaciarNodoD_ALU(Nodo *nae, void * dato, size_t tamDato);

void crearLista_ALU(Lista *l);
void vaciaLista_ALU(Lista *l);

bool insertarEnListaAlFinal_ALU(Lista *l, const void * dato, size_t tamDato);
int insertarEnListaOrd_ALU(Lista *l, const void * dato, unsigned tamDato,Cmp cmp);
int buscarEnListaOrd_ALU(const  Lista *l,void *dato,size_t tamDato, Cmp cmp);


// FUNCIONES COLA
Nodo * crearNodo_ALU(void *dato, size_t tamDato);
void vaciarNodo_ALU(Nodo *nae, void *dato, size_t tamDato);

void crearCola_ALU(Cola *c);

int colaVacia_ALU(const Cola *c);

int desencolar_ALU(Cola *c, void * dato, size_t tamDato);

// FUNCIONES GENERALES
bool pasarTxtABinario_ALU( char * filename, Pedido *p);
bool cargarPedidos_ALU(Cola *c, const char * nombreArchivoPedidos);


// FUNCIONES PUNTERO
void copiarIndiceRecetas(void *pvIdx, const void * pvReg, int nroReg);
void copiarIndiceIngredientes(void * pvIdx,const void * pvReg, int nroReg);

int compararIndIngredientes(const void * d1, const void * d2);
int compararIndRecetas(const void * d1, const void * d2);

// FUNCIONES STRING
void memcpy_ALU(void * destino,void *origen,size_t tam);
int strcmp_ALU(const char * s1, const char *s2);
char* strncpy_ALU(char * destino,const char * origen,size_t tam);

char *strcpy_ALU(char * destino,const char * origen);

int main()
{
    generarArchivoPedidos();
    generarArchivoRecetas();
    generarArchivoIngredientes();

    mostrarArchivoPedidos("Pedidos.txt");
    mostrarArchivoRecetas("Recetas.dat");

    puts("Ingredientes antes de la actualizacion");
    mostrarArchivoIngredientes("Ingredientes.dat");

    int resp;

#ifdef SOLUCION_DOC
    resp = satisfacerPedidos("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
#else
    resp = satisfacerPedidos_alu("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
#endif

    if(resp != TODO_OK)
    {
        puts("Error actualizando los pedidos.");
        return resp;
    }

    puts("Ingredientes despues de la actualizacion");
    mostrarArchivoIngredientes("Ingredientes.dat");

    return 0;
}



int satisfacerPedidos_alu(const char *  nombreArchPedidos, const char * nombreArchRecetas, const char * nombreArchIngredientes)
{
    FILE * fpIng = fopen(nombreArchIngredientes,"r+b");
    FILE * fpPedidos = fopen(nombreArchPedidos,"rt");
    FILE * fpRecetas =fopen(nombreArchRecetas,"rb");
    FILE *fpIngIdx = fopen("Ingredientes.idx","rb");
    FILE *fpRecIdx = fopen("Recetas.idx","rb");


    if(!fpIng || !fpPedidos || !fpRecetas || !fpIngIdx || !fpRecIdx)
    {
        fprintf(stderr,"ERROR EN LA APERTURA DE ARCHIVOS");
        return ERR_ARCHIVO;
    }

    Lista listaIndiceIngredientes;
    Lista listaIndiceRecetas;

    crearLista(&listaIndiceIngredientes);
    crearLista(&listaIndiceRecetas);

    IndReceta indiceRecetas;
    IndIngrediente indiceIngredientes;

//
//    fread(&indiceRecetas,sizeof(IndReceta),1,fpRecIdx);
//    while(!feof(fpRecIdx))
//    {
//        insertarEnListaOrd(&listaIndiceRecetas,&indiceRecetas,sizeof(IndReceta),compararIndRecetas);
//        fread(&indiceRecetas,sizeof(IndReceta),1,fpRecIdx);
//    }

    cargarIndiceEnLista("Recetas.idx",sizeof(IndReceta),&listaIndiceRecetas,compararIndRecetas);
    cargarIndiceEnLista("Ingredientes.idx",sizeof(indiceIngredientes),&listaIndiceIngredientes,compararIndIngredientes);

    //generarIndice(nombreArchRecetas,sizeof(Receta),sizeof(IndReceta),copiarIndiceRecetas,compararIndRecetas);
//
//    fread(&indiceIngredientes,sizeof(IndIngrediente),1,fpIngIdx);
//    while(!feof(fpIngIdx))
//    {
//        //insertarEnListaOrd(&listaIndiceRecetas,&indiceIngredientes,sizeof(IndIngrediente),compararIndIngredientes);
//        insertarEnListaAlFinal(&listaIndiceRecetas,&indiceIngredientes,sizeof(indiceIngredientes));
//
//        fread(&indiceIngredientes,sizeof(IndIngrediente),1,fpIngIdx);
//    }





    Ingrediente i;

    char linea[256];
    while(fgets(linea,256,fpPedidos))
    {
        Pedido p;
        pasarTxtABinario_ALU(linea,&p);

        Receta r;

        Cola colaIngredientes;
        crearCola(&colaIngredientes);

        strcpy(indiceRecetas.codReceta,p.codReceta);

        buscarEnListaOrd(&listaIndiceRecetas,&indiceRecetas,sizeof(IndReceta),compararIndRecetas);

        fseek(fpRecetas,indiceRecetas.nroReg*sizeof(Receta),SEEK_SET);
        fread(&r,sizeof(Receta),1,fpRecetas);

        while(!feof(fpRecetas) && strcmp(r.codReceta,p.codReceta)==0)
        {
            encolar(&colaIngredientes,&r,sizeof(Receta));
            fread(&r,sizeof(Receta),1,fpRecetas);
        }

        while(!colaVacia(&colaIngredientes))
        {
            desencolar(&colaIngredientes,&r,sizeof(Receta));
            strcpy(indiceIngredientes.codIngr,r.codIngr);
            buscarEnListaOrd(&listaIndiceIngredientes,&indiceIngredientes,sizeof(IndIngrediente),compararIndIngredientes);
            fseek(fpIng,indiceIngredientes.nroReg*sizeof(IndIngrediente),SEEK_SET);
            fread(&i,sizeof(Ingrediente),1,fpIng);
            i.stock -=p.cantidad * r.cantidad;
            fseek(fpIng,-(long)sizeof(Ingrediente),SEEK_CUR);
            fwrite(&i,sizeof(Ingrediente),1,fpIng);

        }



    }



    fclose(fpIng);
    fclose(fpPedidos);
    fclose(fpRecetas);
    fclose(fpIngIdx);
    fclose(fpRecIdx);

    vaciarLista(&listaIndiceIngredientes);
    vaciarLista(&listaIndiceRecetas);
    return TODO_OK;
}
bool pasarTxtABinario_ALU(char * linea, Pedido *p)
{
    char * aux = strrchr(linea,'\n');
    if(*aux != '\n')
    {
        fprintf(stderr, "ERROR LINEA LARGA");
        return false;
    }
    *aux = '\0';

    aux = strrchr(linea,'\t');
    sscanf(aux+1,"%d",&p->cantidad);

    *aux ='\0';
    aux = strrchr(linea,'\t');
    strncpy(p->codReceta,aux+1,sizeof(p->codReceta));

    *aux = '\0';
    sscanf(linea,"%d",&p->nroPedido);



    return true;

}

bool cargarPedidos_ALU(Cola *c, const char * nombreArchivoPedidos)
{
    FILE * fpt =fopen(nombreArchivoPedidos,"rt");

    if(!fpt)
        return ERR_ARCHIVO;

    Pedido p;

    char linea[256];
    while (fgets(linea,256,fpt))
    {
        pasarTxtABinario_ALU(linea,&p);
        encolar(c,linea,256);
    }
    fclose(fpt);
    return true;
}


void copiarIndiceRecetas(void *pvIdx, const void * pvReg, int nroReg)
{

    IndReceta * i =(IndReceta * )pvIdx;
    Receta * r = (Receta *)pvReg;

    strncpy(i->codReceta,r->codReceta,sizeof(i->codReceta));
    i->nroReg = nroReg;


}
void copiarIndiceIngredientes(void * pvIdx,const void * pvReg, int nroReg)
{
    IndIngrediente *i = (IndIngrediente *)pvIdx;
    Ingrediente * ing = (Ingrediente *)pvReg;

    strncpy(i->codIngr,ing->codIngr,sizeof(i->codIngr));
    i->nroReg = nroReg;
}

int compararIndIngredientes(const void * d1, const void * d2)
{
    IndIngrediente * i1 = (IndIngrediente*)d1;
    IndIngrediente * i2 = (IndIngrediente*)d2;

    return strcmp(i1->codIngr,i2->codIngr);

}
int compararIndRecetas(const void * d1, const void * d2)
{
    IndReceta * r1 = (IndReceta*)d1;
    IndReceta * r2 = (IndReceta*)d2;

    return strcmp(r1->codReceta,r2->codReceta);

}



// FUNCIONES LISTA
NodoD * crearNodoD_ALU(void *dato, size_t tamDato)
{
    NodoD * nue = (NodoD*)malloc(sizeof(NodoD));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamElem = tamDato;
    nue->sig = NULL;
    nue->ant = NULL;

    return nue;
}
void vaciarNodoD_ALU(Nodo *nae, void * dato, size_t tamDato)
{
    if(!nae)
        return ;

    if(dato != NULL)
        memcpy(dato,nae->dato,MIN(tamDato,nae->tamElem));

    free(nae->dato);
    free(nae);
}

void crearLista_ALU(Lista *l)
{
    *l = NULL;
}
void vaciaLista_ALU(Lista *l)
{
    NodoD * act ;
    NodoD * nae;

    if(!*l)
        return;

    act =*l;

    while(act->ant)
        act  = act->ant;

    while(act)
    {
        nae =act;
        act = nae->sig;

        free(nae->dato);
        free(nae);
    }

    *l = NULL;


}

bool insertarEnListaAlFinal_ALU(Lista *l, const void * dato, size_t tamDato)
{
    NodoD * nue = crearNodoD_ALU((NodoD*)dato,tamDato);
    if(!nue)
        return false;

    NodoD * act= *l;

    if(act)
        while(act->sig)
            act =act->sig;

    nue->ant = act;

    if(act)
        act->sig = nue;

    *l = nue;
    return true;
}

int insertarEnListaOrd_ALU(Lista *l, const void * dato, unsigned tamDato,Cmp cmp)
{
    NodoD * nue = crearNodoD_ALU((NodoD*)dato,tamDato);
    if(!nue)
        return ERR_MEM;
    NodoD * act;
    NodoD * sig= NULL;
    NodoD * ant =NULL;

    act =*l;

    if(act)
    {
        while(act->ant && cmp(dato,act->dato)<0)
            act = act->ant;

        while(act->sig && cmp(dato,act->dato)>0)
            act = act->sig;

        int res = cmp(dato,act->dato);

        if (res==0)
            return ERR_REPETIDO;
        if(res<0)
        {
            sig =act;
            ant = act->ant;
        }
        else
        {
            sig = act->sig;
            ant = act;
        }

    }

    nue->sig = sig;
    nue->ant =ant;

    if(sig)
        sig->ant = nue;

    if(ant)
        act->sig =nue;

    * l = nue;


    return TODO_OK;
}


int buscarEnListaOrd_ALU(const  Lista *l,void *dato,size_t tamDato, Cmp cmp)
{
    if(!*l)
        return ERR_MEM;
    NodoD* act = *l;

    while(act->ant && cmp(dato,act->dato)<0)
        act = act->ant;

    while(act->sig && cmp(dato,act->dato)>0)
        act =act->sig;

    int res = cmp(dato,act->dato);

    if(res!=0)
        return ERR_MEM;

    memcpy(dato,act->dato,MIN(tamDato,act->tamElem));


    return TODO_OK;
}


// FUNCIONES COLA
Nodo * crearNodo_ALU(void *dato, size_t tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue || !(nue->dato  = malloc(tamDato)))
    {

        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->sig = NULL;

    return nue;
}
void vaciarNodo_ALU(Nodo *nae, void *dato, size_t tamDato)
{
    if(!nae)
        return;

    if(dato)
        memcpy(dato,nae->dato,MIN(tamDato,nae->tamElem));
    free(nae->dato);
    free(nae);



}

void crearCola_ALU(Cola *c)
{
    *c = NULL;
}

int colaVacia_ALU(const Cola *c)
{

    return *c == NULL;
}

int desencolar_ALU(Cola *c, void * dato, size_t tamDato)
{
    if(!*c)
        return false;

    Nodo * aux;

    aux = (*c)->sig;

    memcpy(dato,aux->dato,MIN(tamDato,aux->tamElem));

    if(aux == *c)
        *c = NULL;
    else
        (*c)->sig = aux->sig;

    free(aux->dato);
    free(aux);

    return TODO_OK;
}

// FUNCIONES STRING
void memcpy_ALU(void * destino,void *origen,size_t tam)
{
    char * d = (char *)destino;
    char * o = (char *)origen;
    for (int i= 0; i < tam ; i++)
    {
        d[i]  = o[i];
    }
}
int strcmp_ALU(const char * s1, const char *s2)
{

    for (; *s1 == *s2 ; s1++, s2++ )
    {

    }

    return *s1 - *s2;

}
char *  strncpy_ALU(char * destino,const char * origen,size_t tam)
{
    char * temp = destino;
    char * temp2 = (char * )origen;
    int i;
    for ( i =0; i<tam ; i++,temp++,temp2++ )
    {
        *temp = * temp2;
    }
    while(i<tam)
        temp[i] = '\0';
    return destino;
}
char * strcpy_ALU(char * destino,const char * origen)
{
    char * temp = destino;
    char * temp2 = (char * )origen;

    while(*temp != '\0')
    {
        *temp = *temp2;
        temp++;
        temp2++;

    }
    *temp = '\0';

    return destino;
}
