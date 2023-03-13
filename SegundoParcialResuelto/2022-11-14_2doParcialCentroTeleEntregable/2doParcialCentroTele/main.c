/*****************************************************************************************************************
** Apellido/s, Nombre/s:                                      													**
**
** DNI:                                                       													**
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
	//#define SOLUCION_DOC
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

#define min(x,y) (x<y)?x:y

void procesarPagos_ALU(const char* pathCli, const char* pathPagos, const char* pathListado);

void cargarArbolDeArchivo_ALU(Arbol* pa,size_t tamElem,const char* pathCliIDX,Cmp cmp);
void cargarRegistroMedio_ALU(Arbol* pa,FILE* pfCliIdx,size_t tamElem,int li,int ls,Cmp cmp);

int compIndices_ALU(const void* e1, const void* e2);

void crearArbol_ALU(Arbol* pa);
int insertarEnArbol_ALU(Arbol* pa,const void* elem,size_t tamElem,Cmp cmp);
NodoA* crearNodoA_ALU(const void* elem,size_t tamElem);
booleano buscarEnArbol_ALU(const Arbol* pa,void* elem,size_t tamElem,Cmp cmp);

void crearLista_ALU(Lista* pl);
NodoD* crearNodoD_ALU(const void* elem,size_t tamElem);
int insertarEnListaOrd_ALU(Lista* pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar actualizar);
booleano eliminarDeListaPrimero_ALU(Lista* pl, void* elem, size_t tamElem);
void destruirNodoD_ALU(NodoD* nae,void* elem,size_t tamElem);
booleano listaVacia_ALU(const Lista*pl);

void vaciarArbol_ALU(Arbol* pa);
void vaciarLista_ALU(Lista* pl);

void destruirNodoA_ALU(NodoA* nae,void* elem,size_t tamElem);


booleano estaImpago_ALU(Fecha fecha);
booleano esPagoDentroDeFechaDeVencimiento_ALU(Fecha fechaPago, Fecha fechaVencimiento);

int compNroCliente_ALU(const void* e1,const void* e2);
int compCantFactImpagas_ALU(const void* e1,const void* e2);

void actualizarCantPago_ALU(void* actualizado, const void* actualizador);



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

	return 0;
}


void procesarPagos_ALU(const char* pathCli, const char* pathPagos, const char* pathListado)
{
    FILE* pfCli=fopen(pathCli,"r+b");
    FILE* pfPagos=fopen(pathPagos,"rb");
    FILE* pfListado=fopen(pathListado,"wt");
    char pathCliIDX[strlen(pathCli)];
    strcpy(pathCliIDX,pathCli);
    char* punto = strchr(pathCliIDX,'.');
    *punto = '\0';
    strcat(pathCliIDX,".idx");

    Arbol arbolIndice;
    crearArbol_ALU(&arbolIndice);
    cargarArbolDeArchivo_ALU(&arbolIndice,sizeof(IndCli),pathCliIDX,compIndices_ALU);

    Lista listado;
    crearLista_ALU(&listado);

    //IndCli indAux;
    Pago pagoAux;
    //Cliente cliente;
    FacturasImpagasFueraTerm factura;
    factura.cantFactImpagasFueraTerm=0;
    booleano elemEncontrado;

    fread(&pagoAux,sizeof(Pago),1,pfPagos); //obtengo el pago
    factura.nroCliente=pagoAux.nroCliente;
    while(!feof(pfPagos))
    {
        elemEncontrado=buscarEnListaOrd(&listado,&factura,sizeof(FacturasImpagasFueraTerm),compNroCliente_ALU);
            if(elemEncontrado)
            {
                if(estaImpago_ALU(pagoAux.fechaVencimiento)) //obtengo cantMalPago
                    factura.cantFactImpagasFueraTerm++;
                if( !esPagoDentroDeFechaDeVencimiento_ALU( (pagoAux.fechaPago),(pagoAux.fechaVencimiento)  )  )
                    factura.cantFactImpagasFueraTerm++;

            }
            fread(&pagoAux,sizeof(Pago),1,pfPagos);
        insertarEnListaOrd_ALU(&listado,&factura,sizeof(FacturasImpagasFueraTerm),compNroCliente_ALU,actualizarCantPago_ALU);
        fread(&pagoAux,sizeof(Pago),1,pfPagos); //obtengo el pago
        factura.nroCliente=pagoAux.nroCliente;
    }


    factura.nroCliente=pagoAux.nroCliente;


    /*while(!feof(pfPagos))
    {
        indAux.nroCliente=pagoAux.nroCliente; //Le doy nrocliente a indAux
        booleano elemEncontrado = buscarEnArbol_ALU(&arbolIndice,&indAux,sizeof(IndCli),compNroCliente_ALU); //obtengo registro del cliente
        printf("test: %d\t\t%d\n",indAux.nroCliente,indAux.nroReg);
        if(elemEncontrado)
        {
            fseek(pfCli,(indAux.nroReg)*sizeof(IndCli),SEEK_SET);
            fread(&cliente,sizeof(Cliente),1,pfCli); //obtengo el nombre cliente
            if(estaImpago_ALU(pagoAux.fechaVencimiento)) //obtengo cantMalPago
                factura.cantFactImpagasFueraTerm++;
            if( !esPagoDentroDeFechaDeVencimiento_ALU( (pagoAux.fechaPago),(pagoAux.fechaVencimiento)  )  )
                factura.cantFactImpagasFueraTerm++;
            insertarEnListaOrd_ALU(&listado,&factura,sizeof(FacturasImpagasFueraTerm),compNroCliente_ALU,actualizarCantPago_ALU);
        }
        //fprintf(pfListado,"%d\t%s\t%d\n",factura.nroCliente,cliente.nombre,factura.cantFactImpagasFueraTerm);
        fread(&pagoAux,sizeof(Pago),1,pfPagos); //obtengo el pago
        factura.nroCliente=pagoAux.nroCliente;
        factura.cantFactImpagasFueraTerm=0;
    }*/

    do{
        eliminarDeListaPrimero_ALU(&listado,&factura,sizeof(FacturasImpagasFueraTerm));
        printf("%d   %d\n",factura.nroCliente,factura.cantFactImpagasFueraTerm);
    }while(!listaVacia_ALU(&listado));

    fclose(pfCli);
    fclose(pfPagos);
    fclose(pfListado);
}

