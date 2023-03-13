#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define ERR_ARCHIVO -4
#define ERR_NODO -5
#define TODO_OK 0

typedef struct sNodoA
{
    void * dato;
    size_t tamDato;
    struct sNodoA *hIzq;
    struct sNodoA *hDer;
} NodoA;

typedef NodoA * Arbol;

typedef struct sNodoD
{
    void *dato;
    size_t tamDato;
    struct sNodoD * ant;
    struct sNodoD *sig;
} NodoD;

typedef NodoD* Lista;

typedef struct
{
    char codProd[6];
    char tipoProd;
    int cant;

} Producto;

typedef struct
{
    char codProd[6];
    char tipoProd;
    int nroReg;
} Indice;

typedef int(*Cmp) (const void *d1,const void *d2);
typedef void(*Mostrar)(const void * dato,  int nivel);

// FUNCIONES GENERALES
int crearLoteDePruebas_ALU(const char * nombreArchivo);
int crearArchivoIndice_ALU(const char * nombreArchivoIndice,const char * nombreArchivo);

void mostrarArbolIndices_ALU(const void *dato,int nivel);


// FUNCIONES ARBOL
NodoA * crearNodoA_ALU(const void * dato,size_t tamDato);

void crearArbol_ALU(Arbol *t);
int vaciarArbol_ALU(Arbol*t);

int insertarEnArbol_ALU(Arbol *t, const void * dato, size_t tamDato, Cmp cmp);
int insertarEnArbolDesdeArchivoOrdenado_ALU(const char * nombreArchivo, Arbol *t, size_t tamDato, Cmp cmp);
int insertarEnArbolDesdeArchivoOrdenadoRec_ALU(Arbol *t, int li,int ls,FILE * fp, size_t tamDato, Cmp cmp);

void mostrarArbol_ALU(const Arbol *t,Mostrar mostrar);
void mostrarArbolRec_ALU(const Arbol *t, Mostrar mostrar,int nivel);

// FUNCIONES LISTA
NodoD * crearNodoD_ALU(const void * dato, size_t tamDato);

void crearLista_ALU(Lista *l);
void vaciarLista_ALU(Lista *l);

int listaVacia_ALU(const Lista *l);
int listaLlena(const Lista *l, size_t tamDato);

int insertarEnListaOrdConACum_ALU(Lista *l,const void * dato,size_t tamDato,Cmp cmp);
int eliminarPrimeroDeLista_ALU(Lista *l, void *dato, size_t tamDato);



// FUNCIONES PUNTERO

int cmpIndices_ALU(const void *d1, const void *d2);


int main()
{
    crearLoteDePruebas_ALU("productos.dat");
    crearArchivoIndice_ALU("productos.idx", "productos.dat");

    Arbol arbolIndice;
    crearArbol_ALU(&arbolIndice);

    insertarEnArbolDesdeArchivoOrdenado_ALU("productos.idx",&arbolIndice,sizeof(Indice),cmpIndices_ALU);

    mostrarArbol_ALU(&arbolIndice,mostrarArbolIndices_ALU);

    vaciarArbol_ALU(&arbolIndice);

    return 0;
}



// FUNCIONES GENERALES
int crearLoteDePruebas_ALU(const char * nombreArchivo)
{
    FILE *fp = fopen(nombreArchivo, "wb");
    int i =0;
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    Producto productos[]=
    {
        {
            "manza",'m',100
        },
        {
            "banan",'b',50
        },
        {
            "pera",'p',75
        },
        {
            "naran", 'n',25
        },
        {
            "kiwi",'k',15
        },
        {
            "uva", 'u', 200

        },
        {
            "zana", 'z',60
        }
    };

    for (; i<7 ; i++ )
    {
        fwrite(&productos[i],sizeof(Producto),1,fp);
    }

    fclose(fp);
    return TODO_OK;
}

int crearArchivoIndice_ALU(const char * nombreArchivoIndice, const char * nombreArchivo)
{
    FILE *fpInd = fopen(nombreArchivoIndice, "wb");
    FILE * fp = fopen(nombreArchivo,"rb");
    Lista listaIndice;
    crearLista_ALU(&listaIndice);
    Indice indice;
    Producto producto;
    int i =0;
    if(!fpInd || !fp)
    {
        fclose(fp);
        fclose(fpInd);
        return ERR_ARCHIVO;
    }

    fread(&producto,sizeof(Producto),1,fp);
    while(!feof(fp))
    {
        strcpy(indice.codProd,producto.codProd);
        indice.tipoProd = producto.tipoProd;
        indice.nroReg = i;
        i++;
        insertarEnListaOrdConACum_ALU(&listaIndice,&indice,sizeof(Indice),cmpIndices_ALU);

        fread(&producto,sizeof(Producto),1,fp);
    }




    while(!listaVacia_ALU(&listaIndice))
    {
        eliminarPrimeroDeLista_ALU(&listaIndice,&indice,sizeof(Indice));
        fwrite(&indice,sizeof(Indice),1,fpInd);

    }


    fclose(fpInd);
    fclose(fp);
    vaciarLista_ALU(&listaIndice);
    return TODO_OK;
}
void mostrarArbolIndices_ALU(const void *dato,int nivel)
{
    int j= 0;
    Indice * i = (Indice *)dato;
    for (; j<nivel; j++ )
    {
        printf("\t");
    }
    printf("%s %c %d\n",i->codProd,i->tipoProd,i->nroReg);

}



// FUNCIONES ARBOL
NodoA * crearNodoA_ALU(const void * dato,size_t tamDato)
{
    NodoA * nue = (NodoA *)calloc(1,sizeof(NodoA));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->hIzq = NULL;
    nue->hDer = NULL;

    return nue;
}

