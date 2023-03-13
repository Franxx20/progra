#include <stdio.h>
#include <stdlib.h>

/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
* DNI:
****************************************************************************************
************* Descomente el parcial que debe rendir. Si son los 2, es PI: **************
***************************************************************************************/
///#define P1
#define P2
///#define PI
/**************************************************************************************/

#ifdef P1
	#define TDA_LISTA_IMPL_DINAMICA
#endif

#if defined(P2) || defined(PI)
	#define TDA_LISTA_IMPL_DINAMICA_DOBLE
	#define TDA_ARBOL_IMPL_DINAMICA
	#include "../TDAArbol/TDAArbol.h"
#endif

#include "../TDALista/TDALista.h"

#include "../SolucionMuebles/MueblesComun.h"
#include "../SolucionMuebles/SolucionMuebles.h"

// AGREGADO POR POMI

#define NOMBRE_DEP_IND "Depositos.idx"
#define TAM_LINEA 256
#define min(a,b) ((a) < (b) ? (a) : (b))

#include <string.h>

void crearLista_ALU(Lista* pl);

void crearArbol_ALU(Arbol* pa);
void cargarArchivoEnArbol_ALU(Arbol* pa, size_t tamElem, const char* nombreArch);
void cargarArchivoEnArbolConLim_ALU(Arbol* pa, FILE* arch, int limInf, int limSup, Cmp cmp, Actualizar actualizar);
void actNull_ALU(void* actualizado, const void* actualizador);
booleano buscarEnArbol_ALU(const Arbol* pa, void* elem, size_t tamElem, Cmp cmp);
int insertarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
NodoA* crearNodoA_ALU(const void* elem, size_t tamElem);
int actualizarDepositos_ALU(const char* archTransferencias, const char* archDepositos);
int cmpInd_ALU(const void* e1, const void* e2);
int insertarOActualizarEnListaOrd_ALU(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
NodoD* crearNodoD_ALU(const void* elem, size_t tamElem);
booleano eliminarDeListaPrimero_ALU(Lista* pl, void* elem, size_t tamElem);
int cmpTransfLista_ALU(const void* e1, const void* e2);
void actualizarTransf_ALU(void* actualizado, const void* actualizador);

////////////////////


int main()
{
	#if defined(P1) || defined(PI)
		generarArchivos(verdadero, verdadero);
	#else
		generarArchivos(falso, verdadero);
	#endif

	mostrarArchivoTransferencias("Transferencias.txt");

	puts("");
	puts("Depositos antes de actualizar:");
	mostrarArchivoDepositos("Depositos.dat");

	///actualizarDepositos("Transferencias.txt", "Depositos.dat");
	actualizarDepositos_ALU("Transferencias.txt", "Depositos.dat");

	puts("");
	puts("Depositos despues de actualizar:");
	mostrarArchivoDepositos("Depositos.dat");

	return 0;
}


int actualizarDepositos_ALU(const char* archTransferencias, const char* archDepositos)
{
	Arbol aIndice;
	crearArbol_ALU(&aIndice);

	cargarArchivoEnArbol_ALU(&aIndice, sizeof(Indice), NOMBRE_DEP_IND);

	FILE* archTransfer = fopen(archTransferencias, "rt");

	if(!archTransfer)
		return ERR_ARCHIVO;

	Lista listaTransferencias;
	crearLista_ALU(&listaTransferencias);
	Transferencia transfer;
	char linea[TAM_LINEA];
	char* act;

	while(fgets(linea, TAM_LINEA, archTransfer))
	{
		//me posiciono al final de la linea leida
		act = strchr(linea, '\n');

		act = strrchr(linea, '|');
		sscanf(act + 1, "%d", &transfer.cantidad);
		*act = '\0';

		act = strrchr(linea, '|');
		strcpy(transfer.codProd, act + 1);
		*act = '\0';

		act = strrchr(linea, '|');
		sscanf(act + 1, "%d", &transfer.depDestino);
		*act = '\0';

		sscanf(linea, "%d", &transfer.depOrigen);

		insertarOActualizarEnListaOrd_ALU(&listaTransferencias, &transfer, sizeof(Transferencia), cmpTransfLista_ALU, actualizarTransf_ALU);
	}

	fclose(archTransfer);

	// tengo : 		INDICE 		-> aIndice
	//		    TRANSFERENCIAS 	-> listaTransferencias

	FILE* archDep = fopen(archDepositos, "r+b");

	if(!archDep)
		return ERR_ARCHIVO;

	Indice ind;
	Deposito dep;

	while(eliminarDeListaPrimero_ALU(&listaTransferencias, &transfer, sizeof(Transferencia)))
	{
		strcpy(ind.codProd, transfer.codProd);

		// deposito de origen -> se resta stock
		ind.nroDep = transfer.depOrigen;
		buscarEnArbol_ALU(&aIndice, &ind, sizeof(Indice), cmpInd_ALU);

		fseek(archDep, ind.nroReg * sizeof(Deposito), SEEK_SET);
		fread(&dep, sizeof(Deposito), 1, archDep);

		dep.stock -= transfer.cantidad;

		fseek(archDep, ind.nroReg * sizeof(Deposito), SEEK_SET);
		fwrite(&dep, sizeof(Deposito), 1, archDep);

		// deposito de destino -> se aumenta stock
		ind.nroDep = transfer.depDestino;
		buscarEnArbol_ALU(&aIndice, &ind, sizeof(Indice), cmpInd_ALU);

		fseek(archDep, ind.nroReg * sizeof(Indice), SEEK_SET);
		fread(&dep, sizeof(Deposito), 1, archDep);

		dep.stock += transfer.cantidad;

		fseek(archDep, ind.nroReg * sizeof(Deposito), SEEK_SET);
		fwrite(&dep, sizeof(Deposito), 1, archDep);
	}

	fclose(archDep);

	return TODO_OK;
}


void crearArbol_ALU(Arbol* pa)
{
    *pa = NULL;
}

void cargarArchivoEnArbol_ALU(Arbol* pa, size_t tamElem, const char* nombreArch)
{
	FILE* arch = fopen(NOMBRE_DEP_IND, "rb");

	if(!arch)
		return;

	fseek(arch, 0l, SEEK_END);
	int cantBytes = ftell(arch);
	int cantRegistros = cantBytes / tamElem;

	cargarArchivoEnArbolConLim_ALU(pa, arch, 0, cantRegistros - 1, cmpInd_ALU, actNull_ALU);

	fclose(arch);
}

void cargarArchivoEnArbolConLim_ALU(Arbol* pa, FILE* arch, int limInf, int limSup, Cmp cmp, Actualizar actualizar)
{
    //CASO BASE -> LIM INF > LIM SUP
    if(limInf > limSup)
        return;

    int medio = (limInf + limSup) / 2;
    Indice ind;

    fseek(arch, medio * sizeof(Indice), SEEK_SET);
    fread(&ind, sizeof(Indice), 1, arch);

    insertarEnArbol_ALU(pa, &ind, sizeof(Indice), cmp, actualizar);

    cargarArchivoEnArbolConLim_ALU(pa, arch, limInf, medio - 1, cmp, actualizar);
    cargarArchivoEnArbolConLim_ALU(pa, arch, medio + 1, limSup, cmp, actualizar);
}

void actNull_ALU(void* actualizado, const void* actualizador)
{
	return;
}

booleano buscarEnArbol_ALU(const Arbol* pa, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pa)
        return falso;

    int comp = cmp(elem, (*pa)->elem);;

    if(comp == 0)
    {
        memcpy(elem, (*pa)->elem, min(tamElem, (*pa)->tamElem));
        return verdadero;
    }

    if(comp < 0)
        return buscarEnArbol_ALU(&(*pa)->hIzq, elem, tamElem, cmp);
    else
        return buscarEnArbol_ALU(&(*pa)->hDer, elem, tamElem, cmp);
}

int insertarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    if(!*pa)
    {
        *pa = crearNodoA_ALU(elem, tamElem);
        if(!*pa)
            return SIN_MEM;

        return TODO_OK;
    }

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
    {
        actualizar((*pa)->elem, elem);
        return DUPLICADO;
    }

    return insertarEnArbol_ALU(comp < 0 ?
                            &(*pa)->hIzq :
                            &(*pa)->hDer,
                            elem, tamElem, cmp, actualizar);

}

NodoA* crearNodoA_ALU(const void* elem, size_t tamElem)
{
	NodoA* nuevo = malloc(sizeof(NodoA));
	void* elemNodo = malloc(tamElem);

	if(!nuevo || !elemNodo)
	{
		free(nuevo);
		free(elemNodo);
		return NULL;
	}

	memcpy(elemNodo, elem, tamElem);

	nuevo->elem = elemNodo;
	nuevo->tamElem = tamElem;
	nuevo->hIzq = NULL;
	nuevo->hDer = NULL;

	return nuevo;
}

void crearLista_ALU(Lista* pl)
{
	*pl = NULL;
}

int cmpInd_ALU(const void* e1, const void* e2)
{
	Indice* i1 = (Indice*)e1;
	Indice* i2 = (Indice*)e2;

	if(i1->nroDep != i2->nroDep)
		return i1->nroDep - i2->nroDep;

	return strcmp(i1->codProd, i2->codProd);
}

