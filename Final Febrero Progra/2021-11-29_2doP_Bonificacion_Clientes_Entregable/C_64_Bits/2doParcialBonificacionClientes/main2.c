#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../Solucion2doParcialBonificacionClientes/Utilitarias2doParcialBonificacionClientes.h"
#include "../Solucion2doParcialBonificacionClientes/Solucion2doParcialBonificacionClientes.h"
#include "../Solucion2doParcialBonificacionClientes/TiposArchivos.h"

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"
#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"

#include<stdbool.h>
#define MIN(a,b) ((a) < (b) ? (a) : (b))


#define ERR_NODO -2
#define ERR_MEM -3
#define ERR_REPETIDO -4

typedef struct
{
    char codCliente[16];
    float precioTotal;
    float porBonif;
    float precioBonif;
} VentasXCliente;


// FUNCIONES GENERALES
void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas);

int cargarListaDeVentas_ALU(Lista *l, const char * pathVentas);
int ordenarArchivo_ALU(const char * pathArchivo, size_t tamDato, Cmp cmp);

void calcularBonificacion_ALU(VentasXCliente *vxc);

// FUNCIONES ARBOL
NodoA * crearNodoA_ALU(const void * dato, size_t tamDato);
int insertarEnArbol_ALU(Arbol *t, void * dato, size_t tamDato, Cmp cmp);
int buscarEnArbol_ALU(const Arbol *t, void * dato, size_t tamDato, Cmp cmp);
booleano cargarArbolIndices_ALU(Arbol *t, size_t tamDato,const char * nombreArchivo);
booleano cargarArbolDeArchivoOrdenado_ALU(Arbol *t, FILE * fp,size_t tamDato, int li,int ls,Cmp cmp);
int vaciarArbol_ALU(Arbol * t);



// FUNCIONES LISTA
NodoD * creaNodoD_ALU(const void * dato, size_t tamDato);
int crearLista_ALU(Lista *l);
int vaciarLista_ALU(Lista *l);

int listaLlena_ALU(const Lista *l, size_t tamDato);
int listaVacia_ALU(const Lista *l);

int insertarEnListaAlFinal_ALU(Lista *l, const void *dato, size_t tamDato);
int insertarEnListaOrdCDup_ALU(Lista *l, const void * dato,size_t tamDato, Cmp cmp);

int eliminarDeListaPrimero_ALU(Lista *l, void * dato,size_t tamDato);


// FUNCIONES PUNTERO
int cmpVentas_ALU(const void *d1, const void * d2);
int cmpIndices_ALU(const void *d1, const void * d2);
void actualizarVentas_ALU(void * act1, const void * act2);

int main()
{
    generarArchivoClientes();
    generarIndiceArchivoClientes();
    generarArchivoVentas();


    mostrarArchivoClientes();
    puts("\n");

    mostrarArchivoVentas();
    puts("\n");

    bonificarClientes_ALU("Clientes.dat", "Clientes.idx", "Ventas.dat");
    //bonificarClientes("Clientes.dat", "Clientes.idx", "Ventas.dat");

    puts("Clientes Bonificados");
    mostrarArchivoClientes();
    puts("\n");

    return 0;
}


void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas)
{
/// Resuelva esta función y todas las que invoque. Coloque el sufijo _ALU a todas ellas. Resuelva todo en este archivo main.c. No modifique ningún otro.
/// main.c es el único archivo que deberá entregar del proyecto C.

    Cliente cliente;
    Venta venta;
    Indice indiceCliente;

    VentasXCliente vxc;

    Lista listaVentas;
    Arbol arbolIndices;

    crearLista(&listaVentas);
    crearArbol(&arbolIndices);

    FILE * fp;


    cargarListaDeVentas_ALU(&listaVentas,ventas);
    ordenarArchivo_ALU(clientesInd,sizeof(Indice), cmpIndices_ALU);
    cargarArbolIndices_ALU(&arbolIndices,sizeof(Indice),clientesInd);



    fp = fopen(clientes,"r+b");
    if(!fp)
    {
        fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE CLIENTES");
        fclose(fp);
        return ;
    }

    eliminarDeListaPrimero_ALU(&listaVentas,&venta,sizeof(Venta));
    while(!listaVacia_ALU(&listaVentas))
    {
        strcpy(vxc.codCliente,venta.codCliente);
        vxc.precioTotal= venta.precioUnit*venta.cantidad;

        eliminarDeListaPrimero_ALU(&listaVentas,&venta,sizeof(Venta));
        while(strcmp(vxc.codCliente,venta.codCliente) == 0 && !listaVacia(&listaVentas))
        {
            vxc.precioTotal+= venta.precioUnit * venta.cantidad;
            eliminarDeListaPrimero_ALU(&listaVentas,&venta,sizeof(Venta));
        }

        calcularBonificacion_ALU(&vxc);

        strcpy(indiceCliente.codCliente,vxc.codCliente);
        buscarEnArbol_ALU(&arbolIndices,&indiceCliente,sizeof(Indice),cmpIndices_ALU);

        fseek(fp,(long)indiceCliente.nroReg * sizeof(Cliente),SEEK_SET);
        fread(&cliente,sizeof(Cliente),1,fp);

        cliente.porcBonif = vxc.porBonif;

        fseek(fp,-(long)sizeof(Cliente),SEEK_CUR);
        fwrite(&cliente,sizeof(Cliente),1,fp);


    }


    vaciarLista_ALU(&listaVentas);
    vaciarArbol_ALU(&arbolIndices);

    fclose(fp);


}


