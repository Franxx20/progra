#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>

#define min(a,b) ((a)<(b)?(a):(b))
#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_LINEA_LARGA 2
#define  ERR_NODO 3
#define REPETIDO 4

typedef struct
{
    int nroPedido;
    char codProd[11];
    int cantPedida;
    char codSector;
    char oficina[21];
} Pedido;

typedef struct
{
    char codProd[11];
    int cantPedida;
} Compra;

typedef struct
{
    char codSector;
    char codProd[11];
    int cantPorSector;
    int cantProducto;
} Sector;



// LISTA
typedef struct sNodo
{
    void *dato;
    unsigned tamDato;
    struct sNodo * sig;
    struct sNodo * ant;
} Nodo;

typedef int (*Cmp) (const void *d1, const void *d2);
typedef void (*Actualizar) (void * actualizado, const void *actualizador);
typedef void (*Accion) (void *Accion, void *datosAccion);
typedef void (*Mostrar) (void *dato, FILE * stream);

typedef Nodo *Lista;

Nodo * crearNodo(void *dato, unsigned tamDato);
void vaciarNodo(Nodo *nae, void * dato,unsigned tamDato);

void crearLista(Lista *L);
int vaciarLista(Lista *L);

bool listaLlena(const Lista *l, unsigned tamDato);
bool listaVacia(const Lista *l);

int insertarEnListaOrdConAcum(Lista *l, const void *dato, unsigned tamDato, Cmp cmp, Actualizar actualizar);

void mostrarLista(const Lista *l, Mostrar mostrar, FILE *stream);

int eliminarUltimosNdeLaLista(Lista *l, int n);
int eliminarPrimeroDeLaLista(Lista *l, void *dato, unsigned tamDato);


// funciones puntero
int compararPorCodProd(const void * d1, const void * d2);
int compararPorCodSectorYproducto(const void *d1, const void * d2);

void acumularCompras(void *actualizado, const void * actualizador);
void acumularXsector(void *actualizado, const void *actualizador);

void mostrarCompras(void *dato, FILE *stream);
void mostrarSector(void *dato, FILE *stream);

// funciones generales
int crearLotePedidosTxt(const char * filename);
int parsearLinea(char * linea, Pedido *p);


int main()
{
    crearLotePedidosTxt("pedidos.txt");
    FILE *fpt = fopen("pedidos.txt","rt");
    if(!fpt)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE TEXTO EN LECTURA");
        return ERR_ARCHIVO;
    }
    Lista lc;
    Lista ls;

    crearLista(&lc);
    crearLista(&ls);

    Pedido p;
    Compra c;
    Sector s;

    char  linea[256];
    while(fgets(linea,256,fpt))
    {
        parsearLinea(linea,&p);
        // COMPRA
        strncpy(c.codProd,p.codProd,sizeof(c.codProd));
        c.cantPedida=p.cantPedida;

        // SECTOR
        strncpy(s.codProd,p.codProd,sizeof(s.codProd));
        s.codSector = p.codSector;
        s.cantProducto = p.cantPedida;
        s.cantPorSector=s.cantProducto;

        insertarEnListaOrdConAcum(&lc,&c,sizeof(Compra),compararPorCodProd,acumularCompras);

        insertarEnListaOrdConAcum(&ls,&s,sizeof(Sector),compararPorCodSectorYproducto,acumularXsector);



    }

    mostrarLista(&lc,mostrarCompras,stdout);
    puts("");
    mostrarLista(&ls,mostrarSector,stdout);

    puts("");
    int res =  eliminarUltimosNdeLaLista(&lc,1);
    printf("RES %d\n",res);
    mostrarLista(&lc,mostrarCompras,stdout);

    FILE * fpb = fopen("resultadoCompras.bin","wb");
    if(!fpb)
        return ERR_ARCHIVO;

    while(!listaVacia(&lc))
    {
        eliminarPrimeroDeLaLista(&lc,&c,sizeof(Compra));
        fwrite(&c,sizeof(Compra),1,fpb);
        mostrarCompras(&c,stdout);
    }

    vaciarLista(&lc);
    vaciarLista(&ls);
    fclose(fpt);
    fclose(fpb);
    return 0;
}

