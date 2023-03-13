#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_ARCHIVO -3
#define ERR_NODO -2
#define ERR_MEM -1
#define TODO_OK 0

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef int (*Cmp) (const void *d1, const void *d2);
typedef void (*Actualizar) (void *actualizado,const void * actualizador);
typedef void (*Mostrar) (void * datos, FILE *fp);

typedef struct sNodo
{
    void * dato;
    struct sNodo * sig;
    size_t tamDato;
} Nodo;



typedef Nodo * Lista;

typedef struct
{
    char cod[6];
    char tipo;
    int cant;
} Producto;

// FUNCIONES GENERALES
int crearLoteDePrueba(const char * filename);
int cargarLoteDePruebaEnLista(Lista *l, const char * filename,size_t tamDato,Cmp cmp,Actualizar actualizar);


// FUNCIONES LISTA

Nodo * crearNodo(const void *dato,size_t tamDato);

void crearLista(Lista *l);
int vaciarLista(Lista *l);

int listaLlena(const Lista *l, size_t tamDato);
int listaVacia(const Lista *l);

int insertarEnListaOrd(Lista *l, const void * dato, size_t tamDato, Cmp cmp,Actualizar actualizar);
int eliminarPrimerDeLista(Lista *l, void * dato, size_t tamDato);
int eliminarNultimosDeListaRec(Lista *l, size_t tamDato, int cant);
int eliminarNprimerosDeListaRec(Lista *l, size_t tamDato, int cant);

int mostrarLista(const Lista *l, Mostrar mostrar, FILE *fp);


// FUNCIONES PUNTERO
int cmpProducto(const void * d1,const void * d2);
void actualizarProducto(void * actualizado, const void * actualizador);
void mostrarProductos(void * dato,FILE *fp);


int main()
{
    FILE *fp = fopen("productos.txt","wt");
    Lista listaProductos;
    int cant=2;
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }



    crearLista(&listaProductos);
    crearLoteDePrueba("productos.dat");
    cargarLoteDePruebaEnLista(&listaProductos,"productos.dat",sizeof(Producto),cmpProducto,actualizarProducto);
    mostrarLista(&listaProductos,mostrarProductos,stdout);
    puts("productos eliminados al final");
    eliminarNultimosDeListaRec(&listaProductos,sizeof(Producto),cant);
    mostrarLista(&listaProductos,mostrarProductos,stdout);
    puts("productos eliminados al inicio");
    eliminarNprimerosDeListaRec(&listaProductos,sizeof(Producto),cant);
    mostrarLista(&listaProductos,mostrarProductos,stdout);
    mostrarLista(&listaProductos,mostrarProductos,fp);
    fclose(fp);
    vaciarLista(&listaProductos);

    return 0;
}

