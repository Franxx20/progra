///////// GARCETE FRANCO JAVIER 42875393
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define TODO_OK 0
#define ERR_ARCHIVO -1
#define ERR_NODO -2
#define ERR_MEM -3
#define ERR_GENERAL -4
#define ERR_LINEA_LARGA -5


typedef struct
{
    int nroPedido;
    char codPro[11];
    int cantPedida;
    char codSector;
    char oficina[21];
} Pedido;

typedef struct sNodo
{
    void * dato;
    size_t tamDato;
    struct sNodo *sig;
} Nodo;

typedef Nodo * Lista;

typedef int (*Cmp) (const void * d1,const void *d2);
typedef void (*Actualizar) (void * actualizado,const void * actualizador);
typedef void (*Mostrar) (const void * dato, FILE *stream);

// FUNCIONES GENERALES
int crearLoteDePruebas(const char * nombreArchivo);
int cargarArchivoEnLista(Lista *l, const char * nombreArchivo);
int cargarArchivoBinarioYmostrar(Lista *listaCodProd,Lista *listaCantidad, const char *nombreArchivo);
int parsear(char * linea, Pedido * pedido);

// FUNCIONES DE LISTA
Nodo * crearNodo(const void *dato, size_t tamDato);
void crearLista(Lista *l);
int vaciarLista(Lista *l);

int listaVacia(const Lista *l);

int insertarEnListaOrd(Lista *l, const void * dato,size_t tamDato,Cmp cmp,Actualizar actualizar);
int eliminarPrimeroDeLista(Lista *l, void * dato,size_t tamDato);

int recorrerLista(const Lista *l, Mostrar mostrar);
// FUNCIONES PUNTERO
int cmpCodProd(const void * d1,const void * d2);
int cmpCantidad(const void *d1,const void * d2);

void actualizarCantidad(void *actualizado, const void * actualizador);
void mostrarPedido(const void * dato, FILE * stream);

// FUNCIONES string
int strcmp_ALU(const char * s1,const char * s2);
char* strcpy_ALU(char * destino,const char *origen);
int strlen_ALU(const char * str);

char* strrchr_ALU(const char * str,int car);
char * strchr_ALU(const char * str,int car);

int main()
{
//    Pedido pedido;
    Lista listaCodProd;
    Lista listaCantidad;

    crearLista(&listaCodProd);
    crearLista(&listaCantidad);

    int res = crearLoteDePruebas("pedidos.txt");
    if(res != TODO_OK)
        return ERR_ARCHIVO;

    res = cargarArchivoEnLista(&listaCodProd,"pedidos.txt");
    puts("Lista Ordenada por codProd");
    recorrerLista(&listaCodProd,mostrarPedido);

    res = cargarArchivoBinarioYmostrar(&listaCodProd,&listaCantidad,"resultadoCompras.bin");
    if(res != TODO_OK)
        return ERR_ARCHIVO;

    vaciarLista(&listaCodProd);
    vaciarLista(&listaCantidad);

    ////////


    return 0;
}



// FUNCIONES GENERALES

