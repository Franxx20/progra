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
#define P1
//#define P2
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


#define MINIMO(x,y) ((x)<=(y)? (x):(y))

#include <string.h> ///despues borrar

int desencriptarTransferenciaALU(char * linea);
int parsearLinea_ALU(char * linea,Transferencia* transferencia);

int compararIndices_ALU(const void * d1, const void * d2);

// FUNCIONES DE LISTA
void crearLista_ALU(Lista *l);
void vaciarLista_ALU(Lista *l);

int listaLlena_ALU(const Lista *l, unsigned tamDato);
int listaVacia_ALU(const Lista *l);

int insertarEnListaAlFinal_ALU(Lista *l, const void * dato, unsigned tamDato);
int insertarEnListaOrd_ALU(Lista *l, const void *dato,unsigned tamDato,Cmp cmp);

booleano buscarEnListaOrd_ALU(const Lista *l, void * dato, unsigned tamDato,Cmp cmp);

int eliminarDeListaPrimero_ALU(Lista *l,void * dato, unsigned tamDato);



////////////////////////
int actualizarDepositos_ALU(const char* nombreArchTransferencias, const char* nombreArchDepositos);

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

    //actualizarDepositos("Transferencias.txt", "Depositos.dat");
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
    Lista listaIndices;

    Indice indiceDepositos;
    Transferencia transferencia;
    Deposito deposito;


    crearLista_ALU(&listaTransferencias);
    crearLista_ALU(&listaIndices);

    if(!fpTransferencia || !fpDepositos || !fpIndiceDepositos)
    {
        fprintf(stdout,"ERROR EN LA APERTURA DE LOS ARCHIVOS");
        return ERR_ARCHIVO;
    }




    while(fgets(linea,50,fpTransferencia))
    {
        parsearLinea_ALU(linea,&transferencia);
        insertarEnListaAlFinal_ALU(&listaTransferencias,&transferencia,sizeof(Transferencia));
    }

    fread(&indiceDepositos,sizeof(Indice),1,fpIndiceDepositos);
    while(!feof(fpIndiceDepositos) && !listaLlena(&listaIndices,sizeof(Indice)))
    {
        insertarEnListaOrd_ALU(&listaIndices,&indiceDepositos,sizeof(indiceDepositos),compararIndices_ALU);
        fread(&indiceDepositos,sizeof(Indice),1,fpIndiceDepositos);
    }


    while(!listaVacia(&listaTransferencias))
    {
        eliminarDeListaPrimero_ALU(&listaTransferencias,&transferencia,sizeof(Transferencia));

        indiceDepositos.nroDep = transferencia.depOrigen;
        strcpy(indiceDepositos.codProd,transferencia.codProd);

        buscarEnListaOrd_ALU(&listaIndices,&indiceDepositos,sizeof(Indice),compararIndices_ALU);
        fseek(fpDepositos,indiceDepositos.nroReg * sizeof(Deposito),SEEK_SET);
        fread(&deposito,sizeof(Deposito),1,fpDepositos);

        deposito.stock -= transferencia.cantidad;
        fseek(fpDepositos,-(long)sizeof(Indice),SEEK_CUR);
        fwrite(&deposito,sizeof(Deposito),1,fpDepositos);

        indiceDepositos.nroDep = transferencia.depDestino;
    

        buscarEnListaOrd_ALU(&listaIndices,&indiceDepositos,sizeof(Indice),compararIndices_ALU);
        fseek(fpDepositos,indiceDepositos.nroReg * sizeof(Deposito),SEEK_SET);
        fread(&deposito,sizeof(Deposito),1,fpDepositos);

        deposito.stock +=transferencia.cantidad;
        fseek(fpDepositos,-(long)sizeof(Indice),SEEK_CUR);
        fwrite(&deposito,sizeof(Deposito),1,fpDepositos);
    }




    fclose(fpTransferencia);
    fclose(fpDepositos);

    vaciarLista_ALU(&listaIndices);
    vaciarLista_ALU(&listaTransferencias);


    return TODO_OK;
}




