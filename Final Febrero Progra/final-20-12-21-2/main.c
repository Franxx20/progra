#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define TODO_OK 0
#define ERR_ARCHIVO -1
#define ERR_NODO -2
#define ERR_GENERAL -3
#define ERR_MEM -4
#define ERR_LINEA_LARGA -5
#define MIN(a,b) ((a)<(b)?(a):(b))
typedef struct
{
    int nroPedido;
    char codProd[11];
    int cantPedida;
    char codSector;
    char oficina[20];
} Pedido;

typedef struct sNodo
{
    void * dato;
    size_t tamDato;
    struct sNodo * sig;

} Nodo;

typedef Nodo * Lista;

typedef int (*Cmp) (const void * d1,const void * d2);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);
typedef void (*Mostrar) (const void * dato, FILE * stream);

// FUNCIONES GENERALES
int crearLoteDePruebas(const char * nombre);
int cargarListas(Lista * listaXCod, Lista* listaXSecYCod,const char * nombreArchivo);
int parsear(char * linea, Pedido* pedido);

// FUNCIONES LISTA
Nodo * crearNodo(const void *dato, size_t tamDato);
void crearLista(Lista *l);
int vaciarLista(Lista *l);

int listaVacia(const Lista *l);

int insertarEnListaOrd(Lista *l, const void *dato, size_t tamDato, Cmp cmp,Actualizar actualizar);
int insertarEnListaAlFinal(Lista *l,const void * dato, size_t tamDato);
int eliminarPrimeroDeLista(Lista *l, void * dato,size_t tamDato);
int eliminarUltimosNdeLaLista(Lista *l, int num);
int cantNodos(const Lista *l);

void ordenarLista (Lista *l,Cmp cmp);

int recorrerLista(const Lista *l, Mostrar mostrar);


// FUNCIONES PUNTERO
int cmpXCod(const void * d1,const void * d2);
int cmpXSectorYCod(const void * d1, const void * d2);
int cmpSector(const void *d1,const void * d2);


void acumular(void * actualizado,const void * actualizador);
void mostrarCantXProductos(const void * dato,FILE * stream);
void mostrarCantXSector(const void * dato,FILE *stream);
void mostrarPedidos(const void * dato,FILE *stream);


int main()
{
    Pedido pedido;

    Lista listaCantXCod;
    Lista listaCantXSecYCod;

    crearLista(&listaCantXCod);
    crearLista(&listaCantXSecYCod);

    FILE * fpBin;

    int res = crearLoteDePruebas("pedidos.txt");
    if(res !=TODO_OK)
        return ERR_ARCHIVO;

    res = cargarListas(&listaCantXCod,&listaCantXSecYCod,"pedidos.txt");
    if(res !=TODO_OK)
        return ERR_ARCHIVO;

    puts("lista 1\n");
    recorrerLista(&listaCantXCod,mostrarCantXProductos);
    puts("\nlista 2\n");
    recorrerLista(&listaCantXSecYCod,mostrarCantXSector);

    fpBin = fopen("resultadoCompras.bin","wb");
    if(!fpBin)
    {
        fclose(fpBin);
        return ERR_ARCHIVO;
    }

    puts("lista 1 eliminados 2\n");
    eliminarUltimosNdeLaLista(&listaCantXCod,2);
    recorrerLista(&listaCantXCod,mostrarCantXProductos);

    puts("restantes");
    while(!listaVacia(&listaCantXCod))
    {
        eliminarPrimeroDeLista(&listaCantXCod,&pedido,sizeof(Pedido));
        fprintf(stdout,"%d|%s|%d|%c|%s\n",pedido.nroPedido,pedido.codProd,pedido.cantPedida,pedido.codSector,pedido.oficina);
        fwrite(&pedido,sizeof(pedido),1,fpBin);
    }



    fclose(fpBin);

    vaciarLista(&listaCantXCod);
    vaciarLista(&listaCantXSecYCod);
    return 0;
}