int cargarListaDeVentas_ALU(Lista *l, const char * pathVentas)
{
    FILE * fp = fopen(pathVentas,"rb");
    Venta venta;
    if(!fp)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE VENTAS");
        fclose(fp);
        return ERR_ARCHIVO;
    }
    fread(&venta,sizeof(Venta),1,fp);
    while(!feof(fp)&&!listaLlena_ALU(l,sizeof(Venta)))
    {
        insertarEnListaAlFinal_ALU(l,&venta,sizeof(Venta));
        fread(&venta,sizeof(Venta),1,fp);
    }



    fclose(fp);

    return TODO_OK;
}

int ordenarArchivo_ALU(const char * pathArchivo, size_t tamDato, Cmp cmp)
{
    void * dato = calloc(1,tamDato);
    FILE *fp = fopen(pathArchivo,"rb");
    FILE * fpTemp = fopen("temp.bin", "wb");

    Lista lista;

    if(!fp || !fpTemp)
    {
        fclose(fp);
        fclose(fpTemp);
        return ERR_ARCHIVO;
    }

    crearLista_ALU(&lista);

    if(!dato)
    {
        free(dato);
        return ERR_MEM;
    }

    fread(dato,tamDato,1,fp);
    while(!feof(fp) && !listaLlena_ALU(&lista,tamDato))
    {
        insertarEnListaOrdCDup_ALU(&lista,dato,tamDato,cmp);
        fread(dato,tamDato,1,fp);
    }

    while(!listaVacia(&lista))
    {
        eliminarDeListaPrimero_ALU(&lista,dato,tamDato);
        fwrite(dato,tamDato,1,fpTemp);
    }

    free(dato);
    vaciarLista_ALU(&lista);

    fclose(fp);
    fclose(fpTemp);

    remove(pathArchivo);
    rename("temp.bin",pathArchivo);

    return TODO_OK;
}

void calcularBonificacion_ALU(VentasXCliente* vxc)
{
    if(vxc->precioTotal >= 300000)
    {
        vxc->porBonif = 20;
        vxc->precioBonif = vxc->precioTotal - ((vxc->precioTotal * vxc->porBonif)/100);
    }
    else if(vxc->precioTotal>= 200000)
    {
        vxc->porBonif = 10;
        vxc->precioBonif = vxc->precioTotal - ((vxc->precioTotal * vxc->porBonif)/100);
    }
    else if(vxc->precioTotal >= 100000)
    {
        vxc->porBonif = 5;
        vxc->precioBonif = vxc->precioTotal - ((vxc->precioTotal * vxc->porBonif)/100);
    }
    else
    {
        vxc->precioBonif = vxc->precioTotal;
        vxc->porBonif =0;
    }
}
// FUNCIONES ARBOL