// FUNCIONES GENERALES

int crearLotePedidosTxt(const char * filename)
{
    int i;
    Pedido p[6]=
    {
        {
            1,"lapicera",100,'v',"Facturacion"
        },
        {
            2,"lapicera",30,'r',"Recursos Humanos"
        },
        {
            3, "hojas",25, 'v', "Tesoreria"
        },
        {
            4, "pantalla", 3, 'a', "Atencion Al Cliente"
        },
        {
            5, "lapicera", 5,'r', "Gerencia"
        },
        {
            6, "pantalla", 1,'v', "Recursos Humanos"
        }
    };
    FILE *fpt = fopen(filename, "wt");
    if(!fpt)
    {
        fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE TEXTO EN ESCRITURA");
        return ERR_ARCHIVO;
    }

    for (i=0; i<6 ; i++)
    {
        fprintf(fpt,"%d|%s|%d|%c|%s\n",p[i].nroPedido,p[i].codProd,p[i].cantPedida,p[i].codSector,p[i].oficina);
    }

    fclose(fpt);
    return TODO_OK;
}

int parsearLinea(char * linea, Pedido *p)
{
    char * act =strrchr(linea,'\n');
    if(*act != '\n')
    {
        return ERR_LINEA_LARGA;
    }


    // BUSCAMOS LA OFICINA
    *act = '\0';
    act = strrchr(linea,'|');
    strncpy(p->oficina,act+1,sizeof(p->oficina));

    // BUSCAMOS EL CODSECTOR
    *act ='\0';
    act = strrchr(linea,'|');
    p->codSector = *(act+1);

    // BUSCAMOS la cantPedida
    *act = '\0';
    act = strrchr(linea,'|');
    sscanf(act+1,"%d",&p->cantPedida);

    // BUSCAMOS EL codProd
    *act = '\0';
    act = strrchr(linea,'|');
    strncpy(p->codProd,act+1,sizeof(p->codProd));

    // BUSCAMOS EL nroPedido
    *act ='\0';
    sscanf(linea,"%d",&p->nroPedido);

    return TODO_OK;

}

// FUNCIONES LISTA

