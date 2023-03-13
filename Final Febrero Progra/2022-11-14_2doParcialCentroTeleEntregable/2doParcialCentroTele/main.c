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
	#define SOLUCION_DOC
//	#define SOLUCION_ALU
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

void procesarPagos_ALU(const char* pathCli, const char* pathPagos, const char* pathListado);
void impCli_alu(void* elem, void* datosAccion);
int cmpIndice_alu(const void* e1, const void* e2);
int cmpFactura_alu(const void* e1, const void* e2);
int cmpImpagas_alu(const void* e1, const void* e2);
void actImpagas_alu(void* actualizado, const void* actualizador);
void crearLista_alu(Lista* pl);
int insertarEnlistaOrd_alu(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
void ordenarLista_alu(Lista* pl, Cmp cmp);
int sacarDeListaComienzo_alu(Lista* pl, void* elem, size_t tamElem);
void crearArbol_alu(Arbol* pa);
int buscarEnArbol_alu(Arbol* pa, void* elem, size_t tamElem, Cmp cmp);
void cargarArbolEnOrden_alu(Arbol* pa, size_t tamElem, Cmp cmp, char* nombreArch);


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
    ///////////////////////////////////////////////////////////////////////////////
    Arbol arbolIndices;
    crearArbol_alu(&arbolIndices);
    //cargarArbolDeArchivoOrdenado(&arbolIndices, sizeof(IndCli), "Clientes.idx");
	cargarArbolEnOrden_alu(&arbolIndices, sizeof(IndCli), cmpIndice_alu, "Clientes.idx");
	///////////////////////////////////////////////////////////////////////////////
	FILE* archPagos = fopen(pathPagos, "rb");
	if(!archPagos)
    {
        fclose(archPagos);
        return;
    }

	Lista listaPagos;
	crearLista_alu(&listaPagos);

	Pago pagoAct;
	FacturasImpagasFueraTerm impagasAct;

	fread(&pagoAct, sizeof(Pago), 1, archPagos);
	while(!feof(archPagos))
    {
        impagasAct.nroCliente = pagoAct.nroCliente;

        if(pagoAct.fechaPago.anio == 1900 && pagoAct.fechaPago.mes == 1 && pagoAct.fechaPago.dia == 1)
            impagasAct.cantFactImpagasFueraTerm = 1;
        else if(cmpFechas(&pagoAct.fechaPago, &pagoAct.fechaVencimiento) > 0)
            impagasAct.cantFactImpagasFueraTerm = 1;
        else
            impagasAct.cantFactImpagasFueraTerm = 0;

        insertarEnlistaOrd_alu(&listaPagos, &impagasAct, sizeof(FacturasImpagasFueraTerm), cmpFactura_alu, actImpagas_alu);

        fread(&pagoAct, sizeof(Pago), 1, archPagos);
    }
    fclose(archPagos);
    ordenarLista_alu(&listaPagos, cmpImpagas_alu);

    IndCli indAct;
    Cliente cliAct;
    FILE* archListado = fopen(pathListado, "wt");
    FILE* archCli = fopen(pathCli, "rb");
    if(!archListado || !archCli)
    {
        fclose(archListado);
        fclose(archCli);
        return;
    }

    while(sacarDeListaComienzo_alu(&listaPagos, &impagasAct, sizeof(FacturasImpagasFueraTerm)))
    {
        indAct.nroCliente = impagasAct.nroCliente;
        buscarEnArbol_alu(&arbolIndices, &indAct, sizeof(IndCli), cmpIndice_alu);
        fseek(archCli, (long int)indAct.nroReg*sizeof(Cliente), SEEK_SET);
        fread(&cliAct, sizeof(Cliente), 1, archCli);

        fprintf(archListado, "%d|%s|%d\n", impagasAct.nroCliente, cliAct.nombre, impagasAct.cantFactImpagasFueraTerm);
        printf("%d|%s|%d\n", impagasAct.nroCliente, cliAct.nombre, impagasAct.cantFactImpagasFueraTerm);
    }
}

