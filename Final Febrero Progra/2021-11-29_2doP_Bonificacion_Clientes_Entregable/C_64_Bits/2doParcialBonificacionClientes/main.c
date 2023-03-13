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

void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas);

bool cargarListaDeVentas_ALU(const char *nombreArch, Lista *l,Cmp cmp,Actualizar actualizar);
bool cargarIndiceDeClientes_ALU(const char * nombreArch,Arbol * t, Cmp cmp);
bool actualizarClientes_ALU(const char * nombreArch,Arbol *tIndCli, Lista *lVentas,Cmp cmp,Actualizar actualizar);
// FUNCIONES PUNTERO
int compararCodigoCliente_ALU(const void * cliente1, const void *cliente2);
int compararCodigoClienteDeIndice_ALU(const void * ind1, const void * ind2);
int compararCodigoVentas_ALU(const void * venta1, const void * venta2);

void actualizarBonificaciones_ALU(void * cliente,const void * totalCompra);
void actualizarVentas_ALU(void * venta1, const void * venta2);

void mostrarVentas_ALU(void *dato, void * dAccion);

void recorrerLista_ALU(Lista* pl, Accion accion, void* elemsAccion);
// FUNCIONES LISTA
NodoD* crearNodo_ALU(void *dato, unsigned tamDato);
bool eliminarDeListaUltimo_ALU(Lista* pl, void* dato, size_t tamDato);
void crearLista_ALU(Lista *l);
bool eliminarDeListaPrimero_ALU(Lista *l, void * dato, unsigned tamDato);
bool insertarEnListaAlFinal_ALU(Lista *l,void * dato, unsigned tamDato);
void recorrerLista_ALU(Lista* pl, Accion accion, void* elemsAccion);

void vaciarLista_ALU(Lista *l);

// FUNCIONES ARBOL
Arbol *buscarNodo_ALU(Arbol *t, void * dato, Cmp cmp);
NodoA* crearNodoA_ALU(void *dato, unsigned tamDato);
void crearArbol_ALU(Arbol* t);
booleano buscarEnArbol_ALU(const Arbol* t, void* dato, size_t tamElem, Cmp cmp);
int insertarEnArbol_ALU(Arbol* t, void* dato, size_t tamElem, Cmp cmp);
int vaciarArbol_ALU(Arbol* t);

int main()
{
    generarArchivoClientes();
    generarIndiceArchivoClientes();
    generarArchivoVentas();

    mostrarArchivoClientes();
    puts("\n");

    mostrarArchivoVentas();
    puts("\n");

    //bonificarClientes_ALU("Clientes.dat", "Clientes.idx", "Ventas.dat");
      bonificarClientes("Clientes.dat", "Clientes.idx", "Ventas.dat");

    puts("Clientes Bonificados");
    mostrarArchivoClientes();
    puts("\n");

    return 0;
}


void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas)
{
/// Resuelva esta función y todas las que invoque. Coloque el sufijo _ALU a todas ellas. Resuelva todo en este archivo main.c. No modifique ningún otro.
/// main.c es el único archivo que deberá entregar del proyecto C.

    Lista listaVentas;
    crearLista(&listaVentas);
    cargarListaDeVentas_ALU(ventas,&listaVentas,compararCodigoVentas_ALU,actualizarVentas_ALU);
    recorrerLista_ALU(&listaVentas,mostrarVentas_ALU,NULL);


    Arbol arbolIndCli;
    crearArbol_ALU(&arbolIndCli);
    cargarIndiceDeClientes_ALU(clientesInd,&arbolIndCli,compararCodigoCliente_ALU);

    actualizarClientes_ALU(clientes,&arbolIndCli,&listaVentas,compararCodigoCliente_ALU,actualizarBonificaciones_ALU);

    vaciarLista_ALU(&listaVentas);
    vaciarArbol_ALU(&arbolIndCli);
}


bool cargarListaDeVentas_ALU(const char *nombreArch, Lista *l,Cmp cmp,Actualizar actualizar)
{
    FILE * fp = fopen(nombreArch,"rb");
    if(!fp)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE VENTAS");
        return false;
    }
    Venta venta;
    fread(&venta,sizeof(Venta),1,fp);
    while(!feof(fp))
    {
        // insertarOActualizarEnListaOrd(l,&venta,sizeof(venta),cmp,actualizar);
        insertarEnListaAlFinal(l,&venta,sizeof(Venta));
        fread(&venta,sizeof(Venta),1,fp);
    }

    fclose(fp);
    return true;
}