Nodo * crearNodo(void *dato, unsigned tamDato)
{
    Nodo * nue = (Nodo *)malloc(sizeof(Nodo));
    if(!nue||!(nue->dato= malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->sig= NULL;
    nue->ant = NULL;

    return nue;
}
void vaciarNodo(Nodo *nae, void * dato,unsigned tamDato)
{
    if(!nae)
        return;

    if(dato!= NULL)
        memcpy(dato,nae->dato,min(tamDato,nae->tamDato));

    free(nae->dato);
    free(nae);

}

void crearLista(Lista *l)
{
    *l = NULL;
}
int  vaciarLista(Lista *l)
{
    int cne=0;
    Nodo * act =*l;
    Nodo *nae;

    if(act)
    {
        while(act->ant)
            act =act->ant;

        while(act)
        {
            nae =act;
            act = nae->sig;

            free(nae->dato);
            free(nae);

            cne++;
        }

    }
    *l = NULL;

    return cne;

}

bool listaLlena(const Lista *l, unsigned tamDato)
{
    Nodo * nue = (Nodo *)malloc(sizeof(Nodo));
    void *dato = malloc(tamDato);
    free(nue);
    free(dato);

    return !nue || !dato;
}
bool listaVacia(const Lista *l)
{
    return *l == NULL;

}


int insertarEnListaOrdConAcum(Lista *l, const void *dato, unsigned tamDato, Cmp cmp, Actualizar actualizar)
{
    Nodo *nue =crearNodo((Nodo*)dato,tamDato);
    if(!nue)
        return ERR_NODO;

    Nodo *act = *l;
    Nodo *sig = NULL;
    Nodo *ant =NULL;

    if(act)
    {
        while (act->ant  && cmp(dato,act->dato)<0)
            act =act->ant;
        while (act->sig && cmp(dato,act->dato)>0)
            act =act->sig;

        int res = cmp(dato,act->dato);

        if(res ==  0 )
        {
            if(actualizar)
                actualizar(act->dato,dato);
            return REPETIDO;
        }

        if(res<0)
        {
            sig =act;
            ant =act->ant;
        }
        else
        {
            sig =act->sig;
            ant = act;
        }
    }

    nue->sig =sig;
    nue->ant =ant;

    if(sig)
        sig->ant = nue;

    if(ant)
        ant->sig = nue;
    *l  = nue;

    return TODO_OK;
}


void mostrarLista(const Lista *l, Mostrar mostrar, FILE *stream)
{
    if(!*l)
        return ;
    Nodo *act =*l;
    while(act->ant)
        act =act->ant;

    while(act)
    {
        mostrar(act->dato,stream);
        act =act->sig;
    }
}


int eliminarUltimosNdeLaLista(Lista *l, int n)
{
    if(!*l)
        return 1;

    Nodo *act = *l;
    Nodo *nae;
    while(act->sig)
        act =act->sig;

    int i=0;

    for (; i<n && act; i++ )
    {
        nae =act;
        act =nae->ant;


        if(act)
            act->sig =NULL;

        if(nae == *l)
            *l = nae->ant;


        free(nae->dato);
        free(nae);
    }

    i++;
    printf("i %d n %d \n",i,n);
    return i<=n?1:TODO_OK;
}

int eliminarPrimeroDeLaLista(Lista *l, void *dato, unsigned tamDato)
{
    if(!*l)
    {
           return ERR_NODO;
           puts("ALGO!");
    }


    Nodo * act =*l;
    while(act->ant)
        act = act->ant;

    Nodo *nae = act;
    act = nae->sig;

    if(act)
        act->ant =  NULL;


    if(nae == *l)
        *l =nae->sig;

    vaciarNodo(nae,dato,tamDato);
    return TODO_OK;
}


// FUNCIONES PUNTERO
int compararPorCodProd(const void * d1, const void * d2)
{
    Compra * c1 = (Compra *) d1;
    Compra *c2 = (Compra *)d2;

    return strcmp(c1->codProd,c2->codProd);
}
int compararPorCodSectorYproducto(const void *d1, const void * d2)
{
    Sector * s1 = (Sector *)d1;
    Sector *s2 = (Sector *)d2;

    if((s1->codSector - s2->codSector) == 0)
    {
        return strcmp(s1->codProd,s2->codProd);
    }

    return s1->codSector - s2->codSector;
}

void acumularCompras(void *actualizado, const void * actualizador)
{
    Compra * c1 = (Compra *) actualizado;
    Compra *c2 = (Compra *)actualizador;

    c1->cantPedida+=c2->cantPedida;
}
void acumularXsector(void *actualizado, const void *actualizador)
{
    Sector *  s1 =(Sector *)actualizado;
    Sector *s2 = (Sector *)actualizador;

    s1->cantPorSector+= s2->cantPorSector;
}


void mostrarCompras(void *dato, FILE *stream)
{
    Compra * c = (Compra *)dato;
    fprintf(stream,"c CodProd %-10s cantPedida %d\n",c->codProd,c->cantPedida);
}
void mostrarSector(void *dato, FILE *stream)
{
    Sector *s =(Sector *)dato;
    fprintf(stream,"s codSec %c codProd %-10s cantPedida %d cantSector %d\n",s->codSector,s->codProd,s->cantProducto,s->cantPorSector  );
}