/////Funciones//////////////////////////////////////////////////////////////
int cmpIndice_alu(const void* e1, const void* e2)
{
    IndCli* c1 = (IndCli*)e1;
    IndCli* c2 = (IndCli*)e2;

    return c1->nroCliente - c2->nroCliente;
}
int cmpFactura_alu(const void* e1, const void* e2)
{
    FacturasImpagasFueraTerm* c1 = (FacturasImpagasFueraTerm*)e1;
    FacturasImpagasFueraTerm* c2 = (FacturasImpagasFueraTerm*)e2;

    return c1->nroCliente - c2->nroCliente;
}

int cmpImpagas_alu(const void* e1, const void* e2)
{
    FacturasImpagasFueraTerm* i1 = (FacturasImpagasFueraTerm*)e1;
    FacturasImpagasFueraTerm* i2 = (FacturasImpagasFueraTerm*)e2;

    return i2->cantFactImpagasFueraTerm - i1->cantFactImpagasFueraTerm;
}

void actImpagas_alu(void* actualizado, const void* actualizador)
{
    FacturasImpagasFueraTerm* f1 = (FacturasImpagasFueraTerm*)actualizado;
    FacturasImpagasFueraTerm* f2 = (FacturasImpagasFueraTerm*)actualizador;

    f1->cantFactImpagasFueraTerm += f2->cantFactImpagasFueraTerm;
}

/////Arbol//////////////////////////////////////////////////////////
NodoA* crearNodoA_alu(const void* elem, size_t tamElem)
{
    NodoA* nue = (NodoA*)malloc(sizeof(NodoA));
    void* elemNodoA = malloc(tamElem);

    if(!nue || !elemNodoA)
    {
        free(nue);
        free(elemNodoA);
        return NULL;
    }

    memcpy(elemNodoA,elem,tamElem);
    nue->elem = elemNodoA;
    nue->tamElem = tamElem;
    nue->hDer = NULL;
    nue->hIzq = NULL;

    return nue;
}


void crearArbol_alu(Arbol* pa)
{
    *pa = NULL;
}

int insertarEnArbol_alu(Arbol* pa, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    if(!*pa)
    {
        *pa = crearNodoA_alu(elem, tamElem);

        return !*pa ? -1 : 0;
    }

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
    {
        if(actualizar)
            actualizar((*pa)->elem, elem);

        return -2;
    }

    return insertarEnArbol_alu(((comp < 0) ? &(*pa)->hIzq : &(*pa)->hDer), elem, tamElem, cmp, actualizar);
}

void cargarArbolRec_alu(FILE* pf, Arbol* pa, size_t tamElem, int inicio, int fin, Cmp cmp);

void cargarArbolEnOrden_alu(Arbol* pa, size_t tamElem, Cmp cmp, char* nombreArch)
{
    FILE* pt = fopen(nombreArch, "rb");
    if(!pt)
    {
        fclose(pt);
        return;
    }

    int inicio = 0;
    int fin;

    fseek(pt, 0l, SEEK_END);

    fin = (ftell(pt) / tamElem) - 1;

    cargarArbolRec_alu(pt, pa, tamElem, inicio, fin, cmp);

    fclose(pt);
}
void cargarArbolRec_alu(FILE* pf, Arbol* pa, size_t tamElem, int inicio, int fin, Cmp cmp)
{
    if(inicio > fin)
        return;

    int medio = (inicio + fin)/2;

    char vec[tamElem];

    fseek(pf, medio*tamElem, SEEK_SET);
    fread(vec, tamElem, 1, pf);

    insertarEnArbol_alu(pa, vec, tamElem, cmp, NULL);

    cargarArbolRec_alu(pf, pa, tamElem, inicio, medio-1, cmp);
    cargarArbolRec_alu(pf, pa, tamElem, medio+1, fin, cmp);
}

