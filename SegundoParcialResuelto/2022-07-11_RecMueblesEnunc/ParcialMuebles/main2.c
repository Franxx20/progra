#include <stdio.h>
#include <stdlib.h>

/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
* DNI: 44789809
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
#define TRANSFERENCIA_INVALIDA 10

#include <string.h>

int actualizarDepositos_ALU(const char* nombreArchTransferencias, const char* nombreArchDepositos);

/// Funciones de arboles
void crearArbol_ALU(Arbol* pa);
booleano cargarArbolDeArchivoOrdenado_ALU(Arbol* pa, size_t tamElem, const char* nombreArch, Cmp cmp);
booleano cargarArbolDeArchivoConLimites_ALU(Arbol *pa, size_t tamElem, int limInf, int limSup, FILE* arch, Cmp cmp);
int insertarEnArbol_ALU(Arbol* pa, const void* elem, size_t tamElem, Cmp cmp);
NodoA* crearNodoA_ALU(const void* elem, size_t tamElem);

/// Funciones de listas
void crearLista_ALU(Lista* pl);


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


int actualizarDepositos_ALU(const char* nombreArchTransferencias, const char* nombreArchDepositos)
{
    Arbol arbolIndices;
    crearArbol_ALU(&arbolIndices);
    cargarArbolDeArchivoOrdenado_ALU(&arbolIndices, sizeof(Indice), NOMBRE_DEP_IND, cmpInd);

    FILE* archTransferencias = fopen(nombreArchTransferencias, "rb");

    if(!archTransferencias)
        return ERR_ARCHIVO;

    Transferencia transferencia;
    Lista listaTransferencias;
    crearLista_ALU(&listaTransferencias);

    fread(&transferencia, sizeof(Transferencia), 1, archTransferencias);
    while(!feof(archTransferencias))
    {
        insertarEnListaOrdCDup(&listaTransferencias, &transferencia, sizeof(Transferencia), cmpInd);
        fread(&transferencia, sizeof(Transferencia), 1, archTransferencias);
    }
    
    fclose(archTransferencias);

    FILE* archDepositos = fopen(nombreArchDepositos, "w+b");

    if(!archDepositos)
        return ERR_ARCHIVO;

    Indice indice;
    Deposito deposito;

    while(eliminarDeListaPrimero(&listaTransferencias, &transferencia, sizeof(Transferencia)))
    {
        indice.nroDep = transferencia.depOrigen;
        strcpy(indice.codProd, transferencia.codProd);
        buscarEnArbol(&arbolIndices, &indice, sizeof(Indice), cmpInd);

        fseek(archDepositos, indice.nroReg * sizeof(Deposito), SEEK_SET);
        fread(&deposito, sizeof(Deposito), 1, archDepositos);

        if(deposito.stock - transferencia.cantidad > 0)
            deposito.stock -= transferencia.cantidad;
        else
            return TRANSFERENCIA_INVALIDA;
        
        fseek(archDepositos, (long)-sizeof(Deposito), SEEK_CUR);
        fwrite(&deposito, sizeof(Deposito), 1, archDepositos);

        indice.nroDep = transferencia.depDestino;
        strcpy(indice.codProd, transferencia.codProd);
        buscarEnArbol(&arbolIndices, &indice, sizeof(Indice), cmpInd);

        fseek(archDepositos, indice.nroReg * sizeof(Deposito), SEEK_SET);
        fread(&deposito, sizeof(Deposito), 1, archDepositos);

        deposito.stock += transferencia.cantidad;

        fseek(archDepositos, (long)-sizeof(Deposito), SEEK_CUR);
        fwrite(&deposito, sizeof(Deposito), 1, archDepositos);
    }

    fclose(archDepositos);
}


/// Funciones de arboles
void crearArbol_ALU(Arbol* pa)
{
    *pa = NULL;
}

booleano cargarArbolDeArchivoOrdenado_ALU(Arbol* pa, size_t tamElem, const char* nombreArch, Cmp cmp)
{
    FILE* arch = fopen(nombreArch, "rb");

    if(!arch)
        return falso;

    fseek(arch, 0L, SEEK_END);
    int cantBytes = ftell(arch);
    int cantRegistros = cantBytes / tamElem;

    return cargarArbolDeArchivoConLimites_ALU(pa, tamElem, 1, cantRegistros - 1, arch, cmp);
}

booleano cargarArbolDeArchivoConLimites_ALU(Arbol *pa, size_t tamElem, int limInf, int limSup, FILE* arch, Cmp cmp)
{
    if(limSup < limInf)
        return falso;

    int medio = (limSup + limInf) / 2;
    void* elem = malloc(tamElem);
    if(!elem)
        return falso;
    
    fseek(arch, medio * tamElem, SEEK_SET);
    fread(elem, tamElem, 1, arch);

    insertarEnArbol_ALU(pa, elem, tamElem, cmp);

    cargarArbolDeArchivoConLimites_ALU(pa, tamElem, limInf, medio - 1, arch, cmp);
    cargarArbolDeArchivoConLimites_ALU(pa, tamElem, medio + 1, limSup, arch, cmp);
}

int insertarEnArbol_ALU(Arbol* pa, const void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pa)
    {
        *pa = crearNodoA_ALU(elem, tamElem);
        if(!*pa)
            return SIN_MEM;
        
        return TODO_OK;
    }

    int comp = cmp(elem, (*pa)->elem);

    return insertarEnArbol_ALU( comp < 0 ?
                                &(*pa)->hIzq :
                                &(*pa)->hDer ,
                                elem, tamElem, cmp);
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
    nuevo->hDer = NULL;
    nuevo->hIzq = NULL;

    return nuevo;
}


/// Funciones de listas
void crearLista_ALU(Lista* pl)
{
    *pl = NULL;
}

int insertarEnListaOrdCDup_ALU(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
{
    /// HACELA CUANDO LLEGUES A LO DE CANDELITA BB
}