// FUNCIONES GENERALES
int crearLoteDePruebas(const char * nombre)
{
    FILE * fp = fopen(nombre,"wt");
    int i=0;
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    Pedido pedidos[]=
    {
        {
            1,"lapiz",10,'v',"ventas"
        },
        {
            2,"hoja",500,'c',"compras"
        },
        {
            3,"lapiz",20,'c',"compras"
        },
        {
            4,"goma",5,'a',"atencion"
        },
        {
            5,"clip",400,'v',"ventas"
        },
        {
            6,"lapiz",30,'c',"compras"
        },
        {
            7,"clip",300,'a',"atencion"
        },
        {
            8,"hoja",1000,'v',"ventas"
        },
        {
            9,"monitor",2,'g',"gestoria"
        },
        {
            10,"monitor",4,'s',"servicio"
        },
        {
            11,"monitor",4,'s',"servicio"
        },
        {
            12,"clip",300,'v',"ventas"
        },

    };

    for (; i<sizeof(pedidos)/sizeof(Pedido) ; i++ )
    {
        fprintf(fp,"%d|%s|%d|%c|%s\n",pedidos[i].nroPedido,pedidos[i].codProd,pedidos[i].cantPedida,pedidos[i].codSector,pedidos[i].oficina);
    }

    fclose(fp);
    return TODO_OK;
}


int cargarListas(Lista * listaXCod, Lista* listaXSecYCod,const char * nombreArchivo)
{
    Pedido pedido;
    char linea[256];

    Lista listaOrdenada;
    crearLista(&listaOrdenada);

    FILE *fp = fopen(nombreArchivo,"rt");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    while(fgets(linea,256,fp))
    {
        parsear(linea,&pedido);
        insertarEnListaOrd(listaXCod,&pedido,sizeof(Pedido),cmpXCod,acumular);
        insertarEnListaAlFinal(&listaOrdenada,&pedido,sizeof(Pedido));
        insertarEnListaOrd(listaXSecYCod,&pedido,sizeof(Pedido),cmpXSectorYCod,acumular);
    }

    fclose(fp);

    recorrerLista(&listaOrdenada,mostrarPedidos);
    puts("listaOrdenada");
    ordenarLista(&listaOrdenada,cmpSector);
    recorrerLista(&listaOrdenada,mostrarPedidos);


    vaciarLista(&listaOrdenada);
    return TODO_OK;
}
int parsear(char * linea, Pedido* pedido)
{
    char * aux;
    aux = strchr(linea,'\n');
    if(!aux)
    {
        return ERR_LINEA_LARGA;
    }

    *aux = '\0';
    aux = strrchr(linea,'|');
    strcpy(pedido->oficina,aux+1);

    *aux = '\0';
    aux = strrchr(linea,'|');
    pedido->codSector = *(aux+1);

    *aux = '\0';
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%d",&pedido->cantPedida);

    *aux = '\0';
    aux = strrchr(linea,'|');
    strcpy(pedido->codProd,aux+1);
    *aux = '\0';

    sscanf(linea,"%d",&pedido->nroPedido);



    return TODO_OK;
}

// FUNCIONES LISTA
Nodo * crearNodo(const void *dato, size_t tamDato)
{
    Nodo * nue = (Nodo *)calloc(1,sizeof(Nodo));
    if (!nue || !(nue->dato = calloc(1,tamDato)))
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
    Nodo *nae;
    int cne=0;
    if(!*l)
        return cne;
    while(*l)
    {
        nae = *l;
        *l = nae->sig;
        cne++;
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
    Nodo * nue = crearNodo(dato,tamDato);
    if (!nue)
    {
        return ERR_MEM;
    }
//    int res;

    if(*l)
    {
        while((*l) && cmp(dato,(*l)->dato)>0)
            l =&(*l)->sig;


        if((*l) && cmp(dato,((*l)->dato))==0)
            if(actualizar)
            {
                actualizar((*l)->dato,dato);
                free(nue->dato);
                free(nue);

                return TODO_OK;
            }


    }

    nue->sig = *l;
    *l =nue;

    return TODO_OK;
}

int insertarEnListaAlFinal(Lista *l,const void * dato, size_t tamDato)
{
    Nodo *nue = crearNodo(dato,tamDato);
    if(!nue)
        return ERR_NODO;

    while((*l))
        l =&(*l)->sig;

    nue->sig =*l;
    *l= nue;


    return TODO_OK;
}
int eliminarPrimeroDeLista(Lista *l, void * dato,size_t tamDato)
{
    Nodo * nae;
    if(!*l)
        return ERR_NODO;

    nae = *l;
    *l =nae->sig;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);


    return TODO_OK;
}

