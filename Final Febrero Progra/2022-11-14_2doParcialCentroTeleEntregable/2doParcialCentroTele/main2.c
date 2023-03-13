/*****************************************************************************************************************
** Apellido/s, Nombre/s:  My Tomás                                    											**
*
** DNI:  43.669.624                                           													**
**
******************************************************************************************************************
** Corrección																								   	**
** **********																								   	**
**
******************************************************************************************************************
** Nota:
*****************************************************************************************************************/

/*****************************************************************************************************************
** Descomente SOLUCION_ALU y comente SOLUCION_DOC, para probar su código: 										**
**																												*/
//define SOLUCION_DOC
#define SOLUCION_ALU
/*
*****************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Cadena/Cadena.h"
#include "../Fecha/Fecha.h"
#include "../Solucion2doParcialCentroTele/Solucion2doParcialCentroTele.h"

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

#define PATH_CLI 1
#define PATH_PAGOS 2
#define PATH_LISTADO 3

#define MIN(X,Y) X<Y? X:Y

typedef struct
{
    int nroCliente;
    char nombre[201];
    int nroDeudas;
} MorasXCliente;

// FUNCIONES GENERALES
void procesarPagos_ALU(const char* pathCli, const char* pathPagos, const char* pathListado);
int cargarListaDePagos_ALU(const char * pathPagos, Lista *l);
int determinarMorosos_ALU(const Pago * pago);
// FUNCIONES PUNTERO
int cmpPagos_ALU(const void * d1, const void * d2);
int cmpIndices_ALU(const void * d1, const void * d2);
int cmpMorosos_ALU(const void *d1,const void *d2);

// FUNCIONES LISTA
NodoD* crearNodoD(const void *dato, size_t tamDato);
void crearLista_ALU(Lista *l);
int vaciarLista_ALU(Lista *l);

booleano listaLlena_ALU(const Lista *l, size_t tamDato);
booleano listaVacia_ALU(const Lista *l);

int insertarEnListaOrdCDup_ALU(Lista *l, const void * dato,size_t tamDato, Cmp cmp);
booleano eliminarDeListaPrimero_ALU(Lista *l, void * dato, size_t tamDato);

// FUNCIONES ARBOL
NodoA* crearNodoA(const void *dato, size_t tamDato);
void crearArbol_ALU(Arbol *t);
int vaciarArbol_ALU(Arbol*t);

int insertarEnArbol_ALU(Arbol *t, const void * dato, size_t tamDato, Cmp cmp);
int cargarArbolDeArchivoPreorden_ALU(Arbol*t, size_t tamDato,const char * nombreArchivo,Cmp cmp);
int cargarArbolDeArchivoPreordenREC_ALU(Arbol*t, int li,int ls, size_t TamDato,FILE *fp,Cmp cmp);

int buscarEnArbol_ALU(const Arbol *t, void * dato, size_t tamDato, Cmp cmp);


int main(int argc, char* argv[])
{
    generarArchivoClientes(argv[PATH_CLI]);
    generarArchivoPagos(argv[PATH_PAGOS]);

    mostrarArchivoClientes(argv[PATH_CLI]);

    char nombreIdx[201];
    reemplazarSubcad(argv[PATH_CLI], ".dat", ".idx", nombreIdx, 201);
    mostrarArchivoClientesIdx(nombreIdx);

    mostrarArchivoPagos(argv[PATH_PAGOS]);

#ifdef SOLUCION_DOC
    procesarPagos(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);
#else
    procesarPagos_ALU(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);
#endif

    getchar();

    return 0;
}


void procesarPagos_ALU(const char* pathCli, const char* pathPagos, const char* pathListado)
{
    FILE *fpListado = fopen(pathListado,"wt");
    FILE * fpClientes = fopen(pathCli,"rb");


    Lista listaPagos;
    Lista listaMorosos;
    Arbol arbolIndices;

    Pago pago;
    IndCli indice;
    Cliente cliente;
    MorasXCliente mxc;

    int impagos;


    if(!fpListado || !fpClientes)
    {
        fclose(fpListado);
        fclose(fpClientes);
        return;
    }
    crearArbol_ALU(&arbolIndices);
    crearLista_ALU(&listaMorosos);
    crearLista_ALU(&listaPagos);




    cargarArbolDeArchivoPreorden_ALU(&arbolIndices,sizeof(indice),"clientes.idx",cmpIndices_ALU);
    cargarListaDePagos_ALU(pathPagos,&listaPagos);

    eliminarDeListaPrimero_ALU(&listaPagos,&pago,sizeof(Pago));
    while(!listaVacia(&listaPagos))
    {

        indice.nroCliente = pago.nroCliente;

        impagos = 0;
        while(indice.nroCliente == pago.nroCliente && !listaVacia(&listaPagos))
        {
            if(determinarMorosos_ALU(&pago) == 1)
            {
                impagos++;
            }
            eliminarDeListaPrimero_ALU(&listaPagos,&pago,sizeof(Pago));
        }

        if(listaVacia_ALU(&listaPagos))
        {
            if(determinarMorosos_ALU(&pago) == 1)
            {
                impagos++;
            }
        }


        buscarEnArbol_ALU(&arbolIndices,&indice,sizeof(IndCli),cmpIndices_ALU);
        fseek(fpClientes,(long)indice.nroReg * sizeof(Cliente),SEEK_SET);
        fread(&cliente,sizeof(Cliente),1,fpClientes);

        strcpy(mxc.nombre,cliente.nombre);
        mxc.nroDeudas = impagos;
        mxc.nroCliente = indice.nroCliente;

        insertarEnListaOrdCDup_ALU(&listaMorosos,&mxc,sizeof(MorasXCliente),cmpMorosos_ALU);


    }
    fputs("Listado de Deudores\n",stdout);
    fputs("===============================\n",stdout);
    fputs("Nro Cliente       Nombre            Facturas en mora\n",stdout);
      fputs("",stdout);

    fputs("Listado de Deudores\n",fpListado);
    fputs("===============================\n",fpListado);
    fputs("Nro Cliente       Nombre            Facturas en mora\n",fpListado);
    fputs("",fpListado);
    while(!listaVacia(&listaMorosos))
    {
        eliminarDeListaPrimero_ALU(&listaMorosos,&mxc,sizeof(MorasXCliente));
        fprintf(stdout,"%d\t%-20s\t%d\n",mxc.nroCliente,mxc.nombre,mxc.nroDeudas);
        fprintf(fpListado,"%d\t%-20s\t%d\n",mxc.nroCliente,mxc.nombre,mxc.nroDeudas);
    }


    vaciarArbol(&arbolIndices);
    vaciarLista_ALU(&listaPagos);
    vaciarLista_ALU(&listaMorosos);
    fclose(fpListado);
    fclose(fpClientes);
}

int cargarListaDePagos_ALU(const char * pathPagos, Lista *l)
{
    FILE * fp = fopen(pathPagos,"rb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    Pago pago;
    fread(&pago,sizeof(Pago),1,fp);
    while(!feof(fp))
    {
        insertarEnListaOrdCDup_ALU(l,&pago,sizeof(Pago),cmpPagos_ALU);
        fread(&pago,sizeof(Pago),1,fp);
    }
    fclose(fp);
    return TODO_OK;
}

int determinarMorosos_ALU(const Pago * pago)
{
    const Fecha fechaImpaga = {1,1,1900};
    if(cmpFechas(&pago->fechaPago,&fechaImpaga) == 0)
        return 1;
    else if(cmpFechas(&pago->fechaPago,&pago->fechaVencimiento)>0)
        return 1;


    return  0;
}

// FUNCIONES PUNTERO
int cmpPagos_ALU(const void * d1, const void * d2)
{
    Pago * p1 = (Pago* )d1;
    Pago * p2 = (Pago *)d2;

    return p1->nroCliente - p2->nroCliente;
}
int cmpIndices_ALU(const void * d1, const void * d2)
{
    IndCli * i1 =(IndCli *)d1;
    IndCli * i2 =(IndCli *)d2;


    return i1->nroCliente - i2->nroCliente;
}


int cmpMorosos_ALU(const void *d1,const void *d2)
{
    MorasXCliente * m1 = (MorasXCliente *)d1;
    MorasXCliente * m2 = (MorasXCliente *)d2;

    return m2->nroDeudas - m1->nroDeudas;
}


// FUNCIONES LISTA
NodoD* crearNodoD(const void *dato, size_t tamDato)
{
    NodoD * nue = (NodoD*)calloc(1,sizeof(NodoD));
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
    *l= NULL;
}
int vaciarLista_ALU(Lista *l)
{
    int cne =0;
    NodoD * act=*l;
    NodoD * nae;
    if(act)
    {

        while(act->ant)
            act = act->ant;

        nae =act;
        act =nae->sig;
        cne++;
        free(nae->elem);
        free(nae);
    }
    *l = NULL;
    return cne;

}

booleano listaLlena_ALU(const Lista *l, size_t tamDato)
{
    NodoD * nodo = (NodoD *)calloc(1,sizeof(NodoD));
    void * dato = calloc(1,tamDato);
    free(nodo);
    free(dato);

    return !dato || !nodo;
}
booleano listaVacia_ALU(const Lista *l)
{
    return *l ==NULL;
}

int insertarEnListaOrdCDup_ALU(Lista *l, const void * dato,size_t tamDato, Cmp cmp)
{
    NodoD * nue =crearNodoD(dato,tamDato);
    NodoD * act= *l;
    NodoD *sig =NULL;
    NodoD * ant =NULL;
    int resultado;

    if(act)
    {
        while(act->ant && cmp(dato,act->elem)<0)
            act =act->ant;
        while(act->sig && cmp(dato,act->elem)>0)
            act =act->sig;

        resultado = cmp(dato,act->elem);
        // el dato a ingresar es menor al dato actual
        if(resultado<0)
        {
            sig =act;
            ant= act->ant;
        }
        else
        {
            sig = act->sig;
            ant =act;
        }


    }
    nue->sig = sig;
    nue->ant = ant;

    if(sig)
        sig->ant = nue;
    if(ant)
        ant->sig = nue;
    *l = nue;
    return TODO_OK;

}



booleano eliminarDeListaPrimero_ALU(Lista *l, void * dato, size_t tamDato)
{
    NodoD *act = *l;
    NodoD * nae;
    if(!act)
        return falso;

    while(act->ant)
        act = act->ant;

    nae =act;
    act =nae->sig;

    if(act)
        act->ant = NULL;
    if(nae == *l)
        *l = nae->sig;

    memcpy(dato,nae->elem,MIN(nae->tamElem,tamDato));
    free(nae->elem);
    free(nae);


    return verdadero;
}

// FUNCIONES ARBOL
NodoA* crearNodoA(const void *dato, size_t tamDato)
{

    NodoA * nue = (NodoA*)calloc(1,sizeof(NodoA));
    if(!nue || !(nue->elem = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->elem,dato,tamDato);
    nue->tamElem = tamDato;
    nue->hIzq = NULL;
    nue->hDer = NULL;

    return nue;
}
void crearArbol_ALU(Arbol *t)
{
    *t =NULL;
}
int vaciarArbol_ALU(Arbol*t)
{
    int cne =0;
    if(!*t)
        return cne;

    cne+= vaciarArbol_ALU(&(*t)->hIzq);
    cne+= vaciarArbol_ALU(&(*t)->hDer);
    free((*t)->elem);
    free(*t);

    return cne+1;
}


int insertarEnArbol_ALU(Arbol *t, const void * dato, size_t tamDato, Cmp cmp)
{
    int resultado ;
    if(!*t)
    {
        *t = crearNodoA(dato,tamDato);
        if(!*t)
            return -1;
        return TODO_OK;
    }
    resultado = cmp(dato,(*t)->elem);
    if(resultado ==0)
    {

        return -2;

    }
    return insertarEnArbol_ALU(resultado<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);

}

int buscarEnArbol_ALU(const Arbol *t, void * dato, size_t tamDato, Cmp cmp)
{
    int resultado;
    if(!*t)
        return -4;

    resultado = cmp(dato,(*t)->elem);
    if(resultado ==0)
    {
        memcpy(dato,(*t)->elem,MIN(tamDato,(*t)->tamElem));
        return TODO_OK;
    }

    return buscarEnArbol_ALU(resultado<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);

}

int cargarArbolDeArchivoPreorden_ALU(Arbol*t, size_t tamDato,const char * nombreArchivo,Cmp cmp)
{
    int cantBytes;
    int cantReg;
    FILE *  fp = fopen(nombreArchivo,"rb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    fseek(fp,0L,SEEK_END);
    cantBytes = ftell(fp);
    cantReg= cantBytes/tamDato;

    cargarArbolDeArchivoPreordenREC_ALU(t,0,cantReg-1,tamDato,fp,cmp);

    fclose(fp);

    return TODO_OK;
}
int cargarArbolDeArchivoPreordenREC_ALU(Arbol*t, int li,int ls, size_t TamDato,FILE *fp,Cmp cmp)
{
    int mitad;
    void * dato = calloc(1,TamDato);
    if(!dato)
    {
        free(dato);
        return -3;
    }
    if(li > ls)
        return -4;

    mitad =(li+ls)/2;

    fseek(fp,(long)mitad*TamDato,SEEK_SET);
    fread(dato,TamDato,1,fp);
    insertarEnArbol_ALU(t,dato,TamDato,cmp);

    cargarArbolDeArchivoPreordenREC_ALU(t,li,mitad-1,TamDato,fp,cmp);
    cargarArbolDeArchivoPreordenREC_ALU(t,mitad+1,ls,TamDato,fp,cmp);

    return TODO_OK;
}