bool cargarIndiceDeClientes_ALU(const char * nombreArch,Arbol * t, Cmp cmp)
{
    FILE * fp = fopen(nombreArch,"rb");
    if(!fp)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE INDICES");
        return false;
    }
    Indice indice;
    fread(&indice,sizeof(Indice),1,fp);
    while(!feof(fp))
    {
        insertarEnArbol(t,&indice,sizeof(Indice),cmp);
        fread(&indice,sizeof(Indice),1,fp);
    }

    fclose(fp);
    return true;
}

bool actualizarClientes_ALU(const char * nombreArch,Arbol *cliInd, Lista *vent,Cmp comparacionArbol_alu,Actualizar actualizar)
{
    FILE * archClientes = fopen(nombreArch,"r+b");
    if(!archClientes)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE CLIENTES PARA ACTUALIZAR");
        return false;
    }
    Venta vta;
    Indice idx;
    Cliente cli;

    eliminarDeListaUltimo_ALU(vent, &vta, sizeof(Venta));
    strncpy(idx.codCliente, vta.codCliente, 16);
    float precioTotal = vta.cantidad * vta.precioUnit;

    while(!listaVacia(vent))
    {
        eliminarDeListaUltimo_ALU(vent, &vta, sizeof(Venta));
        int comp = strcmp(idx.codCliente, vta.codCliente);

        if(comp != 0)
        {
            if(buscarEnArbol_ALU(cliInd, &idx, sizeof(Indice), comparacionArbol_alu))
            {
                fseek(archClientes, idx.nroReg * sizeof(Cliente), SEEK_SET);
                fread(&cli, sizeof(Cliente), 1, archClientes);
                actualizar(&cli,&precioTotal);
                fseek(archClientes,(long int) (-1 * sizeof(Cliente)), SEEK_CUR);
                fwrite(&cli, sizeof(Cliente), 1, archClientes);
                fseek(archClientes, 0l, SEEK_CUR);
            }
            strncpy(idx.codCliente, vta.codCliente, 16);
            precioTotal = vta.cantidad * vta.precioUnit;
        }
        else
        {
            precioTotal += vta.precioUnit * vta.cantidad;
        }
    }

    if(buscarEnArbol_ALU(cliInd, &idx, sizeof(Indice), comparacionArbol_alu))
    {

        fseek(archClientes, idx.nroReg * sizeof(Cliente), SEEK_SET);
        fread(&cli, sizeof(Cliente), 1, archClientes);
        actualizar(&cli,&precioTotal);


        fseek(archClientes,(long int) (-1 * sizeof(Cliente)), SEEK_CUR);
        fwrite(&cli, sizeof(Cliente), 1, archClientes);
        fseek(archClientes, 0l, SEEK_CUR);
    }

    fclose(archClientes);
    return true;
}

// FUNCIONES PUNTERO
int compararCodigoCliente_ALU(const void * cliente1, const void *cliente2)
{
    const Cliente * c1 = (const Cliente *)cliente1;
    const Cliente * c2 = (const Cliente *)cliente2;

    return strncmp(c1->codigo,c2->codigo,16);
}

int compararCodigoClienteDeIndice_ALU(const void * ind1, const void * ind2)
{
    const Indice * i1 = (const Indice *)ind1;
    const Indice * i2 = (const Indice *)ind2;

    return strncmp(i1->codCliente,i2->codCliente,16);
}

int compararCodigoVentas_ALU(const void * venta1, const void * venta2)
{
    const Venta * v1 = (const Venta*)venta1;
    const Venta * v2 = (const Venta*)venta2;

    return strcmp(v1->codCliente,v2->codCliente);
}

void actualizarBonificaciones_ALU(void * cliente,const void * totalCompra)
{
    float tc = *(const float * )totalCompra;
    Cliente * c = (Cliente *)cliente;

    if(tc >= 300000)
        c->porcBonif = 20;
    else if(tc >= 200000 && tc <= 299999)
        c->porcBonif = 10;
    else if(tc>= 100000 && tc <= 199999)
        c->porcBonif = 5;

}

void actualizarVentas_ALU(void * venta1, const void * venta2)
{
    Venta * v1 = ( Venta*)venta1;
    const   Venta * v2 = ( const Venta*)venta2;

    float aux = v1->precioUnit * v1->cantidad + v2->cantidad * v2->precioUnit;
    v1->precioUnit = aux;
}

void mostrarVentas_ALU(void *dato, void * dAccion)
{
    Venta * v = (Venta *)dato;
    printf("%-16s\t%-16s\t%.2f\t\t%d\n",v->codCliente,v->codProd,v->precioUnit,v->cantidad);
}