void crearArbol_ALU(Arbol* pa)
{
    *pa=NULL;
}

void cargarArbolDeArchivo_ALU(Arbol* pa,size_t tamElem,const char* pathCliIDX,Cmp cmp)
{
    FILE* pfCliIdx = fopen(pathCliIDX,"rb");
    fseek(pfCliIdx,0L,SEEK_END);
    int li=0,ls;
    ls= (ftell(pfCliIdx)/tamElem)-1;
    cargarRegistroMedio_ALU(pa,pfCliIdx,tamElem,li,ls,cmp);
    fclose(pfCliIdx);
}




void cargarRegistroMedio_ALU(Arbol* pa,FILE* pfCliIdx,size_t tamElem,int li,int ls,Cmp cmp)
{
    if(li>ls)
        return;
    int medio=(li+ls)/2;
    fseek(pfCliIdx,medio*tamElem,SEEK_SET);
    void* elem=malloc(tamElem);
    fread(elem,tamElem,1,pfCliIdx);
    insertarEnArbol(pa,elem,tamElem,cmp);
    cargarRegistroMedio_ALU(pa,pfCliIdx,tamElem,li,medio-1,cmp);
    cargarRegistroMedio_ALU(pa,pfCliIdx,tamElem,medio+1,ls,cmp);
}

int insertarEnArbol_ALU(Arbol* pa,const void* elem,size_t tamElem,Cmp cmp)
{
    if(!*pa)
    {
        NodoA* nue = crearNodoA_ALU(elem,tamElem);
        if(!nue)
            return SIN_MEM;
        *pa=nue;
        return TODO_OK;
    }
    int comp = cmp(elem,(*pa)->elem);
    if(comp<0)
        return insertarEnArbol_ALU(&(*pa)->hIzq,elem,tamElem,cmp);
    else
        return insertarEnArbol_ALU(&(*pa)->hDer,elem,tamElem,cmp);
}

NodoA* crearNodoA_ALU(const void* elem,size_t tamElem)
{
    NodoA* nodo = (NodoA*)malloc(sizeof(NodoA));
    void* elemNodo = malloc(tamElem);
    if(!nodo || !elemNodo)
    {
        free(nodo);
        free(elemNodo);
        return NULL;
    }
    memcpy(elemNodo,elem,tamElem);
    nodo->elem=elemNodo;
    nodo->tamElem=tamElem;
    nodo->hIzq = NULL;
    nodo->hDer = NULL;
    return nodo;
}

int compIndices_ALU(const void* e1, const void* e2)
{
    IndCli* n1 = (IndCli*)e1;
    IndCli* n2 = (IndCli*)e2;
    return (n1->nroReg - n2->nroReg);
}

booleano buscarEnArbol_ALU(const Arbol* pa,void* elem,size_t tamElem,Cmp cmp)
{
    if(!*pa)
        return falso;
    int comp = cmp(elem,(*pa)->elem);


    if(comp==0)
    {
        memcpy(elem,(*pa)->elem,min(tamElem,(*pa)->tamElem));
        return verdadero;
    }

    if(comp<0)
        return buscarEnArbol_ALU(&(*pa)->hIzq,elem,tamElem,cmp);
    else
        return buscarEnArbol_ALU(&(*pa)->hDer,elem,tamElem,cmp);
}

