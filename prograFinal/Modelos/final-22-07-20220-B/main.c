#include <stdio.h>
#include <stdlib.h>
#include<string.h>



#define MIN(a,b) ((a) < (b)?(a):(b))
#define SIN_MEM -1
#define TODO_OK 0
#define DUPLICADO -2
#define ERR_ARCHIVO -3



typedef struct
{
    char codProd[6];
    char sector;
    int cant;
} Pedido;

typedef struct sNodo
{
    void *dato;
    unsigned tamDato;
    struct sNodo * sig;
} Nodo;



typedef Nodo * Lista;

typedef int  (*Cmp) (const void *d1, const void * d2);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);


Nodo * crearNodo(const void * dato, unsigned tamDato);
void eliminarNodo(Nodo* nae, void * dato, unsigned tamDato);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

int listaLlena(const Lista *l, unsigned tamDato);
int listaVacia(const Lista *l);

int insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato);
int eliminarPrimeroDeLista(Lista *l, void * dato, unsigned tamDato);

int eliminarDuplicadosDeListaDesConAcum(Lista *l, Cmp cmp,Actualizar actualizar);



int creaLoteDePrueba(const char * filename);
int cargarArchivoEnLista(const char * filename, Lista *l);
int grabarListaEnArchivo(Lista *l, const char * filename);

int compararPedidos(const void * d1, const void * d2);
void actualizarPedidos(void * actualizado, const void * actualizador );

int main()
{
    char filename []= "pedidos.dat";
    Lista l;
    crearLista(&l);

    creaLoteDePrueba(filename);
    cargarArchivoEnLista(filename,&l);

    eliminarDuplicadosDeListaDesConAcum(&l,compararPedidos,actualizarPedidos);

    grabarListaEnArchivo(&l,filename);


    return 0;
}

Nodo * crearNodo(const void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));

    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }


    memcpy(nue->dato,dato,tamDato);
    nue->sig = NULL;
    nue->tamDato = tamDato;


    return nue;
}
void eliminarNodo(Nodo* nae, void * dato, unsigned tamDato)
{
    if(!nae)
        return ;

    if(dato)
        memcpy(dato,nae->dato,MIN(nae->tamDato,tamDato));
    free(nae->dato);
    free(nae);

}

void crearLista(Lista *l)
{
    *l = NULL;
}
void vaciarLista(Lista *l)
{
    Nodo * act = *l;
    Nodo * nae;
    if(!act)
        return;

    while(act)
    {
        nae = act;
        act = nae->sig;

        free(nae->dato);
        free(nae);
    }
    *l =NULL;

}

int listaLlena(const Lista *l, unsigned tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
    void *dato = malloc(tamDato);
    free(nue);
    free(dato);

    return !nue || !dato;
}
int listaVacia(const Lista *l)
{
    return *l == NULL;
}


int insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return SIN_MEM;


    while((*l))
        l = &(*l)->sig;




    *l = nue;


    return TODO_OK;
}
int eliminarPrimeroDeLista(Lista *l, void * dato, unsigned tamDato)
{

    Nodo * nae = *l;
    if(!*l)
        return -3;

    *l = nae->sig;

    eliminarNodo(nae,dato,tamDato);





    return TODO_OK;
}




int eliminarDuplicadosDeListaDesConAcum(Lista *l, Cmp cmp, Actualizar actualizar)
{
    Nodo *nae;
    Lista *lSig;
    if(!*l)
        return -3;



    while(*l)
    {
        lSig = &(*l)->sig;
        while(*lSig)
        {
            if(cmp((*l)->dato,(*lSig)->dato)==0)
            {

                nae = *lSig;
                *lSig = nae->sig;
                actualizar((*l)->dato,nae->dato);

                free(nae->dato);
                free(nae);
            }
            else
            {
                lSig = &(*lSig)->sig;
            }

        }
        l = &(*l)->sig;
    }
    return TODO_OK;
}



int creaLoteDePrueba(const char * filename)
{
    int i =0;
    Pedido p [6] =
    {
        {
            "lap",'a', 15
        },
        {
            "cua", 'b', 10
        },
        {
            "lap", 'a',25
        },
        {
            "cua", 'c', 30

        },
        {
            "cartu",'d', 50

        },
        {
            "Hojas", 'e', 1000
        }

    };
    FILE * fp = fopen(filename,"wb");
    if(!fp)
    {
        return ERR_ARCHIVO;
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO %s",filename);

    }


    for (; i<6; i++ )
    {
        fwrite(&p[i],sizeof(Pedido),1,fp);
    }

    fclose(fp);
    return TODO_OK;
}

int cargarArchivoEnLista(const char * filename, Lista *l)
{
    FILE * fp = fopen(filename,"rb");
    Pedido p;
    if(!fp)
    {
        return ERR_ARCHIVO;
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO %s",filename);

    }

    fread(&p,sizeof(Pedido),1,fp);
    while(!feof(fp))
    {
        insertarEnListaAlFinal(l,&p,sizeof(Pedido));
        fread(&p,sizeof(Pedido),1,fp);
    }

    fclose(fp);

    return TODO_OK;
}

int grabarListaEnArchivo(Lista *l, const char * filename)
{
    Pedido p;
    FILE * fp = fopen("pedidos.txt","wt");
    if(!fp)
    {
        return ERR_ARCHIVO;
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO %s","pedidos.txt");

    }



    while(!listaVacia(l))
    {
        eliminarPrimeroDeLista(l,&p,sizeof(Pedido));
        fprintf(fp,"%s|%c|%d\n",p.codProd,p.sector,p.cant);
    }

    fclose(fp);
    return TODO_OK;
}


int compararPedidos(const void * d1, const void * d2)
{
    Pedido *p1 =(Pedido *)d1;
    Pedido *p2 = (Pedido *)d2;

    return strcmp(p1->codProd,p2->codProd);
}

void actualizarPedidos(void * actualizado, const void * actualizador )
{
    Pedido *p1 =(Pedido *)actualizado;
    Pedido *p2 = (Pedido *)actualizador;

    p1->cant += p2->cant;
}