NodoA * crearNodoA_ALU(const void * dato, size_t tamDato)
{
    NodoA * nue = (NodoA * )calloc(1,sizeof(NodoA));
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
int insertarEnArbol_ALU(Arbol *t, void * dato, size_t tamDato, Cmp cmp)
{
    int resultado;
    if(!*t)
    {
        *t  = crearNodoA_ALU(dato,tamDato);
        if(!*t)
            return ERR_NODO;

        return TODO_OK;
    }
    resultado = cmp((*t)->elem,dato);


    if(resultado ==0)
        return ERR_REPETIDO;

    return insertarEnArbol_ALU(resultado>0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);

}

int buscarEnArbol_ALU(const Arbol *t, void * dato, size_t tamDato, Cmp cmp)
{
    int resultado;
    if(!*t)
    {
        return ERR_NODO;
    }
    resultado = cmp((*t)->elem,dato);

    if(resultado ==0)
    {
        memcpy(dato,(*t)->elem,MIN(tamDato,(*t)->tamElem));
        return TODO_OK;
    }

    return buscarEnArbol_ALU(resultado>0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}
booleano cargarArbolIndices_ALU(Arbol *t, size_t tamDato,const char * nombreArchivo)
{
    FILE * fp = fopen(nombreArchivo,"rb");
    int cantBytes;
    int cantRegistros;
    if(!fp)
    {
        fclose(fp);
        return falso;
    }

    fseek(fp,0L,SEEK_END);
    cantBytes = ftell(fp);
    cantRegistros = cantBytes/ sizeof(Indice);
    cargarArbolDeArchivoOrdenado_ALU(t,fp,tamDato,0,cantRegistros-1,cmpIndices_ALU);
    fclose(fp);


    return verdadero;
}

int vaciarArbol_ALU(Arbol * t){
    int cne =0;
    if(!*t)
        return cne;

    cne+= vaciarArbol_ALU(&(*t)->hIzq);
    cne+= vaciarArbol_ALU(&(*t)->hDer);

    free((*t)->elem);
    free((*t));


    return cne + 1;

}

booleano cargarArbolDeArchivoOrdenado_ALU(Arbol *t, FILE * fp,size_t tamDato, int li,int ls,Cmp cmp)
{
    int mitad;
    void * dato = calloc(1,tamDato);
    if(li > ls)
        return falso;
    if(!dato)
    {
        free(dato);
        return falso;
    }
    mitad = (li + ls )/2;

    fseek(fp,(long)mitad* tamDato,SEEK_SET);
    fread(dato,tamDato,1,fp);
    insertarEnArbol_ALU(t,dato,tamDato,cmp);

    cargarArbolDeArchivoOrdenado_ALU(t,fp,tamDato,li,mitad-1,cmp);
    cargarArbolDeArchivoOrdenado_ALU(t,fp,tamDato,mitad+1,ls,cmp);

    free(dato);

    return verdadero;
}

// FUNCIONES LISTA


NodoD * creaNodoD_ALU(const void * dato, size_t tamDato)
{
    NodoD * nue = (NodoD * )calloc(1,sizeof(NodoD));
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
int crearLista_ALU(Lista *l)
{
    *l = NULL;
    return TODO_OK;
}
int vaciarLista_ALU(Lista *l)
{
    NodoD * nae;
    NodoD * act;
    int cne =0;
    if(!*l)
        return cne;
    act =*l;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        nae = act;
        act = nae->sig;


        free(nae->elem);
        free(nae);
        cne++;

    }
    *l = NULL;

    return cne;
}

int listaLlena_ALU(const Lista *l, size_t tamDato)
{
    NodoD * nodoAux = (NodoD*)calloc(1,sizeof(NodoD));
    void * datoAux = calloc(1,tamDato);

    free(nodoAux);
    free(datoAux);

    return !nodoAux || !datoAux;
}
int listaVacia_ALU(const Lista *l)
{
    return *l == NULL;
}

int insertarEnListaAlFinal_ALU(Lista *l, const void *dato, size_t tamDato)
{
    NodoD * nue = creaNodoD_ALU(dato,tamDato);
    NodoD * act;
    if(!nue)
        return ERR_NODO;
    act = *l;

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
int insertarEnListaOrdCDup_ALU(Lista *l, const void * dato,size_t tamDato, Cmp cmp)
{
    NodoD * nue = creaNodoD_ALU(dato,tamDato);
    NodoD * act;
    NodoD * sig = NULL;
    NodoD * ant = NULL;
    int resultado;
    if(!nue)
        return ERR_NODO;

    act = *l;

    if(act)
    {
        while(act->ant && cmp(dato,act->elem)< 0)
            act =act->ant;

        while(act->sig && cmp(dato,act->elem)>0)
            act = act->sig;

        resultado = cmp(dato,act->elem);

        // el dato a insertar es mas chico que el dato actual
        if (resultado < 0)
        {
            sig = act;
            ant = act->ant;
        }
        else // el dato a insertar es mas grande que el dato actual
        {
            ant = act;
            sig = act->sig;
        }

    }
    nue->sig = sig;
    nue->ant  = ant;

    if(sig)
        sig->ant = nue;

    if(ant)
        ant->sig =nue;

    *l = nue;
    return TODO_OK;
}
int eliminarDeListaPrimero_ALU(Lista *l, void * dato,size_t tamDato)
{
    NodoD * nae;
    NodoD * act;
    if(!*l)
        return ERR_NODO;
    act = *l;

    while(act->ant)
        act = act->ant;

    nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;

    if(nae == *l)
        *l =nae->sig;

    mempcpy(dato,nae->elem,MIN(nae->tamElem,tamDato));
    free(nae->elem);
    free(nae);


    return TODO_OK;
}


// FUNCIONES PUNTERO
int cmpVentas_ALU(const void *d1, const void * d2)
{
    Venta * venta1 = (Venta * )d1;
    Venta * venta2 = (Venta * )d2;

    return strcmp(venta1->codCliente,venta2->codCliente);
}

int cmpIndices_ALU(const void *d1, const void * d2)
{
    Indice * i1 = (Indice * )d1;
    Indice * i2 =(Indice * )d2;

    return strcmp(i1->codCliente,i2->codCliente);
}
void actualizarVentas_ALU(void * act1, const void * act2)
{
//    Venta * actualizado = (Venta * )act1;
//    const  Venta * actualizador = (const Venta * )act2;

}
