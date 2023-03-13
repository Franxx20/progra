#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define TODO_OK 0
#define ERR_ARCHIVO -1
#define ERR_NODO -2
#define ERR_GENERAL -3
#define ERR_LINEA_LARGA -4

typedef struct
{
    int nroPedido;
    char codProd[11];
    int cantPedida;
    char codSector;
    char oficina[20];
} Pedido;


typedef int (*Cmp) (const void * d1,const void *d2);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);
typedef void (*Mostrar) (const void *dato);


typedef struct sNodo
{
    void * dato;
    size_t tamDato;
    struct sNodo * sig;

} Nodo;


typedef Nodo *Lista;


//FUNCIONES LISTA
Nodo * crearNodo(const void *dato,size_t tamDato);
void crearLista(Lista *l);
int vaciarLista(Lista *l);

int listaVacia(const Lista *l);

int insertarEnListaOrdConAcum(Lista *l, const void * dato,size_t tamDato, Cmp cmp,Actualizar actualizar);
int eliminarPrimeroDeLista(Lista *l,void * dato,size_t tamDato);
int eliminarNultimosDeLista(Lista *l, int cant);
int eliminarNultimosDeListaRec(Lista *l, int cant,int cantNodos);
int recorrerLista(const Lista *l, Mostrar Mostrar);
int contarNodos(const Lista *l);

// FUNCIONES GENERALES
int crearLoteDePruebas(const char * nombreArchivo);
int cargarListas(const char *nombreArchivo,Lista *listaCxP, Lista *listaCxS);
int parsearPedidos(char * linea,Pedido * pedido);

// FUNCIONES PUNTERO
int cmpCompras(const void * d1,const void *d2);
int cmpSectores(const void *d1,const void * d2);
void acumular(void * actualizado,const void * actualizador);
//void acumularCantXsector(void * actualizado, const void * actualizador);
void mostrarCantXProductos(const void * dato);
void mostrarCantXSector(const void * dato);


int main()
{
    Lista listaCxP;
    Lista listaCxS;
    crearLista(&listaCxP);
    crearLista(&listaCxS);


    int res = crearLoteDePruebas("pedidos.txt");
    if(res != TODO_OK)
    {
        return ERR_GENERAL;
    }

    res = cargarListas("pedidos.txt",&listaCxP,&listaCxS);
    if(res != TODO_OK)
    {
        return ERR_GENERAL;
    }


    vaciarLista(&listaCxP);
    vaciarLista(&listaCxS);
    return 0;
}


Nodo * crearNodo(const void *dato,size_t tamDato)
{
    Nodo * nue =(Nodo*)calloc(1,sizeof(Nodo));
    if (!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->sig = NULL;
    nue->tamDato = tamDato;

    return nue;
}
void crearLista(Lista *l)
{
    *l =NULL;
}
int vaciarLista(Lista *l)
{
    Nodo * nae;
    int cne=0;

    while(*l)
    {
        nae = *l;
        *l = nae->sig;
        cne++;
        free(nae->dato);
        free(nae);
    }


    return cne;
}

int listaVacia(const Lista *l)
{
    return *l == NULL;
}

int insertarEnListaOrdConAcum(Lista *l, const void * dato,size_t tamDato, Cmp cmp,Actualizar actualizar)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return ERR_NODO;

    while(*l && cmp(dato,(*l)->dato)>0)
        l =&(*l)->sig;

    if(*l && cmp(dato,(*l)->dato)==0)
        if(actualizar)
        {
            actualizar((*l)->dato,dato);
            free(nue->dato);
            free(nue);

            return TODO_OK;
        }
    nue->sig = *l;
    *l = nue;


    return TODO_OK;
}
int eliminarPrimeroDeLista(Lista *l,void * dato,size_t tamDato)
{
    Nodo * nae;
    if(!*l)
        return ERR_NODO;

    nae =*l;
    *l=nae->sig;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);



    return TODO_OK;
}
int eliminarNultimosDeLista(Lista *l, int cant)
{
//    Nodo * nae;
    int tam=0;
    int i=0;
    if(!*l)
        return 0;

    tam = contarNodos(l);
    if(tam < cant)
        return 0;

    for (; i<tam-cant ; i++ )
    {
        l =&(*l)->sig;
    }
//
//    while(*l)
//    {
//        nae = *l;
//        *l =nae->sig;
//        free(nae->dato);
//        free(nae);
//    }
    vaciarLista(l);



    return 1;
}

int eliminarNultimosDeListaRec(Lista *l, int cant,int cantNodos)
{
    Nodo * nae;
    if(!*l || cant ==0)
        return cant;
    cantNodos++;
    cant = eliminarNultimosDeListaRec(&(*l)->sig,cant,cantNodos);
    if(cant>0 && cantNodos >= cant)
    {
        nae = *l;
        *l =nae->sig;
        free(nae->dato);
        free(nae);
    }
    else
    {
        return ERR_NODO;
    }

    return cant-1;
}