int eliminarUltimosNdeLaLista(Lista *l, int num)
{
    int i=0;
    int tam = cantNodos(l);
    if(tam < num)
        return 0;
    if(!*l)
        return 0;
    for (; i<(tam-num) ; i++ )
    {
        l =&(*l)->sig;
    }

    i= vaciarLista(l);
    printf("cantidad de eliminados %d\n",i);


    return 1;
}

int cantNodos(const Lista *l)
{
    int cne=0;
    if(!*l)
        return cne=0;

    while(*l)
    {
        l = &(*l)->sig;
        cne++;
    }



    return cne;
}

void ordenarLista (Lista *l,Cmp cmp)
{
    void *auxDato;
    size_t auxTam;
    Lista *pri = l;
    int ordenado;

    if(!*l)
        return;


    do
    {
        l = pri;
        ordenado =0;

        while((*l)->sig)
        {
            if(cmp((*l)->dato,((*l)->sig->dato))>0)
            {
                auxDato = (*l)->dato;
                auxTam = (*l)->tamDato;

                (*l)->dato = (*l)->sig->dato;
                (*l)->tamDato = (*l)->sig->tamDato;

                (*l)->sig->dato = auxDato;
                (*l)->sig->tamDato = auxTam;

                ordenado =1;
            }
            l =&(*l)->sig;
        }

    }
    while (ordenado);

}

int recorrerLista(const Lista *l, Mostrar mostrar)
{
    if(!*l)return ERR_NODO;

    mostrar((*l)->dato,stdout);
    recorrerLista(&(*l)->sig,mostrar);

    return TODO_OK;
}



// FUNCIONES PUNTERO
int cmpXCod(const void * d1,const void * d2)
{
    const Pedido *p1 = (const Pedido *)d1;
    const Pedido * p2 =(const Pedido *)d2;


    return strcmp(p1->codProd,p2->codProd);
}

int cmpXSectorYCod(const void * d1, const void * d2)
{
    const Pedido *p1 = (const Pedido *)d1;
    const Pedido * p2 =(const Pedido *)d2;

    return p1->codSector-p2->codSector==0?strcmp(p1->codProd,p2->codProd):p1->codSector-p2->codSector;
}

int cmpSector(const void *d1,const void * d2)
{
    const Pedido *p1 = (const Pedido *)d1;
    const Pedido * p2 =(const Pedido *)d2;
    return p1->codSector-p2->codSector;
}

void acumular(void * actualizado,const void * actualizador)
{
    Pedido * p1 =(Pedido *)actualizado;
    const Pedido *p2 =(const Pedido *)actualizador;

    p1->cantPedida+=p2->cantPedida;

}
void mostrarCantXProductos(const void * dato,FILE *stream)
{
    const Pedido *p = (const Pedido *)dato;
    fprintf(stream,"%s %d\n",p->codProd,p->cantPedida);

}
void mostrarCantXSector(const void * dato,FILE *stream)
{

    const Pedido *p = (const Pedido *)dato;
    fprintf(stream,"%c %s %d\n",p->codSector,p->codProd,p->cantPedida);
}

void mostrarPedidos(const void * dato,FILE *stream)
{
    const Pedido pedido = *(const Pedido *)dato;
    fprintf(stream,"%d|%s|%d|%c|%s\n",pedido.nroPedido,pedido.codProd,pedido.cantPedida,pedido.codSector,pedido.oficina);

}