// FUNCIONES LISTA
NodoD* crearNodo_ALU(void *dato, unsigned tamDato)
{
    NodoD * nue = (NodoD*) malloc(sizeof(NodoD));
    if(!nue || !(nue->elem = malloc(sizeof(tamDato))))
    {
        free(nue);
        return NULL;

    }
    memcpy(nue->elem,dato,tamDato);
    nue->ant = NULL;
    nue->sig = NULL;
    return nue;
}

bool eliminarDeListaUltimo_ALU(Lista* l, void* dato, size_t tamDato)
{
    if(!*l)
        return false;
    NodoD * act = *l;
    NodoD * nae;

    while(act->sig)
    {
        act = act->sig;
    }

    nae = act;
    act = nae->ant;

    if(act)
        act->sig = NULL;

    if(*l == nae)
        *l = nae->ant;

    memcpy(dato,nae->elem,MIN(nae->tamElem,tamDato));
    free(nae->elem);
    free(nae);
    return true;
}

void crearLista_ALU(Lista *l)
{
    *l = NULL;
}


bool eliminarDeListaPrimero_ALU(Lista *l, void * dato, unsigned tamDato)
{
    if(!*l)
        return false;
    NodoD * act = *l;
    NodoD*nae;

    while(act->ant)
        act = act->ant;

    nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;

    if(nae == *l)
        *l =nae->sig;

    memcpy(dato,nae->elem,MIN(tamDato,nae->tamElem));
    free(nae->elem);
    free(nae);

    return true;

}

bool insertarEnListaAlFinal_ALU(Lista *l,void * dato, unsigned tamDato)
{
    NodoD * nue = crearNodo_ALU(dato,tamDato);

    if(!nue)
        return false;

    NodoD* act = *l;
    if(act)
    {
        while(act->sig)
            act = act->sig;
    }
    nue->ant = act;
    if(act)
    {
        act->sig = nue;
    }
    *l = nue;

    return true;
}

void recorrerLista_ALU(Lista* l, Accion accion, void* elemsAccion)
{
    if(!*l)
        return ;

    NodoD * act = *l;
    while(act->ant)
        act =act->ant;

    while(act)
    {
        accion(act->elem,elemsAccion);
        act =act->sig;
    }

}

void vaciarLista_ALU(Lista *l)
{

    NodoD * nae;
    NodoD * act = *l;
    if(act )
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

// FUNCIONES ARBOL
NodoA* crearNodoA_ALU(void *dato, unsigned tamDato)
{
    NodoA * nue = (NodoA*) malloc(sizeof(NodoA));
    if(!nue || !(nue->elem = malloc(sizeof(tamDato))))
    {
        free(nue);
        return NULL;

    }
    memcpy(nue->elem,dato,tamDato);
    nue->hIzq = NULL;
    nue->hDer = NULL;
    return nue;

}

void crearArbol_ALU(Arbol* t)
{
    *t = NULL;
}

Arbol *buscarNodo_ALU(Arbol *t, void * dato, Cmp cmp)
{
    if(!*t)
        return NULL;

    int res = cmp(dato,(*t)->elem);
    if(res == 0 )
        return t;
    return buscarNodo_ALU(res<0?&(*t)->hIzq:&(*t)->hDer,dato,cmp);
}

booleano buscarEnArbol_ALU(const Arbol* t, void* dato, size_t tamElem, Cmp cmp)
{
    if (!*t)
        return false;

    int res= cmp(dato,(*t)->elem);

    if(res == 0)
    {
        memcpy(dato,(*t)->elem,MIN(tamElem,(*t)->tamElem));
        return true;
    }
    return buscarEnArbol_ALU(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamElem,cmp);

}
int insertarEnArbol_ALU(Arbol* t, void* dato, size_t tamElem, Cmp cmp)
{
    if(!*t)
    {
        *t = crearNodoA_ALU(dato,tamElem);
        if(!*t)
            return false;

        return true;
    }
    int res = cmp(dato,(*t)->elem);

    if(res ==0 )
        return false;

    return insertarEnArbol_ALU(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamElem,cmp);


}
int vaciarArbol_ALU(Arbol* t)
{
    if(!*t)
        return 0;

    int cne = 0;

    cne +=  vaciarArbol_ALU(&(*t)->hIzq);
    cne +=  vaciarArbol_ALU(&(*t)->hDer);
    free((*t)->elem);
    free(*t);
    *t = NULL;
    return cne +1;

}
