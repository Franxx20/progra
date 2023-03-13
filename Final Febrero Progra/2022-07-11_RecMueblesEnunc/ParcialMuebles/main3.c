#include <stdio.h>
#include <stdlib.h>

#define ERR_LINEA -4

/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
* DNI: 44789809
****************************************************************************************
************* Descomente el parcial que debe rendir. Si son los 2, es PI: **************
***************************************************************************************/
//#define P1
#define P2
//#define PI
/**************************************************************************************/

//#ifdef P1
//#define TDA_LISTA_IMPL_DINAMICA
//#endif

//#if defined(P2) || defined(PI)
#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"
//#endif

#include "../TDALista/TDALista.h"

#include "../SolucionMuebles/MueblesComun.h"
#include "../SolucionMuebles/SolucionMuebles.h"


#define MINIMO(x,y) ((x)<=(y)? (x):(y))

#include <string.h> ///despues borrar



////////////////////////
int actualizarDepositos_ALU(const char* nombreArchTransferencias, const char* nombreArchDepositos);


int compararIndices_ALU(const void * d1, const void * d2);

int parsearLinea_ALU(char * linea,Transferencia* transferencia);



// FUNCIONES LISTA
void crearLista_ALU(Lista *l);

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

   // actualizarDepositos("Transferencias.txt", "Depositos.dat");
    actualizarDepositos_ALU("Transferencias.txt", "Depositos.dat");

    puts("");
    puts("Depositos despues de actualizar:");
    mostrarArchivoDepositos("Depositos.dat");

    return 0;
}

int actualizarDepositos_ALU(const char* nombreArchTransferencias, const char* nombreArchDepositos)
{
    FILE * fpTransferencia = fopen(nombreArchTransferencias,"rt");
    FILE * fpDepositos = fopen(nombreArchDepositos,"r+b");
    FILE * fpIndiceDepositos = fopen("Depositos.idx","rb");

    char linea[50];

    Lista listaTransferencias;
    Arbol arbolIndices;

    Indice indiceDepositos;
    Transferencia transferencia;
    Deposito deposito;

    crearLista_ALU(&listaTransferencias);
    crearArbol(&arbolIndices);

    cargarArbolDeArchivoPreorden(&arbolIndices,sizeof(Indice),"Depositos.idx",compararIndices_ALU);



    if(!fpTransferencia || !fpDepositos || !fpIndiceDepositos)
    {
        fprintf(stdout,"ERROR EN LA APERTURA DE LOS ARCHIVOS");
        return ERR_ARCHIVO;
    }

    while(fgets(linea,50,fpTransferencia))
    {
        parsearLinea_ALU(linea,&transferencia);
        insertarEnListaAlInicio(&listaTransferencias,&transferencia,sizeof(Transferencia));

    }

    while(!listaVacia(&listaTransferencias))
    {
        eliminarDeListaPrimero(&listaTransferencias,&transferencia,sizeof(Transferencia));

        indiceDepositos.nroDep = transferencia.depOrigen;
        strcpy(indiceDepositos.codProd,transferencia.codProd);

        buscarEnArbol(&arbolIndices,&indiceDepositos,sizeof(Indice),compararIndices_ALU);
        fseek(fpDepositos,indiceDepositos.nroReg * sizeof(Deposito),SEEK_SET);
        fread(&deposito,sizeof(Deposito),1,fpDepositos);

        deposito.stock -= transferencia.cantidad;
        fseek(fpDepositos,-(long)sizeof(Indice),SEEK_CUR);
        fwrite(&deposito,sizeof(Deposito),1,fpDepositos);

        indiceDepositos.nroDep = transferencia.depDestino;


        buscarEnArbol(&arbolIndices,&indiceDepositos,sizeof(Indice),compararIndices_ALU);
        fseek(fpDepositos,indiceDepositos.nroReg * sizeof(Deposito),SEEK_SET);
        fread(&deposito,sizeof(Deposito),1,fpDepositos);

        deposito.stock +=transferencia.cantidad;
        fseek(fpDepositos,-(long)sizeof(Indice),SEEK_CUR);
        fwrite(&deposito,sizeof(Deposito),1,fpDepositos);

    }


    return TODO_OK;
}

void crearLista_ALU(Lista *l)
{
    *l = NULL;
}


int compararIndices_ALU(const void * d1, const void * d2)
{
    Indice * i1 = (Indice *)d1;
    Indice * i2 = (Indice*)d2;
    if(i1->nroDep == i2->nroDep)
    {
        return strcmp(i1->codProd,i2->codProd);
    }

    return i1->nroDep - i2->nroDep;
}

int parsearLinea_ALU(char * linea,Transferencia* transferencia)
{

    char * aux = strchr(linea,'\n');

    if(!aux)
    {
        fprintf(stdout,"ERROR NO SE ENCUENTRA FIN DE LINEA\n");
        return ERR_LINEA;
    }



    *aux = '\0';
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%d",&transferencia->cantidad);

    *aux = '\0';
    aux = strrchr(linea,'|');
    strcpy(transferencia->codProd,aux+1);

    *aux = '\0';
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%d",&transferencia->depDestino);

    sscanf(linea,"%d",&transferencia->depOrigen);







    return TODO_OK;
}
//int insertarEnListaAlFinal_ALU(Lista* l, const void* dato, size_t tamDato)
//{
//
//// primero verificamos que el nodo no este lleno
//    NodoD *nue = (NodoD *)malloc(sizeof(NodoD));
//    void *nueDato = malloc(tamDato);
//
//    if (!nue || !nueDato)
//    {
//        free(nue);
//        free(nueDato);
//        return SIN_MEM;
//    }
//
//    NodoD *act = *l;
//    // si todavia hay un nodo siguiente entonces se avanza el nodo act hasta el
//    // final de la lista
//    if (act->sig)
//        act = act->sig;
//    nue->elem = nueDato;
//    memcpy(nue->elem, dato, tamDato);
//    nue->tamElem = tamDato;
//    nue->sig = NULL;
//    nue->ant = act;
//
//    if (act)
//        act->sig = nue;
//
//    *l = nue;
//    return 1;
//}
