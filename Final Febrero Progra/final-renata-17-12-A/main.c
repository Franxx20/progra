#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

#define ERR_MEM -1
#define ERR_NODO -2
#define ERR_ARCHIVO -3
#define TODO_OK 0

typedef int (*Cmp) (const void * d1, const void * d2);
typedef void (*Actualizar) (void * actualizado,const void * actualizador);
typedef void (*Mostrar) (void * dato, void * datosAccion,FILE *fp);

typedef struct sNodo
{
    void *dato;
    size_t tamDato;
    struct sNodo *hIzq;
    struct sNodo * hDer;
} Nodo;

typedef Nodo * Arbol;

typedef struct
{
    char codigo[11];
    int sector;
    int pos;
} Indice;

typedef struct
{
    char codigo[11];
    int sector;
    int estado;

} Producto;

// FUNCIONES ARBOL

Nodo * crearNodo(const void *dato, size_t tamDato);
void crearArbol(Arbol*t);
int vaciarArbol(Arbol *t);

int ArbolLleno(Arbol*t);
int insertarEnArbol(Arbol *t, const void * dato, size_t tamDato, Cmp cmp);

int buscarMayorNodoEnArbolPorCondicion(const Arbol *t,size_t tamDato, Cmp cmp);
Nodo * buscarMayorNodoEnArbolPorCondicionRec(const Arbol *t, Nodo  * dato,size_t tamDato, Cmp cmp);

int recorrerArbolPreOrden(const Arbol *t,Mostrar mostrar, Cmp cmp);
int recorrerArbolPreOrdenRec(const Arbol *t,Mostrar mostrar, Cmp cmp,int nivel);

// FUNCIONES GENERALES
int cargarLoteDePrueba(const char * nombreArchivo);
int cargarIndicesEnArbol(Arbol *t, const char *nombreArchivo);

// FUNCIONES PUNTERO
int compararProductos(const void *d1, const void * d2);
int compararIndices(const void *d1, const void *d2);

void mostrarIndices(void *dato, void * datosAccion, FILE * fp);




int main()
{
    Arbol arbolIndices;
    crearArbol(&arbolIndices);

    cargarLoteDePrueba("productos.dat");
    cargarIndicesEnArbol(&arbolIndices,"productos.dat");
    recorrerArbolPreOrden(&arbolIndices,mostrarIndices,compararProductos);

    buscarMayorNodoEnArbolPorCondicion(&arbolIndices,sizeof(Indice),compararIndices);
    puts(" ");
    recorrerArbolPreOrden(&arbolIndices,mostrarIndices,compararIndices);
    puts(" ");
    vaciarArbol(&arbolIndices);
    return 0;
}


// FUNCIONES ARBOL