void crearArbol_ALU(Arbol *t)
{
    *t = NULL;
}
int vaciarArbol_ALU(Arbol*t)
{
    int cne = 0;
    if(!*t)
        return cne;

    cne+= vaciarArbol_ALU(&(*t)->hIzq);
    cne+= vaciarArbol_ALU(&(*t)->hDer);
    free((*t)->dato);
    free((*t));

    return cne+1;
}

int insertarEnArbol_ALU(Arbol *t, const void * dato, size_t tamDato, Cmp cmp)
{
    int resultado;
    if(!*t)
    {
        *t = crearNodoA_ALU(dato,tamDato);
        if(!*t)
        {
            return ERR_NODO;
        }

        return TODO_OK;
    }
    resultado = cmp(dato,(*t)->dato);
    if(resultado ==0)
        return -3;

    return insertarEnArbol_ALU(resultado<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);

}
int insertarEnArbolDesdeArchivoOrdenado_ALU(const char * nombreArchivo, Arbol *t, size_t tamDato, Cmp cmp)
{
    FILE *fp = fopen(nombreArchivo,"rb");
    int cantBytes;
    int cantReg;
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    fseek(fp,0L,SEEK_END);

    cantBytes = ftell(fp);
    cantReg= cantBytes/tamDato;


    insertarEnArbolDesdeArchivoOrdenadoRec_ALU(t,0,cantReg-1,fp,tamDato,cmp);

    fclose(fp);
    return TODO_OK;
}
int insertarEnArbolDesdeArchivoOrdenadoRec_ALU(Arbol *t, int li,int ls,FILE * fp, size_t tamDato, Cmp cmp)
{
    int mitad;
    void * dato = calloc(1,tamDato);

    if(li > ls)
        return -6;

    mitad = (li + ls)/2;

    if(!dato)
    {
        free(dato);
        return -7;
    }
    fseek(fp,mitad*tamDato,SEEK_SET);
    fread(dato,tamDato,1,fp);

    insertarEnArbol_ALU(t,dato,tamDato,cmp);

    insertarEnArbolDesdeArchivoOrdenadoRec_ALU(t,li,mitad-1,fp,tamDato,cmp);
    insertarEnArbolDesdeArchivoOrdenadoRec_ALU(t,mitad+1,ls,fp,tamDato,cmp);

    return TODO_OK;
}

void mostrarArbol_ALU(const Arbol *t,Mostrar mostrar)
{
    mostrarArbolRec_ALU(t,mostrar,0);
}
void mostrarArbolRec_ALU(const Arbol *t, Mostrar mostrar,int nivel)
{
    if(!*t)
        return ;

    mostrarArbolRec_ALU(&(*t)->hDer,mostrar,nivel+1);
    mostrar((*t)->dato,nivel);
    mostrarArbolRec_ALU(&(*t)->hIzq,mostrar,nivel+1);
}
// FUNCIONES PUNTERO

int cmpIndices_ALU(const void *d1, const void *d2)
{
    Indice * i1 = (Indice *)d1;
    Indice * i2 = (Indice *)d2;
    int resultado = strcmp(i1->codProd,i2->codProd);

    return resultado ==0?i1->tipoProd-i2->tipoProd:resultado;

}


// FUNCIONES LISTA
NodoD * crearNodoD_ALU(const void * dato, size_t tamDato)
{
    NodoD * nue = (NodoD*)calloc(1,sizeof(NodoD));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;

    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;
    nue->ant = NULL;


    return nue;
}

void crearLista_ALU(Lista *l)
{
    *l= NULL;
}
void vaciarLista_ALU(Lista *l)
{
    NodoD * nae;
    NodoD * act;
    act = *l;
    if(act)
    {
        while(act->ant)
            act =act->ant;

        while(act)
        {
            nae = act;
            act =nae->sig;



            free(nae->dato);
            free(nae);
        }
        *l =NULL;
    }

}

int listaVacia_ALU(const Lista *l)
{
    return *l == NULL;
}
int listaLlena(const Lista *l, size_t tamDato)
{
    NodoD * nodo = (NodoD*)calloc(1,sizeof(NodoD));
    void *dato = calloc(1,tamDato);
    free(nodo);
    free(dato);
    return !nodo || !dato;
}

int insertarEnListaOrdConACum_ALU(Lista *l,const void * dato,size_t tamDato,Cmp cmp)
{
    NodoD * nue = crearNodoD_ALU(dato,tamDato);
    if(!nue)
        return -2;
    NodoD * act =*l;
    NodoD * sig = NULL;
    NodoD * ant = NULL;
    int resultado;

    if(act)
    {
        while(act->ant && cmp(dato,act->dato)<0)
            act = act ->ant;

        while(act->sig && cmp(dato,act->dato)>0)
            act =act->sig;

        resultado = cmp(dato,act->dato);

        if(resultado == 0 )
            return -7;

        // el dato a insertar es menor al dato actual
        if(resultado<0)
        {
            sig =act;
            ant = act->ant;
        }
        else // el dato a insertar es mayor al dato actual
        {
            sig = act->sig;
            ant = act;
        }
    }
    nue->sig = sig;
    nue->ant = ant;

    if(sig)
        sig->ant = nue;
    if(ant)
        ant->sig = nue;

    *l= nue;



    return TODO_OK;
}
int eliminarPrimeroDeLista_ALU(Lista *l, void *dato, size_t tamDato)
{
    NodoD * act;
    NodoD * nae;
    if(!*l)
        return -8;
    act  = *l;

    while(act->ant)
        act = act->ant;

    nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;

    if(nae == *l)
        *l = nae->sig;

    memcpy(dato,nae->dato,MIN(nae->tamDato,tamDato));

    free(nae->dato);
    free(nae);


    return TODO_OK;
}