int insertarOActualizarEnListaOrd_ALU(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
	NodoD	*act = *pl,
			*ant,
			*sig,
			*nuevo;

	if(!act)
	{
		ant = NULL;
		sig = NULL;
	}
	else
	{
		while(act->sig && cmp(elem, act->elem) > 0)
			act = act->sig;

		while(act->ant && cmp(elem, act->elem) < 0)
			act = act->ant;

		int comp = cmp(elem, act->elem);
		if(comp == 0)
		{
			*pl = act;
			actualizar(act->elem, elem);
			return DUPLICADO;
		}

		if(comp < 0)
		{
			ant = act->ant;
			sig = act;
		}
		else
		{
			ant = act;
			sig = act->sig;
		}
	}

    nuevo = crearNodoD_ALU(elem, tamElem);
    if(!nuevo)
    {
        return SIN_MEM;
    }

	memcpy(nuevo->elem, elem, tamElem);
	nuevo->tamElem = tamElem;
	nuevo->sig = sig;
	nuevo->ant = ant;
	if(ant)
		ant->sig = nuevo;
	if(sig)
		sig->ant = nuevo;

	*pl = nuevo;
	return TODO_OK;
}

NodoD* crearNodoD_ALU(const void* elem, size_t tamElem)
{
	NodoD* nuevo = malloc(sizeof(NodoD));
	void* elemNodo = malloc(tamElem);

	if(!nuevo || !elemNodo)
	{
		free(nuevo);
		free(elemNodo);
		return NULL;
	}

	memcpy(elemNodo, elem, tamElem);
	nuevo->elem = elemNodo;
	nuevo->tamElem = tamElem;
	nuevo->ant = NULL;
	nuevo->sig = NULL;

	return nuevo;
}

booleano eliminarDeListaPrimero_ALU(Lista* pl, void* elem, size_t tamElem)
{
	if(!*pl)
		return falso;

	NodoD* act = *pl;

	while(act->ant)
		act = act->ant;

	NodoD* nae = act;
	act = nae->sig;

	if(act)
		act->ant = NULL;

	if(nae == *pl)
		*pl = nae->sig;

	memcpy(elem, nae->elem, min(tamElem, nae->tamElem));
	free(nae->elem);
	free(nae);

	return verdadero;
}


int cmpTransfLista_ALU(const void* e1, const void* e2)
{
	Transferencia* t1 = (Transferencia*)e1;
	Transferencia* t2 = (Transferencia*)e2;

	if(t1->depOrigen != t2->depOrigen)
		return t1->depOrigen - t2->depOrigen;

	if(t1->depDestino != t2->depDestino)
		return t1->depDestino - t2->depDestino;

	return strcmp(t1->codProd, t2->codProd);
}

void actualizarTransf_ALU(void* actualizado, const void* actualizador)
{
	Transferencia* t1 = (Transferencia*)actualizado;
	Transferencia* t2 = (Transferencia*)actualizador;

	t1->cantidad += t2->cantidad;
}
