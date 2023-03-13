#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MIN(a,b) ((a)<(b)?(a):(b))
#define TODO_OK 0
#define ERR_ARCHIVO -1
#define ERR_NODO -2
#define ERR_EN_MAIN -3
#define ERR_MEM -4

typedef struct
{
    char cod[6];
    char tipo;
    int cant;
} Producto;

typedef struct
{
    char cod[6];
    char tipo;
    unsigned numInd;
} Indice;

// funciones generales
int crearLoteDePruebas(const char *nombreArchivo);
int crearArchivoDeIndices(const char * nombreArchivoOrig,const char * nombreArchivoIndices);
int crearArchivoDeIndices2(const char * nombreArchivoOrig,const char * nombreArchivoIndices);

typedef int (*Cmp) (const void * d1, const void *d2);
typedef void (*Actualizar) (void ** actualizado, size_t* tamDato1,const void * actualizador, size_t tamDato2);
typedef void (*Mostrar) (const void *dato, FILE * fp,int nivel);

// FUNCIONES LISTA
typedef struct sNodoD
{
    void * dato;
    size_t tamDato;
    struct sNodoD * sig;
    struct sNodoD * ant;
} NodoD;

typedef NodoD * Lista;

NodoD * crearNodoD(const void * dato,size_t tamDato);
void crearLista(Lista *l);
int vaciarLista(Lista*l);

int listaVacia(const Lista *l);
int insertarEnListaOrd(Lista *l, const void *dato, size_t tamDato, Cmp cmp,Actualizar actualizar);
int eliminarPrimeroDeLista(Lista *L, void *dato,size_t tamDato);

typedef struct sNodo
{
    void * dato;
    size_t tamDato;
    struct sNodo *hIzq;
    struct sNodo * hDer;

} NodoA;

typedef NodoA * Arbol;

// funciones Arbol

NodoA * crearNodoA(const void * dato, size_t tamDato);


Arbol *buscarNodo(Arbol *t, void * dato, Cmp cmp);
void eliminarNodo(Arbol *pnae);
int alturaArbol(const Arbol *t);
Arbol * mayorNodo(Arbol *t);
Arbol * menorNodo(Arbol *t);

int podarArbol(Arbol *t, int nivel);

void crearArbol(Arbol *t);
int vaciarArbol(Arbol *t);

int insertarEnArbol(Arbol *t, const void * dato,size_t tamDato, Cmp cmp,Actualizar acumular);
int buscarEnArbol(const Arbol *t, void * dato,size_t tamDato, Cmp cmp);
int ordenarArchivoDesdeArbolEnOrden(Arbol *t, FILE *fp);

int insertarEnArbolDesdeArchivoOrd(Arbol *t, const char * nombreArchivo,size_t tamDato,Cmp cmp,Actualizar actualizar);
int insertarEnArbolDesdeArchivoOrdRec(Arbol *t, FILE *fp,int li,int ls, size_t tamDato,Cmp cmp, Actualizar actualizar);

int eliminarDeArbol(Arbol *t, void * dato, size_t tamDato, Cmp cmp,Actualizar actualizar);

int mostrarArbolGrafico(const Arbol * t, Mostrar mostrar);
int mostrarArbolGraficoRec(const Arbol *t, Mostrar mostrar,int nivel);


int contarNodoArbolHastaNivel(const Arbol*t, int nivel);

// FUNCIONES PUNTERO
int cmpIndices(const void *d1,const void * d2);
int cmpIndices2(const void *d1,const void * d2);

void mostrarIndices(const void *dato,FILE *stream,int nivel);