void crearLista_ALU(Lista* pl)
{
    *pl=NULL;
}

NodoD* crearNodoD_ALU(const void* elem,size_t tamElem)
{
    NodoD* nodoD = (NodoD*)malloc(sizeof(NodoD));
    void* elemNodo = malloc(tamElem);
    if(!nodoD || !elemNodo)
    {
        free(nodoD);
        free(elemNodo);
        return NULL;
    }
    memcpy(elemNodo,elem,tamElem);
    nodoD->elem=elemNodo;
    nodoD->tamElem=tamElem;
    nodoD->ant = NULL;
    nodoD->sig = NULL;
    return nodoD;
}

int insertarEnListaOrd_ALU(Lista* pl,const void* elem,size_t tamElem,Cmp cmp,Actualizar actualizar)
{
    NodoD* nue = crearNodoD_ALU(elem,tamElem);
    if(!*pl)
    {
        *pl = nue;
        return TODO_OK;
    }

    NodoD* act = *pl;

    int comp;
    while(act->sig && (comp=cmp(elem,act->elem) < 0)  )
        act = act->sig;

    if(comp==0)
    {
        actualizar(act->elem,elem);
        return DUPLICADO;
    }

    act->sig = nue;
    nue->ant = act;
    return TODO_OK;
}


booleano estaImpago_ALU(Fecha fecha)
{
    if(fecha.anio==1900)
    {
        if(fecha.mes==1)
        {
            if(fecha.dia==1)
                return verdadero;
            else
                return falso;
        }
        else
            return falso;
    }
    else
        return falso;
}

booleano esPagoDentroDeFechaDeVencimiento_ALU(Fecha fechaPago, Fecha fechaVencimiento)
{
    if(fechaPago.anio<=fechaVencimiento.anio)
    {
        if(fechaPago.mes<=fechaVencimiento.mes)
        {
            if(fechaPago.dia<=fechaVencimiento.dia)
                return verdadero;
            else
                return falso;
        }
        return falso;
    }
    return falso;
}

int compNroCliente_ALU(const void* e1,const void* e2)
{
    FacturasImpagasFueraTerm* n1 = (FacturasImpagasFueraTerm*)e1;
    FacturasImpagasFueraTerm* n2 = (FacturasImpagasFueraTerm*)e2;
    return n1->nroCliente - n2->nroCliente;
}

void actualizarCantPago_ALU(void* actualizado, const void* actualizador)
{
    FacturasImpagasFueraTerm* n1 = (FacturasImpagasFueraTerm*)actualizado;
    FacturasImpagasFueraTerm* n2 = (FacturasImpagasFueraTerm*)actualizador;
    n1->cantFactImpagasFueraTerm += n2->cantFactImpagasFueraTerm;
}

booleano eliminarDeListaPrimero_ALU(Lista* pl, void* elem, size_t tamElem)
{
    if(!*pl)
        return falso;

    NodoD* nae = *pl;
    *pl = nae->sig;
    destruirNodoD_ALU(nae,elem,tamElem);
    return verdadero;
}

void destruirNodoD_ALU(NodoD* nae,void* elem,size_t tamElem)
{
    memcpy(elem,nae->elem,min(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);
}

booleano listaVacia_ALU(const Lista*pl)
{
    if(*pl)
        return falso;
    else
        return verdadero;
}

void vaciarArbol_ALU(Arbol* pa)
{
    vaciarArbol(&(*pa)->hIzq);
    vaciarArbol(&(*pa)->hDer);
    destruirNodoA_ALU(*pa,NULL,0);
}



void vaciarLista_ALU(Lista* pl)
{
    if(!*pl)
        return;

    NodoD* nae = *pl;
    while(nae->sig)
    {
        *pl = nae->sig;
        destruirNodoD_ALU(nae,NULL,0);
        nae = *pl;
    }
}

void destruirNodoA_ALU(NodoA* nae,void* elem,size_t tamElem)
{
    memcpy(elem,nae->elem,min(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);
}

booleano buscarEnListaOrd_ALU(const Lista* pl,void* elem,size_t tamElem,Cmp cmp)
{
    if(!*pl)
        return falso;
    NodoD* act = *pl;

    int comp;
    while(act->sig && (comp=cmp(act->elem,act->sig->elem) < 0 ))
        act=act->sig;

    if(comp==0)
    {
        memcpy(elem,act->elem,min(tamElem,act->tamElem));
        return verdadero;
    }
    return falso;
}