int recorrerLista(const Lista *l, Mostrar mostrar)
{
    if(!*l)
        return ERR_NODO;

    mostrar((*l)->dato);
    recorrerLista(&(*l)->sig,mostrar);

    return TODO_OK;
}

int contarNodos(const Lista *l)
{
    int cn=0;
    if(!*l)
        return cn;

    while((*l))
    {
        l=&(*l)->sig;
        cn++;

    }

    return cn;
}

// FUNCIONES GENERALES
int crearLoteDePruebas(const char * nombreArchivo)
{
    FILE *fp = fopen(nombreArchivo,"wt");
    int i=0;
    if (!fp)
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
int cargarListas(const char *nombreArchivo,Lista *listaCxP, Lista *listaCxS)
{
    FILE *fpTxt = fopen(nombreArchivo,"rt");
    FILE * fpBin = fopen("resultadoCompras.bin","wb");
    int res;

    if (!fpTxt || !fpBin)
    {
        fclose(fpBin);
        fclose(fpTxt);
    }

    char linea[256];
    Pedido pedido;
    while(fgets(linea,256,fpTxt))
    {
        parsearPedidos(linea,&pedido);
        insertarEnListaOrdConAcum(listaCxP,&pedido,sizeof(pedido),cmpCompras,acumular);
        insertarEnListaOrdConAcum(listaCxS,&pedido,sizeof(pedido),cmpSectores,acumular);
    }
    puts("\ncantidad por producto");
    recorrerLista(listaCxP,mostrarCantXProductos);
    puts("\ncantidad por sector y producto");
    recorrerLista(listaCxS,mostrarCantXSector);

    puts("\neliminados 2 de CxP");
//    res = eliminarNultimosDeLista(listaCxP,3);
    res = eliminarNultimosDeListaRec(listaCxP,3,0);
    if(res == ERR_NODO)
    {
        printf("error\n");
        return ERR_NODO;
    }
    recorrerLista(listaCxP,mostrarCantXProductos);

    while(!listaVacia(listaCxP))
    {
        eliminarPrimeroDeLista(listaCxP,&pedido,sizeof(Pedido));
        fwrite(&pedido,sizeof(Pedido),1,fpBin);
    }


    fclose(fpBin);
    fclose(fpTxt);

    return TODO_OK;
}
int parsearPedidos(char * linea,Pedido * pedido)
{
    char *aux;
    aux = strchr(linea,'\n');
    if(!aux)
        return ERR_LINEA_LARGA;

    *aux = '\0';
//buscamos la oficina
    aux = strrchr(linea,'|');
    strcpy(pedido->oficina,aux+1);
    *aux = '\0';

// buscamos el codSector
    aux = strrchr(linea, '|');
    sscanf(aux+1,"%c",&pedido->codSector);
    *aux = '\0';

// buscamos la cantPedida
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%d",&pedido->cantPedida);
    *aux=  '\0';

// buscamos el codProd
    aux = strrchr(linea,'|');
    strcpy(pedido->codProd,aux+1);
    *aux='\0';

// buscamos el nroPedido
    sscanf(linea,"%d",&pedido->nroPedido);


    return TODO_OK;
}


// FUNCIONES PUNTERO
int cmpCompras(const void * d1,const void *d2)
{
    const Pedido * p1 = (const Pedido *)d1;
    const Pedido * p2 = (const Pedido *)d2;

    return strcmp(p1->codProd,p2->codProd);
}
int cmpSectores(const void *d1,const void * d2)
{
    const Pedido * p1 = (const Pedido *)d1;
    const Pedido * p2 = (const Pedido *)d2;

    return p1->codSector == p2->codSector?strcmp(p1->codProd,p2->codProd):p1->codSector-p2->codSector;
}
void acumular(void * actualizado,const void * actualizador)
{
    Pedido * p1 = ( Pedido *)actualizado;
    const Pedido * p2 = (const Pedido *)actualizador;

    p1->cantPedida+=p2->cantPedida;


}
//void acumularCantXsector(void * actualizado, const void * actualizador)
//{
//    Pedido * p1 = ( Pedido *)actualizado;
//    const Pedido * p2 = (const Pedido *)actualizador;
//
//    p1->cantPedida+=p2->cantPedida;
//}


void mostrarCantXProductos(const void * dato)
{
    const Pedido *p = (const Pedido * )dato;

    fprintf(stdout, "%s %d\n",p->codProd,p->cantPedida);

}
void mostrarCantXSector(const void * dato)
{
    const Pedido *p = (const Pedido * )dato;

    fprintf(stdout, "%c %s %d\n",p->codSector,p->codProd,p->cantPedida);


}
