/*****************************************************************************************************************
** Apellido/s, Nombre/s:                                      													**
**
** DNI:                                                       													**
**
******************************************************************************************************************
** Correcci�n																								   	**
** **********																								   	**
**
******************************************************************************************************************
** Nota:
*****************************************************************************************************************/

/*****************************************************************************************************************
** Descomente SOLUCION_ALU y comente SOLUCION_DOC, para probar su c�digo: 										**
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

#define MIN(x, y) (x < y) ? x : y

typedef struct
{
    int nroCliente;
    char nombre[201];
    int cantImpagos;

} Moroso;

void procesarPagos_ALU(const char *pathCli, const char *pathPagos, const char *pathListado);
int compararFecha_ALU(const Fecha *f1, const Fecha *f2);

// FUNCIONES PUNTERO
int compararPagos_ALU(const void *d1, const void *d2);
int compararClientesInd_ALU(const void *d1, const void *d2);
int compararMorosos_ALU(const void *d1, const void *d2);
void imprimirArbol_ALU(const void *elem, void *datosImprimir, int nivel);
void mostrarPagos_ALU(void *dato, void *datosAccion);
void mostrarMorosos_ALU(void *dato, void *datosAccion);
int compararMorosos2_ALU(const void *d1, const void *d2);

// FUNCIONES LISTA
NodoD *crearNodo(const void *dato, size_t tamDato);
booleano listaLlena_ALU(const Lista *pl, size_t tamElem);
booleano listaVacia_ALU(const Lista *l);
void crearLista_ALU(Lista *l);
void vaciarLista_ALU(Lista *l);

booleano eliminarDeListaPrimero_ALU(Lista *l, void *dato, size_t tamElem);
booleano insertarEnListaOrdCDup_ALU(Lista *l, const void *dato, size_t tamElem, Cmp cmp);

void recorrerLista_ALU(Lista *l, Accion accion, void *datosAccion);

// FUNCIONES ARBOl
NodoA *crearNodoA(const void *dato, size_t tamDato);
booleano cargarArbolDeArchivoOrdenado_ALU(Arbol *t, size_t tamDato, const char *nombreArch, Cmp cmp);
int buscarEnArbol_ALU(const Arbol *t, void *dato, size_t tamDato, Cmp cmp);
int vaciarArbol_ALU(Arbol *t);
void crearArbol_ALU(Arbol *t);
void cargarArbolRec_ALU(Arbol *t, size_t tamDato, int li, int ls, FILE *arch, Cmp cmp);
int insertarEnArbol_ALU(Arbol *t, const void *dato, size_t tamDato, Cmp cmp);

int main(int argc, char *argv[])
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

void procesarPagos_ALU(const char *pathCli, const char *pathPagos, const char *pathListado)
{
    FILE *fpc = fopen(pathCli, "rb");
    FILE *fpp = fopen(pathPagos, "rb");
    FILE *fpd = fopen(pathListado, "wt");
    if (!fpc || !fpp || !fpd)
    {
        fprintf(stderr, "ERROR AL ABRIR LOS ARCHIVOS ");
        return;
    }

    Cliente c;
    IndCli i;
    Pago p;

    Lista lPagos;
    Arbol aCliInd;
    crearArbol_ALU(&aCliInd);
    crearLista_ALU(&lPagos);

    // insertamos en la  lista de pagos
    fread(&p, sizeof(Pago), 1, fpp);
    while (!feof(fpp))
    {

        insertarEnListaOrdCDup_ALU(&lPagos, &p, sizeof(Pago), compararPagos_ALU);
        fread(&p, sizeof(Pago), 1, fpp);
    }

    recorrerLista_ALU(&lPagos, mostrarPagos_ALU, NULL);
    // insertamos en el arbol de clientes
    cargarArbolDeArchivoOrdenado_ALU(&aCliInd, sizeof(IndCli), "clientes.idx",compararClientesInd_ALU);
    // cargarArbolDeArchivoOrdenado(&aCliInd,sizeof(IndCli),"clientes.idx");
    imprimirArbol(&aCliInd, imprimirArbol_ALU, NULL);

    Moroso m;
    Lista lMorosos;

    crearLista_ALU(&lMorosos);
    char linea[256];
    strcpy(linea, "Nro Cliente     Nombre            Facturas en mora\n");
    fprintf(fpd, linea);

    //    Fecha fImpaga = {1, 1, 1900};

    Pago pActual;

    eliminarDeListaPrimero_ALU(&lPagos, &pActual, sizeof(Pago));
    m.cantImpagos = 0;
    m.nroCliente = pActual.nroCliente;

    if (compararFecha_ALU(&pActual.fechaVencimiento, &pActual.fechaPago) < 0)
        m.cantImpagos++;

    while (!listaVacia_ALU(&lPagos))
    {
        eliminarDeListaPrimero_ALU(&lPagos, &pActual, sizeof(Pago));
        int comp = m.nroCliente - pActual.nroCliente;
        if (comp == 0)
        {
            if (compararFecha_ALU(&pActual.fechaVencimiento, &pActual.fechaPago) < 0)
                m.cantImpagos++;
        }
        else
        {
            i.nroCliente = m.nroCliente;
            if (buscarEnArbol_ALU(&aCliInd, &i, sizeof(IndCli), compararClientesInd_ALU))
            {
                fseek(fpc, i.nroReg * sizeof(Cliente), SEEK_SET);
                fread(&c, sizeof(Cliente), 1, fpc);

                strncpy(m.nombre, c.nombre, 201);

                insertarEnListaOrdCDup_ALU(&lMorosos, &m, sizeof(Moroso), compararMorosos2_ALU);
            }

            m.nroCliente = pActual.nroCliente;
            m.cantImpagos = 0;

            if (compararFecha_ALU(&pActual.fechaVencimiento, &pActual.fechaPago) < 0)
                m.cantImpagos++;
        }
    }

    i.nroCliente = m.nroCliente;
    if (buscarEnArbol_ALU(&aCliInd, &i, sizeof(IndCli), compararClientesInd_ALU))
    {
        fseek(fpc, i.nroReg * sizeof(Cliente), SEEK_SET);
        fread(&c, sizeof(Cliente), 1, fpc);

        strncpy(m.nombre, c.nombre, 201);

        insertarEnListaOrdCDup(&lMorosos, &m, sizeof(Moroso), compararMorosos2_ALU);
    }

    while (!listaVacia(&lMorosos))
    {
        eliminarDeListaPrimero_ALU(&lMorosos, &m, sizeof(Moroso));
        fprintf(fpd, "%d\t%20s\t%d\n", m.nroCliente, m.nombre, m.cantImpagos);
        fprintf(stdout, "%d\t%20s\t%d\n", m.nroCliente, m.nombre, m.cantImpagos);
    }

    puts("Morosos");
    recorrerLista_ALU(&lMorosos, mostrarMorosos_ALU, NULL);

    fclose(fpc);
    fclose(fpp);
    fclose(fpd);
    vaciarArbol_ALU(&aCliInd);
    vaciarLista_ALU(&lPagos);
    vaciarLista_ALU(&lMorosos);
}
// FUNCIONES GENERALES

int compararFecha_ALU(const Fecha *f1, const Fecha *f2)
{
    if (f2->anio == 1900 && f2->mes == 1 && f2->dia == 1)
        return -1;

    int comp = f1->anio - f2->anio;

    if (comp == 0)
    {
        comp = f1->mes - f2->mes;
        if (comp == 0)
            comp = f1->dia - f2->dia;
    }

    return comp;
}

// FUNCIONES PUNTERO
int compararPagos_ALU(const void *d1, const void *d2)
{
    const Pago *p1 = (const Pago *)d1;
    const Pago *p2 = (const Pago *)d2;

    return p1->nroCliente - p2->nroCliente;
}
int compararClientesInd_ALU(const void *d1, const void *d2)
{
    const IndCli *i1 = (const IndCli *)d1;
    const IndCli *i2 = (const IndCli *)d2;

    return i1->nroCliente - i2->nroCliente;
}

int compararMorosos_ALU(const void *d1, const void *d2)
{
    const Moroso *m1 = (const Moroso *)d1;
    const Moroso *m2 = (const Moroso *)d2;

    return m1->cantImpagos - m2->cantImpagos;
}
int compararMorosos2_ALU(const void *d1, const void *d2)
{
    const Moroso *m1 = (const Moroso *)d1;
    const Moroso *m2 = (const Moroso *)d2;

    return m2->cantImpagos - m1->cantImpagos;
}

void imprimirArbol_ALU(const void *elem, void *datosImprimir, int nivel)
{

    for (int i = 0; i < nivel; i++)
    {
        printf("\t");
    }
    const IndCli *j = (const IndCli *)(elem);
    printf("%d %d\n", j->nroCliente, j->nroReg);
}

void mostrarPagos_ALU(void *dato, void *datosAccion)
{
    Pago *p = (Pago *)dato;
    printf("%d\t%-14s\tfv: %d/%d/%d\tfp: %d/%d/%d\t%lf\n", p->nroCliente, p->nroFactura, p->fechaVencimiento.dia, p->fechaVencimiento.mes, p->fechaVencimiento.anio, p->fechaPago.dia, p->fechaPago.mes, p->fechaPago.anio, p->importe);
}

void mostrarMorosos_ALU(void *dato, void *datosAccion)
{
    Moroso *m = (Moroso *)dato;
    printf("%d\t%-16s\t%d\n", m->nroCliente, m->nombre, m->cantImpagos);
}
// FUNCIONES LISTA
NodoD *crearNodo(const void *dato, size_t tamDato)
{
    NodoD *nue = (NodoD *)malloc(sizeof(NodoD));
    if (!nue || !(nue->elem = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->elem, dato, tamDato);
    nue->tamElem = tamDato;
    nue->ant = NULL;
    nue->sig = NULL;

    return nue;
}

booleano listaLlena_ALU(const Lista *pl, size_t tamElem)
{
    NodoD *nue = (NodoD *)malloc(sizeof(NodoD));
    void *dato = malloc(tamElem);

    free(nue);
    free(dato);

    return !nue || !dato;
}

booleano listaVacia_ALU(const Lista *l)
{
    return *l == NULL;
}
void crearLista_ALU(Lista *l)
{
    *l = NULL;
}
void vaciarLista_ALU(Lista *l)
{
    NodoD *nae;
    NodoD *act;

    if (!*l)
        return;
    act = *l;

    while (act->ant)
        act = act->ant;

    while (act)
    {
        nae = act;
        act = nae->sig;
        free(nae->elem);
        free(nae);
    }
}
booleano eliminarDeListaPrimero_ALU(Lista *l, void *dato, size_t tamElem)
{
    NodoD *act;
    NodoD *nae;
    if (!*l)
        return falso;
    act = *l;
    while (act->ant)
        act = act->ant;

    nae = act;
    act = nae->sig;

    if (act)
        act->ant = NULL;

    if (nae == *l)
        *l = nae->sig;

    memcpy(dato, nae->elem, MIN(nae->tamElem, tamElem));

    free(nae->elem);
    free(nae);

    return verdadero;
}
booleano insertarEnListaOrdCDup_ALU(Lista *l, const void *dato, size_t tamElem, Cmp cmp)
{
    NodoD *act;
    NodoD *sig = NULL;
    NodoD *ant = NULL;

    act = *l;

    if (act)
    {
        while (act->sig && cmp(dato, act->elem) > 0)
            act = act->sig;

        while (act->ant && cmp(dato, act->elem) < 0)
            act = act->ant;

        int comp = cmp(dato, act->elem);
        // el dato a insertar es mas chico que el actual
        if (comp < 0)
        {
            sig = act;
            ant = act->ant;
        }
        else // el dato a insertar es mas grande que el actual
        {
            ant = act;
            sig = act->sig;
        }
    }

    NodoD *nue = crearNodo(dato, tamElem);
    if (!nue)
        return falso;

    nue->ant = ant;
    nue->sig = sig;

    if (ant)
        ant->sig = nue;
    if (sig)
        sig->ant = nue;

    *l = nue;

    return verdadero;
}

void recorrerLista_ALU(Lista *l, Accion accion, void *datosAccion)
{

    NodoD *act;
    if (!*l)
        return;
    act = *l;
    while (act->ant)
        act = act->ant;

    while (act)
    {
        accion(act->elem, datosAccion);
        act = act->sig;
    }
}

// FUNCIONES ARBOl
NodoA *crearNodoA(const void *dato, size_t tamDato)
{

    NodoA *nue = (NodoA *)malloc(sizeof(NodoA));
    if (!nue || !(nue->elem = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->elem, dato, tamDato);
    nue->tamElem = tamDato;
    nue->hDer = NULL;
    nue->hIzq = NULL;

    return nue;
}
booleano cargarArbolDeArchivoOrdenado_ALU(Arbol *t, size_t tamDato, const char *nombreArch, Cmp cmp)
{
    FILE * fp = fopen(nombreArch,"rb");
    if(!fp)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO BINARIO DE ARBOL");
        return falso;
    }

    fseek(fp,0l,SEEK_END);
    int ls = (ftell(fp)/tamDato) -1;



    cargarArbolRec_ALU(t,tamDato,0,ls,fp,cmp);


    fclose(fp);

    return verdadero;
}

int buscarEnArbol_ALU(const Arbol *t, void *dato, size_t tamDato, Cmp cmp)
{
    if(!*t)
        return 0;

    int comp = cmp(dato,(*t)->elem);

    if(comp ==0)
    {
        memcpy(dato,(*t)->elem,MIN(tamDato,(*t)->tamElem));
        return 1;
    }

    return buscarEnArbol_ALU(comp<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}

int vaciarArbol_ALU(Arbol *t)
{
    int cne = 0;
    if (!*t)
        return 0;

    cne += vaciarArbol_ALU(&(*t)->hIzq);
    cne += vaciarArbol_ALU(&(*t)->hDer);

    free((*t)->elem);
    free(*t);
    *t = NULL;

    return cne + 1;
}
void crearArbol_ALU(Arbol *t)
{
    *t = NULL;
}
void cargarArbolRec_ALU(Arbol *t, size_t tamDato, int li, int ls, FILE *arch, Cmp cmp)
{
    if(li > ls)
        return;

    int mitad = (li +ls )/2;
    fseek(arch,mitad * tamDato,SEEK_SET);

    void * dato = malloc(tamDato);
    if(!dato )
        return ;


    fread(dato,tamDato,1,arch);

    insertarEnArbol_ALU(t,dato,tamDato,cmp);

    free(dato);

    cargarArbolRec_ALU(t,tamDato,li,mitad-1,arch,cmp);
    cargarArbolRec_ALU(t,tamDato,mitad+1,ls,arch,cmp);
}
int insertarEnArbol_ALU(Arbol *t, const void *dato, size_t tamDato, Cmp cmp)
{
    if (!*t)
    {
        *t = crearNodoA(dato, tamDato);
        if (!*t)
            return 0;
    }

// en caso de que el arbol tenga nodos
    int comp= cmp(dato,(*t)->elem);

    if(comp ==0)
        return DUPLICADO;



    return insertarEnArbol_ALU(comp<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}
