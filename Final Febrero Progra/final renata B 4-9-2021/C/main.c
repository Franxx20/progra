#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

#define TODO_OK 0
#define ERR_ARCHIVO -1
#define ERR_NODO -2
#define ERR_GENERAL -3

typedef struct
{
    char Dominio[8];
    int antiguedad;
    int kmRecorridos;
} Vehiculo;

typedef struct
{
    int antiguedad;
    int kmRecorridos;
    int cantidad;
    int promedio;
} PromedioKm;

typedef int (*Cmp)(const void *d1,const void *d2);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);

typedef struct sNodo
{
    void * dato;
    size_t tamDato;
    struct sNodo * sig;
} Nodo;

typedef Nodo * Lista;

// FUNCIONES GENERALES
int crearLoteDePruebas(const char *nombreArchivo);
int cargarLista(const char * nombreArchivo, Lista *l);
int mostrarPromedios(Lista *l);

// FUNCIONES LISTA
Nodo * crearNodo(const void *dato, size_t tamDato);
void crearLista(Lista *l);
int vaciarLista(Lista *l);

int listaLlena(const Lista *l, size_t tamDato);
int listaVacia(const Lista *l);

int insertarEnListaOrdConACum(Lista *l, const void *dato, size_t tamDato,Cmp cmp,Actualizar actualizar);
int eliminarPrimeroDeLista(Lista *l, void * dato,size_t tamDato);



// FUNCIONES PUNTERO
int compararAntiguedad(const void *d1, const void * d2);
void acumularKm(void * actualizado, const void * actualizador);



int main()
{
    Lista listaPromedios;
    crearLista(&listaPromedios);
    int res;

    res = crearLoteDePruebas("vehiculos.dat");
    if(res != TODO_OK)
        return ERR_GENERAL;
    res =cargarLista("vehiculos.dat",&listaPromedios);
    if(res != TODO_OK)
        return ERR_GENERAL;

    res = mostrarPromedios(&listaPromedios);


    vaciarLista(&listaPromedios);

    return 0;
}

typedef Nodo * Lista;

// FUNCIONES GENERALES
int crearLoteDePruebas(const char *nombreArchivo)
{
    Vehiculo vehiculos[]=
    {
//        {
//            "AAA111",10,200
//        },
//        {
//            "BBB111",5,100
//        },
//        {
//            "AAA222",10,300
//        },
//        {
//            "CCC111",1,100
//        },
//        {
//            "DDD111",5,500
//        }
               {"AAA111", 10, 200},
        {"BBB111", 5, 100},
        {"AAA222", 10, 300},
        {"CCC111", 1, 100},
        {"DDD111", 5, 500},
    };

    FILE * fp = fopen(nombreArchivo,"wb");
    int i=0;
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    for (; i<sizeof(vehiculos)/sizeof(Vehiculo); i++ )
    {
        fwrite(&vehiculos[i],sizeof(Vehiculo),1,fp);
    }

    fclose(fp);
    return TODO_OK;
}
int cargarLista(const char * nombreArchivo, Lista *l)
{
    FILE * fp = fopen(nombreArchivo,"rb");
    PromedioKm promedioKm;
    Vehiculo vehiculo;
    if (!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    fread(&vehiculo,sizeof(Vehiculo),1,fp);
    while(!feof(fp))
    {
        promedioKm.cantidad = 1;
        promedioKm.kmRecorridos = vehiculo.kmRecorridos;
        promedioKm.antiguedad = vehiculo.antiguedad;
        promedioKm.promedio = promedioKm.kmRecorridos/promedioKm.cantidad;
        insertarEnListaOrdConACum(l,&promedioKm,sizeof(PromedioKm),compararAntiguedad,acumularKm);
        fread(&vehiculo,sizeof(Vehiculo),1,fp);
    }

    fclose(fp);

    return TODO_OK;
}
int mostrarPromedios(Lista *l)
{
    PromedioKm promedioKm;

    eliminarPrimeroDeLista(l,&promedioKm,sizeof(PromedioKm));
    fprintf(stdout,"%d %d\n",promedioKm.antiguedad,promedioKm.promedio);
    while(!listaVacia(l))
    {
        eliminarPrimeroDeLista(l,&promedioKm,sizeof(PromedioKm));
        fprintf(stdout,"%d %d\n",promedioKm.antiguedad,promedioKm.promedio);
    }

    return TODO_OK;
}

// FUNCIONES LISTA
Nodo * crearNodo(const void *dato, size_t tamDato)
{
    Nodo * nue = (Nodo *)calloc(1,sizeof(Nodo));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
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
    Nodo * act=*l;
    Nodo * nae;
    int cne=0;
    if(act)
    {
        while(act)
        {
            nae = act->sig;
            act =nae->sig;
            cne++;
            free(nae->dato);
            free(nae);

        }
        *l = NULL;
    }


    return cne;
}

int listaLlena(const Lista *l, size_t tamDato)
{
    Nodo * nodo = (Nodo *)calloc(1,sizeof(Nodo));
    void * dato = calloc(1,tamDato);
    free(nodo);
    free(dato);

    return !nodo||!dato;
}
int listaVacia(const Lista *l)
{
    return *l == NULL;
}

int insertarEnListaOrdConACum(Lista *l, const void *dato, size_t tamDato,Cmp cmp,Actualizar actualizar)
{
    Nodo * nue = crearNodo(dato,tamDato);

    if(!nue)
    {
        return ERR_NODO;
    }

    while(*l && cmp(dato,(*l)->dato)<0)
        l = &(*l)->sig;


    if(*l && cmp(dato,((*l)->dato))==0)
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
int eliminarPrimeroDeLista(Lista *l, void * dato,size_t tamDato)
{
    Nodo * nae;
    if(!*l)
        return ERR_NODO;

    nae = *l;
    *l = nae->sig;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);

    return TODO_OK;
}

// FUNCIONES PUNTERO
int compararAntiguedad(const void *d1, const void * d2)
{
    const PromedioKm * p1  =(const PromedioKm *)d1;
    const PromedioKm * p2 = (const PromedioKm * )d2;

    return -p1->antiguedad + p2->antiguedad;
}
void acumularKm(void * actualizado, const void * actualizador)
{
    PromedioKm * p1 = (PromedioKm * )actualizado;
    const PromedioKm * p2 = (const PromedioKm * )actualizador;

    p1->cantidad++;
    p1->kmRecorridos+=p2->kmRecorridos;
    p1->promedio = p1->kmRecorridos/p1->cantidad;
}
