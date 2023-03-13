/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres: ANGEL, FACUNDO NICOLAS
*
* DNI: 40640923
*
****************************************************************************************
********** Descomente el parcial que debe rendir. Si es el integrador, es P2: **********
***************************************************************************************/
//#define P1
#define P2
/***************************************************************************************
********************* Descomente la solución que quiere probar: ************************
***************************************************************************************/
//#define SOLUCION_DOC
#define SOLUCION_ALU
/**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef P1
#define TDA_COLA_IMPL_DINAMICA
#define TDA_LISTA_IMPL_DINAMICA
#endif

#ifdef P2
#define TDA_COLA_IMPL_DINAMICA_CIRCULAR
#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#endif

#include "../TDACola/TDACola.h"
#include "../TDALista/TDALista.h"
#include "../SolucionDelivery/TiposDelivery.h"
#include "../SolucionDelivery/SolucionDelivery.h"
#include "../Utilitarias/Utilitarias.h"


#define TAM_LINEA 100
#define min(x,y) (x>y)?(y):(x)

// FUNCIONES GENERALES

int cargarListaPedidos_ALU(Lista *l, const char * nombreArchivoPedidos);
int parsearPedidos_ALU(char * linea, Pedido * pedido);
int cargarIndiceEnLista_ALU(const char * pathInd,size_t indice,Lista *l, Cmp cmp);

int cambiarExtension_ALU(char * nombreExtNueva,const char * nombreExtVieja);

// FUNCIONES PUNTERO
int cmpIndIngredientes_ALU(const void * d1, const void *d2);
int cmpIndRecetas_ALU(const void * d1,const void * d2);

// FUNCIONES COLA
void crearCola_ALU(Cola* pc);
bool encolar_ALU(Cola* pc, const void* elem, size_t tamElem);
bool desencolar_ALU(Cola* pc, void* elem, size_t tamElem);
void vaciarCola_ALU( Cola* pc);
bool colaVacia_ALU(const Cola *c);

// FUNCIONES LISTA
NodoD * crearNodoD_ALU(const void *dato, size_t tamDato);
void crearLista_ALU(Lista *l);
void vaciarLista_ALU(Lista *l);

int insertarEnListaAlFinal_ALU(Lista *l, const void * dato, size_t tamDato);
int insertarEnListaOrdCDup_ALU(Lista *l, const void * dato, size_t tamDato, Cmp cmp);

booleano eliminarDeListaPrimero_ALU(Lista *l, void * dato, size_t tamDato);

booleano listaLlena_ALU(const Lista *l, size_t tamDato);
booleano listaVacia_ALU(const Lista *l);

booleano buscarEnListaOrd_ALU(const Lista *l, void * dato, size_t tamDato, Cmp cmp);

void vaciarCola(Cola* pc);
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
    resp = satisfacerPedidos_ALU("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
#endif

    if(resp != TODO_OK)
    {
        puts("Error actualizando los pedidos.");
        return resp;
    }

    puts("Ingredientes despues de la actualizacion");
    mostrarArchivoIngredientes("Ingredientes.dat");

    getchar();

    return 0;
}



///Procesa los pedidos del archivo Pedidos.txt, actualizando el archivo Ingredientes.dat, para que �ste refleje la cantidad que queda en stock luego de despachar los pedidos.
int satisfacerPedidos_ALU(const char* nombreArchPedidos, const char* nombreArchRecetas, const char* nombreArchIngredientes)
{
    FILE * fpRecetas = fopen(nombreArchRecetas, "rb");
    FILE * fpIngredientes = fopen(nombreArchIngredientes,"r+b");
    if(!fpRecetas || !fpIngredientes)
    {
        fclose(fpIngredientes);
        fclose(fpRecetas);
    }

    char * nombreIndiceRecetas = calloc(256,sizeof(char));
    char * nombreIndiceIngredientes = calloc(256,sizeof(char));

    Lista listaPedidos;
    Lista listaIndiceIngredientes;
    Lista listaIndiceRecetas;

    Cola colaRecetas;


    Pedido pedido;

    Ingrediente ingrediente;
    IndIngrediente indiceIngrediente;


    char * codReceta = calloc(1,sizeof(ingrediente.codIngr));

    Receta receta;

    IndReceta indiceReceta;

    crearLista_ALU(&listaPedidos);
    crearLista_ALU(&listaIndiceIngredientes);
    crearLista_ALU(&listaIndiceRecetas);

    crearCola_ALU(&colaRecetas);



    cargarListaPedidos_ALU(&listaPedidos,nombreArchPedidos);

    cambiarExtension_ALU(nombreIndiceIngredientes,nombreArchIngredientes);
    cambiarExtension_ALU(nombreIndiceRecetas,nombreArchRecetas);

    cargarIndiceEnLista_ALU(nombreIndiceIngredientes,sizeof(IndIngrediente),&listaIndiceIngredientes,cmpIndIngredientes_ALU);
    cargarIndiceEnLista_ALU(nombreIndiceRecetas,sizeof(indiceReceta),&listaIndiceRecetas,cmpIndRecetas_ALU);


    while(!listaVacia(&listaPedidos))
    {
        eliminarDeListaPrimero_ALU(&listaPedidos,&pedido,sizeof(Pedido));
        strcpy(indiceReceta.codReceta,pedido.codReceta);
        buscarEnListaOrd_ALU(&listaIndiceRecetas,&indiceReceta,sizeof(indiceReceta),cmpIndRecetas_ALU);

        fseek(fpRecetas,indiceReceta.nroReg * sizeof(Receta),SEEK_SET);
        fread(&receta,sizeof(Receta),1,fpRecetas);

        while(!feof(fpRecetas) && strcmp(receta.codReceta,indiceReceta.codReceta) == 0)
        {
            encolar_ALU(&colaRecetas,&receta,sizeof(Receta));
            fread(&receta,sizeof(Receta),1,fpRecetas);
        }

        while(!colaVacia_ALU(&colaRecetas))
        {
            desencolar_ALU(&colaRecetas,&receta,sizeof(Receta));
            strcpy(indiceIngrediente.codIngr,receta.codIngr);

            buscarEnListaOrd_ALU(&listaIndiceIngredientes,&indiceIngrediente,sizeof(IndIngrediente),cmpIndIngredientes_ALU);
            fseek(fpIngredientes,indiceIngrediente.nroReg * sizeof(Ingrediente),SEEK_SET);
            fread(&ingrediente,sizeof(Ingrediente),1,fpIngredientes);

            ingrediente.stock-=receta.cantidad*pedido.cantidad;

            fseek(fpIngredientes,-(long)sizeof(Ingrediente),SEEK_CUR);
            fwrite(&ingrediente,sizeof(Ingrediente),1,fpIngredientes);
        }

    }



    vaciarLista_ALU(&listaPedidos);
    vaciarLista_ALU(&listaIndiceIngredientes);
    vaciarLista_ALU(&listaIndiceRecetas);
    vaciarCola_ALU(&colaRecetas);
    free(codReceta);
    free(nombreIndiceIngredientes);
    free(nombreIndiceRecetas);

    fclose(fpIngredientes);
    fclose(fpRecetas);
    return TODO_OK;
}

int cargarListaPedidos_ALU(Lista *l, const char * nombreArchivoPedidos)
{
    FILE * fp = fopen(nombreArchivoPedidos,"rt");
    char * linea = calloc(256,sizeof(char));
    Pedido pedido;
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    while(fgets(linea,256,fp))
    {
        parsearPedidos_ALU(linea,&pedido);
        insertarEnListaAlFinal_ALU(l,&pedido,sizeof(Pedido));
    }

    free(linea);
    return TODO_OK;
}

int parsearPedidos_ALU(char * linea, Pedido * pedido)
{
    char * aux = strchr(linea,'\n');
    if(!aux)
        return -2;

    *aux = '\0';
    aux = strrchr(linea,'\t');
    sscanf(aux+1,"%d",&pedido->cantidad);

    *aux = '\0';
    aux = strrchr(linea,'\t');
    strcpy(pedido->codReceta,aux+1);

    *aux = '\0';
    sscanf(linea,"%d",&pedido->nroPedido);


    return TODO_OK;
}
int cargarIndiceEnLista_ALU(const char * pathInd,size_t tamIndice,Lista *l, Cmp cmp)
{
    FILE *fp = fopen(pathInd,"rb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    void * indice = calloc(1,tamIndice);

    if(!indice)
    {
        free(indice);
        return -3;
    }

    fread(indice,tamIndice,1,fp);
    while(!feof(fp))
    {
        insertarEnListaOrdCDup_ALU(l,indice,tamIndice,cmp);
        fread(indice,tamIndice,1,fp);
    }

    return TODO_OK;
}
int cambiarExtension_ALU(char * nombreExtNueva,const char * nombreExtVieja)
{
    char * aux;
    strcpy(nombreExtNueva,nombreExtVieja);
    aux = strchr(nombreExtNueva,'.');
    strcpy(aux+1,"idx");
    return TODO_OK;
}


// FUNCIONES PUNTERO
int cmpIndIngredientes_ALU(const void * d1, const void *d2)
{
    IndIngrediente * i1 = (IndIngrediente * )d1;
    IndIngrediente * i2 = (IndIngrediente * )d2;
    return strcmp(i1->codIngr,i2->codIngr);
}
int cmpIndRecetas_ALU(const void * d1,const void * d2)
{
    IndReceta * r1 = (IndReceta *)d1;
    IndReceta * r2 = (IndReceta *)d2;

    return strcmp(r1->codReceta, r2->codReceta);
}

// FUNCIONES COLA
void crearCola_ALU(Cola* c)
{
    *c  = NULL;
}
bool encolar_ALU(Cola* c, const void* elem, size_t tamElem)
{
    Nodo * nue = (Nodo *)calloc(1,tamElem);
    if(!nue || !(nue->elem = calloc(1,tamElem)))
    {
        free(nue);
        return falso;
    }
    memcpy(nue->elem,elem,tamElem);
    nue->tamElem = tamElem;

    if(*c == NULL)
        nue->sig = nue;
    else
    {
        nue->sig = (*c)->sig;
        (*c)->sig = nue;
    }
    *c = nue;

    return verdadero;
}
bool desencolar_ALU(Cola* c, void* elem, size_t tamElem)
{
    if((*c)== NULL)
        return falso;

    Nodo * nae;
    nae = (*c)->sig;
    memcpy(elem,nae->elem,min(nae->tamElem,tamElem));

    if(nae == *c)
        *c = NULL;
    else
        (*c)->sig = nae->sig;

    free(nae->elem);
    free(nae);

    return verdadero;
}
void vaciarCola_ALU(  Cola* c)
{
    Nodo * nae;


    while(*c)
    {
        nae = (*c)->sig;
        if(*c == nae)
            *c = NULL;
        else(*c)->sig = nae->sig;
        free(nae->elem);
        free(nae);
    }


}
bool colaVacia_ALU(const Cola *c)
{
    return *c == NULL;
}

// FUNCIONES LISTA
NodoD * crearNodoD_ALU(const void *dato, size_t tamDato)
{
    NodoD * nue= (NodoD * )calloc(1,sizeof(NodoD));
    if(!nue || !(nue->elem = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->elem,dato,tamDato);
    nue->tamElem = tamDato;
    nue->sig = NULL;
    nue->ant = NULL;

    return nue;
}
void crearLista_ALU(Lista *l)
{
    *l = NULL;
}
void vaciarLista_ALU(Lista *l)
{
    NodoD * nae;
    NodoD *act = *l;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        while(act)
        {
            nae =act;
            act = nae->sig;

            free(nae->elem);
            free(nae);
        }
        *l = NULL;
    }
}


int insertarEnListaAlFinal_ALU(Lista *l, const void * dato, size_t tamDato)
{
    NodoD * nue = crearNodoD_ALU(dato,tamDato);
    NodoD * act;
    if(!nue)
    {
        return -3;
    }
    act =*l;
    if(act)
    {
        while(act->sig)
            act = act->sig;
    }
    nue->ant = act;
    if(act)
        act->sig = nue;

    *l = nue;
    return TODO_OK;
}

int insertarEnListaOrdCDup_ALU(Lista *l, const void * dato, size_t tamDato, Cmp cmp)
{
    NodoD * nue = crearNodoD_ALU(dato,tamDato);
    int resultado;
    if(!nue)
        return -4;
    NodoD * act = *l;
    NodoD * sig= NULL;
    NodoD * ant= NULL;

    if(act)
    {
        while(act->ant && cmp(dato,act->elem) < 0)
            act =act->ant;

        while(act->sig && cmp(dato,act->elem)>0)
            act =act->sig;

        resultado = cmp(dato,act->elem);

        // el dato a insertar es menor al dato actual
        if(resultado< 0)
        {
            sig = act;
            ant = act->ant;

        }
        else // el dato a insertar es mayor al dato actual
        {
            sig = act->sig;
            ant = act;
        }
    }

    nue->sig = sig;
    nue->ant = ant;

    if(ant)
        ant->sig = nue;

    if(sig)
        sig->ant = nue;

    *l = nue;

    return TODO_OK;
}


booleano buscarEnListaOrd_ALU(const Lista *l, void * dato, size_t tamDato, Cmp cmp)
{
    NodoD * act;
    int resultado;
    if(!*l)
        return falso;

    act =*l;

    while(act->ant && cmp(dato,act->elem)<0)
        act = act->ant;
    while(act->sig && cmp(dato,act->elem)>0)
        act =act->sig;

    resultado = cmp(dato,act->elem);
    if(resultado ==0 && act)
    {
        memcpy(dato,act->elem,min(act->tamElem,tamDato));
        return verdadero;
    }

    return falso;

}

booleano eliminarDeListaPrimero_ALU(Lista *l, void * dato, size_t tamDato)
{
    NodoD * nae;
    NodoD *act;

    if(!*l)
        return falso;
    act =*l;

    while(act->ant)
        act = act->ant;

    nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;

    if(*l == nae)
        *l = nae->sig;
    memcpy(dato,nae->elem,min(tamDato,nae->tamElem));
    free(nae->elem);
    free(nae);

    return verdadero;
}

booleano listaLlena_ALU(const Lista *l, size_t tamDato)
{
    NodoD * nodo = (NodoD *)calloc(1,sizeof(NodoD));
    void * dato = calloc(1,tamDato);
    free(nodo);
    free(dato);
    return !nodo || !dato;
}
booleano listaVacia_ALU(const Lista *l)
{

    return *l == NULL;
}