int desencriptarTransferenciaALU(char * linea)
{

    char * inicio = linea;
    char * fin = linea + strlen(linea)-1;

    char * bufferInicio;
    char * bufferFin;

    int cantidadInicio = 0;
    int cantidadFin = 0;
    int i = 0;
    int j = 0;



    cantidadInicio = *inicio - '0';
    cantidadFin = *(fin-1) - '0';

    bufferInicio = calloc(cantidadInicio,sizeof(char));
    bufferFin = calloc(cantidadFin,sizeof(char));



    for (; i<cantidadInicio ; i++ )
    {
        *(bufferInicio+i)= *(inicio+1+i);
    }
    for (; j<cantidadFin ; j++)
    {
        *(bufferFin+j) = *(fin-2-j);
    }

    for (i=cantidadInicio; i>0; i--)
    {
        *(inicio+1) = bufferInicio[i-1];
        inicio++;
    }

    fin-=cantidadFin+1;
    for (j=0; j<cantidadFin; j++)
    {
        *fin = bufferFin[j];
        fin++;
    }





    free(bufferInicio);
    free(bufferFin);


    return TODO_OK;
}


int parsearLinea_ALU(char * linea,Transferencia* transferencia)
{
    char * aux = strchr(linea,'\n');

    if(!aux)
    {
        fprintf(stdout,"ERROR NO SE ENCUENTRA FIN DE LINEA\n");
        return ERR_LINEA;
    }

    desencriptarTransferenciaALU(linea);

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

// FUNCIONES DE LISTA
void crearLista_ALU(Lista *l)
{
    *l = NULL;
}
void vaciarLista_ALU(Lista *l)
{
    Nodo * aux;
    while(*l)
    {
        aux = *l;
        *l = aux->sig;
        free(aux->elem);
        free(aux);
    }
}

int listaLlena_ALU(const Lista *l, unsigned tamDato)
{
    Nodo * auxNodo =(Nodo * )malloc(sizeof(Nodo));
    void * auxDato = malloc(tamDato);
    free(auxDato);
    free(auxNodo);

    return !auxNodo || !auxNodo;

}
int listaVacia_ALU(const Lista *l)
{
    return *l == NULL;
}

int insertarEnListaAlFinal_ALU(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo *)malloc(sizeof(Nodo));
    if(!nue || !(nue->elem = malloc(tamDato)))
    {
        fprintf(stderr,"LISTA LLENA");
        free(nue);
        return -5;
    }
    while(*l)
        l = &(*l)->sig;

    nue->sig = NULL;
    nue->tamElem = tamDato;
    memcpy(nue->elem,dato,tamDato);
    *l = nue;

    return TODO_OK;
}


int insertarEnListaOrd_ALU(Lista *l, const void *dato,unsigned tamDato,Cmp cmp)
{
    Nodo * nue = (Nodo*  )malloc(sizeof(Nodo));
    if(!nue || !(nue->elem = malloc(tamDato)))
    {
        free(nue);
        return -5;
    }

    while(*l && cmp(dato,(*l)->elem)>0)
        l = &(*l)->sig;

    if(*l && cmp(dato,(*l)->elem)==0)
    {
        fprintf(stderr,"ERROR DATO DUPLICADO");
        free(nue->elem);
        free(nue);
        return -6;
    }

    memcpy(nue->elem,dato,tamDato);
    nue->tamElem = tamDato;

    nue->sig = *l;
    *l  = nue;


    return TODO_OK;
}

booleano buscarEnListaOrd_ALU(const Lista *l, void * dato, unsigned tamDato,Cmp cmp)
{
    if(!*l)
        return falso;

    while((*l)&& cmp(dato,(*l)->elem)>0)
        l = &(*l)->sig;

    if(!*l || cmp(dato,(*l)->elem)<0)
        return falso;

    memcpy(dato,(*l)->elem,MINIMO(tamDato,(*l)->tamElem));
    return verdadero;
}

int eliminarDeListaPrimero_ALU(Lista *l,void * dato, unsigned tamDato)
{
    Nodo * nae;
    if(!*l)
        return -7;

    nae = *l;
    *l = nae->sig;

    memcpy(dato,nae->elem,MINIMO(nae->tamElem,tamDato));
    free(nae->elem);
    free(nae);

    return TODO_OK;
}

