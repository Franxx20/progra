#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(X)	((X) < 0? (X) * -1 : (X))

typedef struct
{
    char vehiculo[20];
    int antiguedad;
    float km;
} Vehiculo;

typedef struct
{
    int antiguedad;
    float promedio;
    int cantVehiculos;
    float kmTotalesRecorridos;
} Promedio;

typedef int (*Cmp) (const void * d1, const void *d2);
typedef void (*Actualizar) (void *actualizado, const void *actualizador);
typedef void (*Mostrar)(const void *dato, FILE *stream);

bool crearLote(const char * filename);
bool solucion(const char * filename);



/* LISTA SIMPLE */
typedef struct sNodo
{
    void * dato;
    unsigned tamDato;
    struct sNodo * sig;
}
Nodo;

typedef Nodo *  Lista;

Nodo * crearNodo(void * dato, unsigned tamDato);
void vaciarNodo(Nodo * nae,  void * dato, unsigned tamDato);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

bool listaLlena(const Lista *l, unsigned tamDato);
bool listaVacia(const Lista *l);

bool insertarEnListaOrdConAcum(Lista *l, void * dato, unsigned tamDato, Cmp cmp, Actualizar actualizado);
bool eliminarPrimeroDeLista(Lista *l, void * dato, unsigned tamDato);

void mostrarLista( const Lista *l,Mostrar mostrar);
// FIN LISTA SIMPLE

// FUNCIONES GENERALES
int compararAntiguedad(const void * auto1, const void *auto2);
void promediarVehiculos(void * actualizado, const void * actualizador);

void mostrarPromedio(const void *dato, FILE *stream);

int main()
{
    const char *archivo = "vehiculos.dat";
    crearLote(archivo);
    solucion(archivo);

    return 0;
}



bool crearLote(const char * filename)
{
    int i;
    FILE * fp = fopen(filename,"wb");
    if(!fp)
    {
        fprintf(stderr,"ERROR  EN LA CREACION DEL LOTE DE PRUEBA");
        return false;
    }
    Vehiculo v [6]= { {"AAA111",10,200},{"BBB111",5,100}, { "AAA222",10,300},{"CCC111",1,100}, {"DDD111",5,500},{"EEE111",30,-222} } ;

    for ( i=0; i<(sizeof(v)/sizeof(v[0])) ; i++ )
    {
        fwrite(&v[i],sizeof(Vehiculo),1,fp);
    }

    fclose(fp);
    return true;
}

bool solucion(const char * filename)
{
    FILE * fp = fopen(filename,"rb");
    Vehiculo v;
    Promedio p;
    Lista l;


    if(!fp )
    {
        fprintf(stderr,"ERROR EN LA APERTURA DE ARCHIVO EN SOLUCION");
        return false;
    }

    crearLista(&l);

    fread(&v,sizeof(Vehiculo),1,fp);
    while (!feof(fp))
    {
        p.antiguedad = v.antiguedad;
        p.cantVehiculos =1;
        p.kmTotalesRecorridos = v.km;
        p.promedio = ABS(p.kmTotalesRecorridos);

        insertarEnListaOrdConAcum(&l,&p,sizeof(Promedio),compararAntiguedad,promediarVehiculos);
        fread(&v,sizeof(Vehiculo),1,fp);
    }
    fclose(fp);


    mostrarLista(&l,mostrarPromedio);
    vaciarLista(&l);
    return true;
}

// LISTA SIMPLE

Nodo * crearNodo(void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
    // Nodo * nue = (Nodo*)calloc();
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;

    return nue;

}
void vaciarNodo(Nodo * nae,  void * dato, unsigned tamDato)
{
    if(!nae)
        return ;

    if(dato != NULL)
        memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));

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

    Nodo * nae ;

    if(!*l)
        return ;


    while(act)
    {
        nae = act;
        act = nae->sig;

        free(nae->dato);
        free(nae);

    }

    *l = NULL;

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


bool insertarEnListaOrdConAcum(Lista *l, void * dato, unsigned tamDato, Cmp cmp, Actualizar actualizar)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;

    while((*l) && cmp(dato,(*l)->dato) >0)
        l = &(*l)->sig;



    if( (*l) && cmp(dato,(*l)->dato) ==0 )
    {
        if(actualizar != NULL)
        {
            actualizar((*l)->dato, dato);
            free(nue->dato);
            free(nue);
            return true;
        }

    }


    nue->sig = *l;
    *l = nue;


    return true;
}


void mostrarLista( const Lista *l,Mostrar mostrar)
{
    if(!*l)
        return ;

    while((*l))
    {
        mostrar((*l)->dato,stdout);
        l = &(*l)->sig;
    }

}


// FUNCIONES GENERALES
int compararAntiguedad(const void * prom1, const void *prom2)
{
    const Promedio * p1 =(const Promedio * )prom1;
    const Promedio * p2 = (const Promedio * )prom2;

    return p1->antiguedad - p2->antiguedad;
}

void promediarVehiculos(void * actualizado, const void * actualizador)
{
    Promedio * p = (Promedio *)actualizado;
    Promedio * pa =(Promedio * )actualizador;

    p->cantVehiculos+=1;
    p->kmTotalesRecorridos+=ABS(pa->kmTotalesRecorridos);
    p->promedio = p->kmTotalesRecorridos/p->cantVehiculos;

}

void mostrarPromedio(const void *dato, FILE *stream)
{
    Promedio *prom = (Promedio *)dato;
    fprintf(stream, "%d\t%.2f\n", prom->antiguedad, prom->promedio);
}