Nodo * crearNodo(const void *dato, size_t tamDato)
{
    Nodo * nue = (Nodo*)calloc(1,sizeof(Nodo));
    if(!nue||!(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue-> hDer = NULL;
    nue->hIzq =NULL;

    return nue;
}
void crearArbol(Arbol*t)
{
    *t =NULL;
}
int vaciarArbol(Arbol *t)
{
    int cne = 0;
    if(!*t)
        return cne;

    cne+=vaciarArbol(&(*t)->hIzq);
    cne+= vaciarArbol(&(*t)->hDer);

    free((*t)->dato);
    free(*t);

    return cne+1;
}

int ArbolLleno(Arbol*t);

int insertarEnArbol(Arbol *t, const void * dato, size_t tamDato, Cmp cmp)
{
    int resultado;
    if(!*t)
    {
        *t = crearNodo(dato,tamDato);
        if(!*t)
        {
            return ERR_NODO;
        }
        return TODO_OK;
    }
    resultado = cmp(dato,(*t)->dato);

    if(resultado ==0)
    {
        return ERR_NODO;
    }

    return insertarEnArbol(resultado<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}

int buscarMayorNodoEnArbolPorCondicion(const Arbol *t,size_t tamDato, Cmp cmp)
{

//    Nodo * mayor1;
//    Nodo * mayor2;
    Nodo * mayor;
    Nodo * mayor3;
    if(!*t)
        return ERR_NODO;
    int nivel =0;

    mayor =*t;
    mayor = buscarMayorNodoEnArbolPorCondicionRec(&(*t)->hDer,mayor,tamDato,cmp);

    mayor = buscarMayorNodoEnArbolPorCondicionRec(&(*t)->hIzq,mayor,tamDato,cmp);

    mayor3= buscarMayorNodoEnArbolPorCondicionRec(t,mayor,tamDato,cmp);
    puts("resultado: ");
//    mostrarIndices(mayor2->dato,&nivel,stdout);
    mostrarIndices(mayor->dato,&nivel,stdout);
    mostrarIndices(mayor3->dato,&nivel,stdout);
    return TODO_OK;
}

Nodo *  buscarMayorNodoEnArbolPorCondicionRec(const Arbol *t, Nodo * mayor,size_t tamDato, Cmp cmp)
{

    if(!*t)
        return mayor;

    if(cmp(mayor->dato,(*t)->dato)<0)
        mayor = *t;

    mayor = buscarMayorNodoEnArbolPorCondicionRec(&(*t)->hIzq,mayor,tamDato,cmp);
    mayor = buscarMayorNodoEnArbolPorCondicionRec(&(*t)->hDer,mayor,tamDato,cmp);

    return mayor;
}

int recorrerArbolPreOrden(const Arbol *t,Mostrar mostrar, Cmp cmp)
{
    if(!*t)
        return ERR_NODO;
    recorrerArbolPreOrdenRec(t,mostrar,cmp,0);

    return TODO_OK;
}

int recorrerArbolPreOrdenRec(const Arbol *t,Mostrar mostrar, Cmp cmp, int nivel)
{
    if(!*t)
        return ERR_NODO;

    recorrerArbolPreOrdenRec(&(*t)->hDer,mostrar,cmp,nivel+1);
    mostrar((*t)->dato,&nivel,stdout);
    recorrerArbolPreOrdenRec(&(*t)->hIzq,mostrar,cmp,nivel+1);

    return TODO_OK;
}

// FUNCIONES GENERALES
int cargarLoteDePrueba(const char * nombreArchivo)
{
    FILE *fp = fopen(nombreArchivo,"wb");
    int i=0;
    Producto productos[]=
    {
        {
            "manzana",'1',0
        },
        {
            "banana",'2',1
        },
        {
            "kiwi",'3',1
        },
        {
            "pera",'1',0
        },
        {
            "zanahoria",'2',1
        },
        {
            "azucar",'3',0
        },
        {
            "azucar",'1',1
        },
        {
            "maiz",'2',1
        },
        {
            "ajo",'3',1
        },
        {
            "harina",'1',1
        }
    };
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    for (; i<sizeof(productos)/sizeof(Producto) ; i++ )
    {
        if(productos[i].estado == 1)
        {
            fwrite(&productos[i],sizeof(Producto),1,fp);
        }
    }




    fclose(fp);
    return TODO_OK;
}
int cargarIndicesEnArbol(Arbol *t, const char *nombreArchivo)
{
    Indice indice;
    Producto producto;
    int i=0;
    FILE *fp = fopen(nombreArchivo,"rb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    fread(&producto,sizeof(Producto),1,fp);
    strcpy(indice.codigo,producto.codigo);
    indice.sector = producto.sector;
    indice.pos = i;
    while(!feof(fp))
    {

        insertarEnArbol(t,&indice,sizeof(Indice),compararProductos);
        i++;
        fread(&producto,sizeof(Producto),1,fp);
        strcpy(indice.codigo,producto.codigo);
        indice.sector = producto.sector;
        indice.pos = i;
    }

    fclose(fp);
    return TODO_OK;
}


// FUNCIONES PUNTERO
int compararProductos(const void *d1, const void * d2)
{
    const Producto * p1 =(const Producto *)d1;
    const Producto * p2 = (const Producto * )d2;

    if(strcmp(p1->codigo,p2->codigo)==0)
        return p1->sector - p2->sector;

    return strcmp(p1->codigo,p2->codigo);
}
int compararIndices(const void *d1, const void *d2)
{
    const Indice * i1 =(const Indice * )d1;
    const Indice * i2 =(const Indice * )d2;


    return i1->pos -i2->pos;
}


void mostrarIndices(void *dato, void * datosAccion, FILE * fp)
{
    int  nivel =*(int *)datosAccion;
    Indice * indice =(Indice * )dato;

    int i=0;

    for (; i<nivel ; i++ )
    {
        fprintf(fp,"\t");
    }
    fprintf(fp,"%s %d %d\n",indice->codigo,indice->sector,indice->pos);

}