int main()
{
    int res;

    res = crearLoteDePruebas("productos.dat");
    if(res != TODO_OK)
        return ERR_EN_MAIN;

    res = crearArchivoDeIndices("productos.dat","prodTC.idx");
    if(res != TODO_OK)
        return ERR_EN_MAIN;


    Arbol arbolIndices1;
    crearArbol(&arbolIndices1);
    puts("despues\n");


    insertarEnArbolDesdeArchivoOrd(&arbolIndices1,"prodTC.idx",sizeof(Indice),cmpIndices,NULL);
    mostrarArbolGrafico(&arbolIndices1,mostrarIndices);

    vaciarArbol(&arbolIndices1);
    puts("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

    Arbol arbolIndices2;
    crearArbol(&arbolIndices2);


    res = crearArchivoDeIndices2("productos.dat","prodTC2.idx");
    if(res != TODO_OK)
        return ERR_EN_MAIN;

    puts("\ndespues2\n");

    insertarEnArbolDesdeArchivoOrd(&arbolIndices2,"prodTC2.idx",sizeof(Indice),cmpIndices,NULL);
    mostrarArbolGrafico(&arbolIndices2,mostrarIndices);

    printf("\nAltura Arbol: %d\n",alturaArbol(&arbolIndices2));
    printf("nodos: %d\n",contarNodoArbolHastaNivel(&arbolIndices2,3));
    puts("antes\n");

    puts("arbol podado");
    printf("\nnodos eliminados: %d\n",podarArbol(&arbolIndices2,alturaArbol(&arbolIndices2)-2));
    mostrarArbolGrafico(&arbolIndices2,mostrarIndices);

    vaciarArbol(&arbolIndices2);

    return 0;
}

// FUNCIONES GENERALES


int crearLoteDePruebas(const char *nombreArchivo)
{
    FILE * fp = fopen(nombreArchivo,"wb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    Producto productos[] =
    {
        {"AAAAD", 'B', 100},
        {"AAAAA", 'B', 100},
        {"AAAAC", 'B', 100},
        {"AAAAG", 'C', 100},
        {"AAAAI", 'C', 100},
        {"AAAAG", 'A', 100},
        {"AAAAF", 'B', 100},
        {"AAAAE", 'A', 100},
        {"AAAAA", 'A', 100},
        {"AAAAK", 'A', 100},
        {"AAAAI", 'A', 100},
    };

    fwrite(productos,sizeof(productos),1,fp);

    fclose(fp);

    return TODO_OK;
}

int crearArchivoDeIndices(const char * nombreArchivoOrig,const char * nombreArchivoIndices)
{
    Producto producto;
    Indice indice;
    int i=0;

    Arbol arbolIndices;
    crearArbol(&arbolIndices);

    FILE *fpBin = fopen(nombreArchivoOrig,"rb");
    FILE * fpInd = fopen(nombreArchivoIndices,"wb");
    if (!fpBin || !fpInd)
    {
        fclose(fpBin);
        fclose(fpInd);

        return ERR_ARCHIVO;
    }

    fread(&producto,sizeof(Producto),1,fpBin);
    indice.numInd = i;
    strcpy(indice.cod,producto.cod);
    indice.tipo = producto.tipo;
    i++;

    while (!feof(fpBin))
    {
        insertarEnArbol(&arbolIndices,&indice,sizeof(Indice),cmpIndices,NULL);
        fread(&producto,sizeof(Producto),1,fpBin);
        indice.numInd = i;
        strcpy(indice.cod,producto.cod);
        indice.tipo = producto.tipo;
        i++;
    }

    ordenarArchivoDesdeArbolEnOrden(&arbolIndices,fpInd);

    mostrarArbolGrafico(&arbolIndices,mostrarIndices);






    fclose(fpBin);
    fclose(fpInd);


    vaciarArbol(&arbolIndices);

    return TODO_OK;
}

int crearArchivoDeIndices2(const char * nombreArchivoOrig,const char * nombreArchivoIndices)
{
    Producto producto;
    Indice indice;
    int i=0;

    Lista listaIndices;
    crearLista(&listaIndices);

    FILE *fpBin = fopen(nombreArchivoOrig,"rb");
    FILE * fpInd = fopen(nombreArchivoIndices,"wb");
    if (!fpBin || !fpInd)
    {
        fclose(fpBin);
        fclose(fpInd);

        return ERR_ARCHIVO;
    }

    fread(&producto,sizeof(Producto),1,fpBin);
    indice.numInd = i;
    strcpy(indice.cod,producto.cod);
    indice.tipo = producto.tipo;
    i++;

    while (!feof(fpBin))
    {
        insertarEnListaOrd(&listaIndices,&indice,sizeof(Indice),cmpIndices,NULL);
        fread(&producto,sizeof(Producto),1,fpBin);
        indice.numInd = i;
        strcpy(indice.cod,producto.cod);
        indice.tipo = producto.tipo;
        i++;
    }


    while(!listaVacia(&listaIndices))
    {
        eliminarPrimeroDeLista(&listaIndices,&indice,sizeof(Indice));
        fwrite(&indice,sizeof(Indice),1,fpInd);
    }





    fclose(fpBin);
    fclose(fpInd);


    vaciarLista(&listaIndices);

    return TODO_OK;
}

// FUNCIONES LISTA
NodoD * crearNodoD(const void * dato,size_t tamDato)
{
    NodoD * nue = calloc(1,sizeof(NodoD));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamDato =tamDato;
    nue->sig = NULL;
    nue->ant = NULL;


    return nue;

}
void crearLista(Lista *l)
{
    *l = NULL;
}
int vaciarLista(Lista*l)
{
    int cne= 0;
    NodoD * nae;
    NodoD * act=*l;
    if(!act)
        return cne;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        nae = act;
        act =nae->sig;

        free(nae->dato);
        free(nae);
    }

    *l = NULL;


    return cne;
}

int listaVacia(const Lista *l)
{
    return *l == NULL;
}
int insertarEnListaOrd(Lista *l, const void *dato, size_t tamDato, Cmp cmp,Actualizar actualizar)
{
    NodoD * nue = crearNodoD(dato,tamDato);
    NodoD * act = *l;
    NodoD * ant = NULL;
    NodoD * sig = NULL;
    if(!nue)
    {
        return ERR_NODO;
    }
    int res;

    if(act)
    {


        while(act->ant && cmp(dato,act->dato)<0)
            act =act->ant;
        while(act->sig && cmp(dato,act->dato)>0)
            act =act->sig;

        res = cmp(dato,act->dato);

        if(res == 0)
        {
            if(actualizar)
            {
                actualizar(&(act)->dato,&(act)->tamDato,dato,tamDato);
                *l =act;
                free(nue->dato);
                free(nue);
                return TODO_OK;
            }
        }

        else if(res <0) // si el dato a insertar es menor que el dato actual
        {
            sig= act;
            ant=act->ant;
        }
        else // si el dato a insertar es mayor al dato actual
        {
            sig =act->sig;
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
int eliminarPrimeroDeLista(Lista *l, void *dato,size_t tamDato)
{
    NodoD * act = *l;
    NodoD * nae;
    if(!act)
        return ERR_NODO;

    while(act->ant)
        act =act->ant;

    nae =act;
    act = nae->sig;
    if(nae == *l)
        *l =nae->sig;

    if(act)
        act->ant = NULL;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);

    return TODO_OK;
}



// funciones Arbol

NodoA * crearNodoA(const void * dato, size_t tamDato)
{
    NodoA * nue = calloc(1,sizeof(NodoA));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamDato =tamDato;
    nue->hIzq = NULL;
    nue->hDer = NULL;


    return nue;
}



Arbol *buscarNodo(Arbol *t, void * dato, Cmp cmp)
{
    int res;
    if(!*t)
        return NULL;

    res = cmp(dato,(*t)->dato);
    if(res ==0)
    {
        return t;
    }

    return buscarNodo(res<0?&(*t)->hIzq:&(*t)->hDer,dato,cmp);
}
void eliminarNodo(Arbol *pnae)
{
    int hi,hd;
    Arbol * pnareemp;
    if(!(*pnae)->hIzq && !(*pnae)->hDer)
    {
        free(*pnae);
        *pnae = NULL;
        return;
    }

    hi =alturaArbol(&(*pnae)->hIzq);
    hd =alturaArbol(&(*pnae)->hDer);

    pnareemp = hi>=hd?mayorNodo(&(*pnae)->hIzq):menorNodo(&(*pnae)->hDer);

    (*pnae)->dato = (*pnareemp)->dato;
    (*pnae)->tamDato =(*pnareemp)->tamDato;

    eliminarNodo(pnareemp);


}
int alturaArbol(const Arbol *t)
{
    int cni=0,cnd=0;
    if(!*t)
        return 0;

    cni += alturaArbol(&(*t)->hIzq);
    cnd += alturaArbol(&(*t)->hDer);


    return cni >= cnd?cni+1:cnd+1;
}
Arbol * mayorNodo(Arbol *t)
{
    while((*t)->hDer)
        t =&(*t)->hDer;

    return t;

}
Arbol * menorNodo(Arbol *t)
{
    while((*t)->hIzq)
        t = &(*t)->hIzq;

    return t;
}

int podarArbol(Arbol *t, int nivel)
{


//    int cne=0;
//    if(!*t)
//        return cne;
////    if(nivel==0)
////    {
////        NodoA * nae = *t;
////        free(nae->dato);
////        free(nae);
////        *t = NULL;
////    }
//
//    cne+=podarArbol(&(*t)->hIzq,nivel-1);
//    cne+=podarArbol(&(*t)->hDer,nivel-1);
//
//
//
//    if(nivel ==0)
//    {
//        vaciarArbol(t);
//    }
//
//    return cne+1;
    if(!*t)
        return 0;

    if(nivel ==0)
        return vaciarArbol(t);
    else
        return podarArbol(&(*t)->hIzq,nivel-1) + podarArbol(&(*t)->hDer,nivel-1);
}

void crearArbol(Arbol *t)
{
    *t = NULL;
}
int vaciarArbol(Arbol *t)
{

    int  cne =0;
    if(!*t)
        return cne;

    cne += vaciarArbol(&(*t)->hIzq);
    cne += vaciarArbol(&(*t)->hDer);

    free((*t)->dato);
    free(*t);
    *t = NULL;

    return cne+1;
}

int insertarEnArbol(Arbol *t, const void * dato,size_t tamDato, Cmp cmp,Actualizar acumular)
{
    int res;
    if(!*t)
    {
        *t = crearNodoA(dato,tamDato);
        if(!*t)
            return ERR_NODO;

        return TODO_OK;
    }
    res = cmp(dato,(*t)->dato);
    if(res == 0)
    {
        if(acumular)
        {
            acumular(&(*t)->dato,&(*t)->tamDato,dato,tamDato);
            return TODO_OK;
        }
    }

    return insertarEnArbol(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp,acumular);
}

int buscarEnArbol(const Arbol *t, void * dato,size_t tamDato, Cmp cmp)
{
    int res;
    if(!*t)
        return ERR_NODO;

    res = cmp(dato,(*t)->dato);
    if(res ==0)
    {
        memcpy(dato,(*t)->dato,MIN(tamDato,(*t)->tamDato));
        return TODO_OK;
    }


    return buscarEnArbol(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}

int ordenarArchivoDesdeArbolEnOrden(Arbol *t, FILE *fp)
{
    if(!*t)
        return ERR_NODO;


    // ESTO ES LECTURA EN ORDEN menor a mayor
    ordenarArchivoDesdeArbolEnOrden(&(*t)->hIzq,fp);
    fwrite((*t)->dato,(*t)->tamDato,1,fp);
    ordenarArchivoDesdeArbolEnOrden(&(*t)->hDer,fp);

//    free(dato);

    return TODO_OK;
}

int insertarEnArbolDesdeArchivoOrd(Arbol *t, const char * nombreArchivo,size_t tamDato,Cmp cmp,Actualizar actualizar)
{
    int cantBytes,cantReg;

    FILE * fp =fopen(nombreArchivo,"rb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }


    fseek(fp,0L,SEEK_END);
    cantBytes = ftell(fp);
    cantReg = cantBytes/tamDato;

    insertarEnArbolDesdeArchivoOrdRec(t,fp,0,cantReg-1,tamDato,cmp,actualizar);

    fclose(fp);
    return TODO_OK;
}
int insertarEnArbolDesdeArchivoOrdRec(Arbol *t, FILE *fp,int li,int ls, size_t tamDato,Cmp cmp, Actualizar actualizar)
{
    int mitad;
    void *registro = calloc(1,tamDato);

    if(li > ls)
        return TODO_OK;
    if(!registro)
    {
        free(registro);
        return ERR_MEM;
    }

    mitad =  (li +ls)/2;

    fseek(fp,mitad * tamDato,SEEK_SET);
    fread(registro,tamDato,1,fp);
    insertarEnArbol(t,registro,tamDato,cmp,actualizar);

    free(registro);

    insertarEnArbolDesdeArchivoOrdRec(&(*t)->hIzq,fp,li,mitad-1,tamDato,cmp,actualizar);
    insertarEnArbolDesdeArchivoOrdRec(&(*t)->hDer,fp,mitad+1,ls,tamDato,cmp,actualizar);


    return TODO_OK;
}

int eliminarDeArbol(Arbol *t, void * dato, size_t tamDato, Cmp cmp,Actualizar actualizar)
{
    Arbol * pnae  = buscarNodo(t,dato,cmp);
    if(!pnae)
        return ERR_NODO;

    memcpy(dato,(*pnae)->dato,MIN(tamDato,(*pnae)->tamDato));
    free((*pnae)->dato);

    eliminarNodo(pnae);

    return TODO_OK;
}

int mostrarArbolGrafico(const Arbol * t, Mostrar mostrar)
{
    if(!*t)
        return ERR_NODO;

    mostrarArbolGraficoRec(t,mostrar,0);


    return TODO_OK;
}

int mostrarArbolGraficoRec(const Arbol *t, Mostrar mostrar,int nivel)
{
    if(!*t)
        return ERR_NODO;

    mostrarArbolGraficoRec(&(*t)->hIzq,mostrar,nivel+1);
//    Sleep(250);
    mostrar((*t)->dato,stdout,nivel);
    mostrarArbolGraficoRec(&(*t)->hDer,mostrar,nivel+1);

    return TODO_OK;

}

int contarNodoArbolHastaNivel(const Arbol*t, int nivel){
  if(!*t)
        return 0;
    if(nivel == 0)
        return 1;

    return contarNodoArbolHastaNivel(&(*t)->hIzq,nivel-1)  + contarNodoArbolHastaNivel(&(*t)->hDer,nivel-1 ) +1;

}



// FUNCIONES PUNTERO
int cmpIndices(const void *d1,const void * d2)
{
    const Indice * i1 = (const Indice * )d1;
    const Indice * i2 =(const Indice * )d2;

    return i1->tipo == i2->tipo?strcmp(i1->cod,i2->cod):i1->tipo-i2->tipo;
}

int cmpIndices2(const void *d1,const void * d2)
{
    const Indice * i1 = (const Indice * )d1;
    const Indice * i2 =(const Indice * )d2;

    return i1->numInd - i2->numInd;
}

void mostrarIndices(const void *dato,FILE *stream,int nivel)
{
    int i=0;
    const Indice * indice = (const Indice *)dato;
    for (; i<nivel ; i++ )
    {
        fprintf(stream,"\t");
    }
    fprintf(stream,"%s|%c|%d\n",indice->cod,indice->tipo,indice->numInd);


}