// FUNCIONES GENERALES
int crearLoteDePrueba(const char * filename)
{
    Producto productos[] =
    {
        {
            "manza",'m',100
        },

        {
            "kiwi", 'k', 200
        },
        {
            "bana",'b',50
        },
        {
            "naran",'n',75
        },
        {
            "pera",'p',40
        },
        {
            "manza",'m',100
        },
        {
            "pera",'p',75
        },
        {
            "olivi",'o',10
        },
        {
            "azuca",'a',80
        },
        {
            "manda",'m',79
        },
        {
            "limon",'l',23
        }
    };
    FILE *fp =fopen(filename,"wb");
    int i=0;
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    for (; i<sizeof(productos)/sizeof(Producto) ; i++ )
    {
        fwrite(&productos[i],sizeof(Producto),1,fp);
    }

    fclose(fp);
    return TODO_OK;
}
int cargarLoteDePruebaEnLista(Lista *l, const char * filename,size_t tamDato,Cmp cmp,Actualizar actualizar)
{
    void * dato = calloc(1,tamDato);
    FILE * fp =fopen(filename,"rb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    if(!dato)
    {
        free(dato);
        return ERR_MEM;
    }


//    if(!*l)
//        return ERR_NODO;

    fread(dato,tamDato,1,fp);
    while(!feof(fp))
    {
        insertarEnListaOrd(l,dato,tamDato,cmp,actualizar);
        fread(dato,tamDato,1,fp);
    }
//    if(feof(fp))
//insertarEnListaOrd(l,dato,tamDato,cmp,actualizar);
    fclose(fp);
    free(dato);
    return TODO_OK;
}


// FUNCIONES LISTA

Nodo * crearNodo(const void *dato,size_t tamDato)
{
    Nodo * nue = (Nodo*)calloc(1,sizeof(Nodo));
    if(!nue|| !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }


    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;
    return nue;
}

void crearLista(Lista *l)
{
    *l = NULL;
}
int vaciarLista(Lista *l)
{
    int cne= 0;
    Nodo * act = *l;
    Nodo * nae;
    if(act)
    {
        while(act)
        {
            nae = act;
            act= nae->sig;

            cne++;
            free(nae->dato);
            free(nae);
        }
        *l =NULL;
    }


    return cne;
}

int listaLlena(const Lista *l, size_t tamDato)
{
    Nodo * nodo = (Nodo *)calloc(1,sizeof(Nodo));
    void * dato = calloc(1,tamDato);
    free(nodo);
    free(dato);

    return !nodo || !dato;
}
int listaVacia(const Lista *l)
{
    return *l == NULL;
}

int insertarEnListaOrd(Lista *l, const void * dato, size_t tamDato, Cmp cmp,Actualizar actualizar)
{

    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return ERR_NODO;

    if(*l)
    {

        while((*l) && cmp(dato,(*l)->dato)>0)
            l =&(*l)->sig;



        if((*l) && cmp(dato,(*l)->dato) ==0)
        {
            if(actualizar)
            {
                actualizar((*l)->dato,dato);
                free(nue->dato);
                free(nue);
            }


            return TODO_OK;
        }

    }


    nue->sig = *l;
    *l = nue;


    return TODO_OK;
}
int eliminarPrimerDeLista(Lista *l, void * dato, size_t tamDato)
{
    Nodo * nae;
    if(!*l)
        return ERR_NODO;

    nae =*l;
    *l = nae->sig;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);



    return TODO_OK;
}

int eliminarNultimosDeListaRec(Lista *l,  size_t tamDato, int  cant)
{
    int cnae =0;
    if(!*l)
        return cnae;


    cnae = eliminarNultimosDeListaRec(&(*l)->sig,tamDato,cant);
    if(cnae<cant)
    {
        free((*l)->dato);
        free(*l);

        *l= NULL;
    }

    return cnae+1;
}
int eliminarNprimerosDeListaRec(Lista *l, size_t tamDato, int cant)
{
    int cne =0;
    Nodo * nae;

    if(!*l)
        return cne;

    if(cant ==0)
        return cne;

    if(cant  > 0)
    {
        nae =*l;
        *l = nae->sig;

        cne++;

        free(nae->dato);
        free(nae);

    }
    eliminarNprimerosDeListaRec(l,tamDato,cant-1);
    return cne;
}

int mostrarLista(const Lista *l, Mostrar mostrar,FILE *fp)
{
    if(!*l)
        return ERR_NODO;
    if(*l)
        mostrar((*l)->dato,fp);
    mostrarLista(&(*l)->sig,mostrar,fp);


    return TODO_OK;
}


// FUNCIONES PUNTERO
int cmpProducto(const void * d1,const void * d2)
{
    const Producto * p1 = (const Producto *)d1;
    const Producto * p2 = (const Producto *)d2;

    return strcmp(p1->cod,p2->cod);
}
void actualizarProducto(void * actualizado, const void * actualizador)
{
    Producto * p1 =(Producto *)actualizado;
    const Producto * p2 =(const Producto* )actualizador;
    p1->cant += p2->cant;
}
void mostrarProductos(void * dato, FILE *fp)
{
    Producto * p = (Producto *)dato;
    fprintf(fp, "%s %c %d\n",p->cod,p->tipo,p->cant);
}