int buscarEnArbol_alu(Arbol* pa, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pa)
    {
        return 0;
    }

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
    {
        memcpy(elem, (*pa)->elem, MIN(tamElem, (*pa)->tamElem));
        return 1;
    }

    return buscarEnArbol_alu((comp < 0 ? &(*pa)->hIzq : &(*pa)->hDer), elem, tamElem, cmp);
}
/////NodoD///////////////////////////////////////////////////////////////////
NodoD* crearNodoD_alu(const void* elem, size_t tamElem)
{
    NodoD* nue = (NodoD*)malloc(sizeof(NodoD));
    void* elemNodo = malloc(tamElem);

    if(!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return NULL;
    }

    memcpy(elemNodo, elem, tamElem);

    nue->elem = elemNodo;
    nue->tamElem = tamElem;
    nue->sig = NULL;
    nue->ant = NULL;

    return nue;
}


void destruirNodoD_alu(NodoD* nae, void* elem, size_t tamElem)
{
    memcpy(elem, nae->elem, MIN(tamElem, nae->tamElem));
    free(nae->elem);
    free(nae);
}
/////Lista///////////////////////////////////////////////////////////////////////////////////////////////
void crearLista_alu(Lista* pl)
{
    *pl = NULL;
}

int insertarEnlistaOrd_alu(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    NodoD* act = *pl;
    NodoD* ant = NULL, * sig = NULL;

    if(act)
    {
        while(act->ant && cmp(elem, act->elem) < 0)
        {
            act = act->ant;
        }

        while(act->sig && cmp(elem, act->elem) > 0)
        {
            act = act->sig;
        }

        int comp = cmp(elem, act->elem);

        if(comp == 0)
        {
            if(actualizar)
                actualizar(act->elem, elem);
            return -1;
        }

        if(comp < 0)
        {
            sig = act;
            ant = act->ant;
        }
        else
        {
            ant = act;
            sig = act->sig;
        }
    }

    NodoD* nue = crearNodoD_alu(elem, tamElem);

    if(!nue)
    {
        return -2;
    }
    nue->ant = ant;
    nue->sig = sig;

    if(ant)
    {
        ant->sig = nue;
    }

    if(sig)
    {
        sig->ant = nue;
    }

    *pl = nue;

    return 0;
}

NodoD* buscarMenorEnlista_alu(Lista* pl,Cmp cmp)
{
    NodoD* der;
    NodoD* izq;
    NodoD* menor = *pl;

    if(!*pl)
    {
        return NULL;
    }

    der = (*pl)->sig;
    izq = (*pl)->ant;

    while(der)
    {
        if(cmp(der->elem, menor->elem) < 0)
        {
            menor = der;
        }
        der = der->sig;
    }

    while(izq)
    {
        if(cmp(izq->elem, menor->elem) < 0)
        {
            menor = izq;
        }
        izq = izq->ant;
    }

    return menor;
}

void ordenarLista_alu(Lista* pl, Cmp cmp)
{
    Lista Lord;
    Lista* plo = &Lord;
    *plo = NULL;

    NodoD* menor;

    while(*pl)
    {
        menor = buscarMenorEnlista_alu(pl, cmp);

        if(menor->ant)
        {
            menor->ant->sig = menor->sig;
        }

        if(menor->sig)
        {
            menor->sig->ant = menor->ant;
        }

        if(*pl == menor)
        {
            if((*pl)->sig)
            {
                *pl = (*pl)->sig;
            }
            else
            {
                *pl = (*pl)->ant;
            }
        }

        menor->ant = *plo;
        menor->sig = NULL;

        if(menor->ant)
            menor->ant->sig = menor;

        *plo = menor;
    }

    *pl = Lord;
}

int sacarDeListaComienzo_alu(Lista* pl, void* elem, size_t tamElem)
{
    NodoD* act = *pl;

    if(!*pl)
    {
        return 0;
    }

    while(act->ant)
    {
        act = act->ant;
    }

    NodoD* nae = act;

    if(nae == *pl)
    {
        *pl = nae->sig;
    }

    if(act->sig)
    {
        act->sig->ant = NULL;
    }

    destruirNodoD_alu(nae, elem, tamElem);

    return 1;
}