int crearLoteDePruebas(const char * nombreArchivo)
{
    FILE * fp = fopen(nombreArchivo,"wt");
    int i=0;
    Pedido pedidos[]=
    {
        {
            1,"lapiz",10,'v',"venta"
        },
        {
            2,"hoja",100,'g',"gerencia"
        },
        {
            3,"lapiz",30,'v',"ventas"
        },
        {
            4,"monitor",3,'a',"atencion"
        },
        {
            5,"hoja",100,'c',"compras"
        },
        {
            6,"impresora",1,'g',"gerencia"
        },
        {
            7,"hoja",150,'g',"gerencia"
        },
        {
            8,"impresora",3,'c',"compras"
        },

        {
            9,"hoja",75,'g',"gerencia"
        },

        {
            10,"clips",400,'a',"atencion"
        },
    };
//       Pedido pedidos[]={
//        {
//            1,"a",10,'v',"venta"
//        },
//        {
//            2,"b",100,'g',"gerencia"
//        },
//        {
//            3,"a",30,'v',"ventas"
//        },
//        {
//            4,"f",3,'a',"atencion"
//        },
//        {
//            5,"b",100,'c',"compras"
//        },
//        {
//            6,"e",1,'g',"gerencia"
//        },
//        {
//            7,"b",150,'g',"gerencia"
//        },
//        {
//            8,"e",3,'c',"compras"
//        },
//    };
    if (!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    for (; i<sizeof(pedidos)/sizeof(Pedido) ; i++ )
    {
        fprintf(fp,"%d|%-10s|%d|%c|%s\n",pedidos[i].nroPedido,pedidos[i].codPro,pedidos[i].cantPedida,pedidos[i].codSector,pedidos[i].oficina);
    }


    fclose(fp);

    return TODO_OK;
}
int cargarArchivoEnLista(Lista *l, const char * nombreArchivo)
{
    Pedido pedido;
    char linea[256];
    FILE * fpTxt = fopen(nombreArchivo, "rt");
    if(!fpTxt)
    {
        fclose(fpTxt);
        return ERR_ARCHIVO;
    }

    while(fgets(linea,256,fpTxt))
    {
        parsear(linea,&pedido);
        insertarEnListaOrd(l,&pedido,sizeof(Pedido),cmpCodProd,actualizarCantidad);
    }

    fclose(fpTxt);

    return TODO_OK;
}

int cargarArchivoBinarioYmostrar(Lista *listaCodProd,Lista *listaCantidad, const char *nombreArchivo)
{
    Pedido pedido;
    FILE * fp = fopen(nombreArchivo,"wb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    while(!listaVacia(listaCodProd))
    {
        eliminarPrimeroDeLista(listaCodProd,&pedido,sizeof(Pedido));
        insertarEnListaOrd(listaCantidad,&pedido,sizeof(Pedido),cmpCantidad,NULL);
    }

//
//    puts("lista ordenada por cantidad de pedidos");
//    recorrerLista(&listaCantidad,mostrarPedido);

    while(!listaVacia(listaCantidad))
    {
        eliminarPrimeroDeLista(listaCantidad,&pedido,sizeof(Pedido));
        fwrite(&pedido,sizeof(Pedido),1,fp);

    }

    fclose(fp);

    fp = fopen(nombreArchivo,"rb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    puts("\n\nmostrando los pedidos del archivo binario ordenados por cantidad de pedidos");
    fread(&pedido,sizeof(Pedido),1,fp);
    while(!feof(fp))
    {
        mostrarPedido(&pedido,stdout);
        fread(&pedido,sizeof(Pedido),1,fp);
    }

    fclose(fp);

    return TODO_OK;
}


int parsear(char * linea, Pedido * pedido)
{
    char * aux = strchr_ALU(linea,'\n');
    if(!aux)
    {
        return ERR_LINEA_LARGA;
    }

// buscamos la oficina
    *aux = '\0';
    aux = strrchr_ALU(linea,'|');
    strcpy(pedido->oficina,aux+1);

// buscamos el codSector;
    *aux = '\0';
    aux = strrchr_ALU(linea,'|');
    pedido->codSector = *(aux+1);

// buscamos la cantidad pedida
    *aux = '\0';
    aux = strrchr_ALU(linea,'|');
    sscanf(aux+1,"%d",&pedido->cantPedida);

// buscamos el codProd
    *aux = '\0';
    aux = strrchr_ALU(linea,'|');
    strcpy(pedido->codPro,aux+1);

// buscamos el nroPedido
    *aux = '\0';
    sscanf(linea,"%d",&pedido->nroPedido);



    return TODO_OK;
}


// FUNCIONES DE LISTA
Nodo * crearNodo(const void *dato, size_t tamDato)
{
    Nodo * nue = (Nodo*)calloc(1,sizeof(Nodo));
    if (!nue || !(nue->dato= calloc(1,tamDato)))
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
    Nodo * nae;
    int cne=0;
    if(!*l)
        return cne;

    while(*l)
    {
        nae = *l;
        *l = nae->sig;
        free(nae->dato);
        free(nae);
    }

    return cne;
}

int listaVacia(const Lista *l)
{

    return *l== NULL;
}

int insertarEnListaOrd(Lista *l, const void * dato,size_t tamDato,Cmp cmp,Actualizar actualizar)
{
    Nodo * nue = crearNodo(dato,tamDato);
//int res;
    if(!nue)
    {
        return ERR_MEM;
    }

    if(*l)
    {
        while((*l) && cmp(dato,(*l)->dato)>0)
            l =&(*l)->sig;

        if((*l) && cmp(dato,(*l)->dato )==0)
        {
            if(actualizar)
            {
                actualizar((*l)->dato,dato);
                free(nue->dato);
                free(nue);
                return TODO_OK;
            }
        }
    }
    nue->sig = *l;
    *l = nue;



    return TODO_OK;
}

int eliminarPrimeroDeLista(Lista *l, void * dato,size_t tamDato)
{
    Nodo * nae;
    if(!*l)
        return ERR_NODO;

    nae = *l;
    *l= nae->sig;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);

    return TODO_OK;
}

int recorrerLista(const Lista *l, Mostrar mostrar)
{
    if(!*l)
        return ERR_NODO;

    mostrar((*l)->dato,stdout);
    recorrerLista(&(*l)->sig,mostrar);

    return TODO_OK;
}

// FUNCIONES PUNTERO
int cmpCodProd(const void * d1,const void * d2)
{
    const Pedido * p1 = (const Pedido *)d1;
    const Pedido * p2 = (const Pedido *)d2;

    return strcmp_ALU(p1->codPro,p2->codPro);
}
int cmpCantidad(const void *d1,const void * d2)
{
    const Pedido * p1 = (const Pedido *)d1;
    const Pedido * p2 = (const Pedido *)d2;

    return p2->cantPedida - p1->cantPedida;
}

void actualizarCantidad(void *actualizado, const void * actualizador)
{
    Pedido * p1 = ( Pedido *)actualizado;
    const Pedido * p2 = (const Pedido *)actualizador;

    p1->cantPedida+=p2->cantPedida;
}
void mostrarPedido(const void * dato, FILE * stream)
{
    const Pedido * pedido = (const Pedido *)dato;
    fprintf(stream,"%d|%-10s|%d|%c|%s\n",pedido->nroPedido,pedido->codPro,pedido->cantPedida,pedido->codSector,pedido->oficina);

}



// FUNCIONES string
int strcmp_ALU(const char * s1,const char * s2)
{
    while(*s1 && *s2)
    {
        if(*s1 != *s2)
            return *s1 -*s2;
        s1++;
        s2++;
    }
    return *s1 -*s2;
}
char* strcpy_ALU(char * destino,const char *origen)
{
    char * aux = destino;
    if(!destino)
        return NULL;

    while(*origen !='\0')
    {
        *destino = * origen;
        destino++;
        origen++;
    }
    return aux;
}
int strlen_ALU(const char * str)
{
    int cant= 0;
    if(!*str)
        return cant;
    while(*str)
    {
        cant++;
        str++;
    }

    return cant;
}

char* strrchr_ALU(const char * str,int car)
{

    int i=0;
    if(!*str)
        return NULL;

    while(*str)
    {
        str++;
        i++;
    }
    for (; i>0 ; i-- )
    {
        if(*str == car)
            return (char*)str;
        str--;
    }

    return NULL;
}
char * strchr_ALU(const char * str,int car)
{

    while(*str)
    {
        if(*str == car)
            return (char *)str;

        str++;
    }

    return NULL;
}
