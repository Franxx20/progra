#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define TODO_OK 0
#define ERR_ARCHIVO -1
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct
{
    char codPedido[6];
    char sector;
    int cant;
} Pedido;

typedef struct sNodo
{
    void * dato;
    size_t tamDato;
    struct sNodo * sig;
    struct sNodo * ant;
} NodoD;

typedef struct sNodoA
{
    void * dato;
    size_t tamDato;
    struct sNodoA * hIzq;
    struct sNodoA * hDer;
} NodoA;

typedef NodoA * Arbol;


typedef NodoD * Lista;

typedef int (*Cmp)(const void *d1, const void * d2);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);
typedef void (*Mostrar)(void * datos, FILE * stream);
typedef void (*MostrarA)(void * datos, FILE * stream,int nivel);

// FUNCIONES GENERALES
int cargarLoteDePruebas_ALU(const char * pathName);
int cargarLoteEnLista_ALU(const char * pathName, Lista *l);
int procesarArchivo_ALU(const char * pathName);
// FUNCIONES PUNTERO
int cmpPedido_ALU(const void * d1, const void * d2);
void actualizarPedido_ALU(void * actualizado, const void *actualizador);
void mostrarPedido_ALU(void * dato, FILE * stream);
void mostrarArbol_ALU(void *dato,FILE* stream,int nivel);


// FUNCIONES LISTA
NodoD * crearNodoD_ALU(void * dato, size_t tamDato);
void crearLista_ALU(Lista *l);
int vaciarLista_ALU(Lista *l);

int listaLlena_ALU(const Lista *l,size_t tamDato);
int listaVacia_ALU(const Lista *l);
int recorreLista_ALU(const Lista *l, Mostrar mostrar, FILE * fp);

int insertarEnListaOrd_ALU(Lista *l, const void * dato, size_t tamDato, Cmp cmp,Actualizar actualizar);
int insertarEnListaAlFinal_ALU(Lista *l, const void * dato, size_t tamDato);

int eliminarDuplicadosDeListaDes_ALU(Lista *l,Cmp cmp, Actualizar actualizar);

int eliminarPrimeroDeLista_ALU(Lista *l, void * dato, size_t tamDato);

// FUNCIONES ARBOL
NodoA* crearNodoA(const void * dato, size_t tamDato);

void crearArbol_ALU(Arbol *t);
int vaciarArbol_ALU(Arbol *t);

int insertarEnArbol_ALU(Arbol *t, void * dato, size_t tamDato,Cmp cmp,Actualizar actualizar);
int insertarEnArbolDesdeArchivoOrdenado_ALU(const char * nombreArchivo, Arbol *t, size_t tamDato, Cmp cmp,Actualizar actualizar);
int insertarEnArbolDesdeArchivoOrdenadoRec_ALU(Arbol *t, int li,int ls, FILE * fp, size_t tamDato, Cmp cmp,Actualizar actualizar);

int recorrerArbolPreOrdenPorNivel_ALU(const Arbol *t,MostrarA mostrar,int nivel);
int recorrerArbolPreOrdenPorNivelRec_ALU(const Arbol *t, MostrarA mostrar, int nivel,int nivelDeseado);


int main()
{
    FILE * fp = fopen("pedidos.txt", "wt");
    Lista listaPedidos;
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    crearLista_ALU(&listaPedidos);

    cargarLoteDePruebas_ALU("pedidos.dat");
    cargarLoteEnLista_ALU("pedidos.dat",&listaPedidos);
    puts("Lista sin actualizar");
    recorreLista_ALU(&listaPedidos,mostrarPedido_ALU,stdout);
    puts("Lista actualizada");
    eliminarDuplicadosDeListaDes_ALU(&listaPedidos,cmpPedido_ALU,actualizarPedido_ALU);
    recorreLista_ALU(&listaPedidos,mostrarPedido_ALU,stdout);
    recorreLista_ALU(&listaPedidos,mostrarPedido_ALU,fp);


    vaciarLista_ALU(&listaPedidos);
    puts("ARBOLES");
    procesarArchivo_ALU("pedidos.dat");



    fclose(fp);
    return 0;
}


// FUNCIONES GENERALES
int cargarLoteDePruebas_ALU(const char * pathName)
{
    FILE *fp = fopen(pathName,"wb");
    int i;
    Pedido pedidos[]=
    {
        {
            "zana",'z',10
        },
        {
            "pera",'p',15
        },
        {
            "zana", 'z',40
        },
        {
            "manza",'m',5
        },
        {
            "bana",'b',100
        },
        {
            "zana", 'z',30
        },
        {
            "manza", 'm', 5
        },
        {
            "pera",'p',30
        },
        {
            "bana",'b',15
        }
    };
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    for (i=0; i< sizeof(pedidos)/sizeof(Pedido); i++)
    {
        fwrite(&pedidos[i],sizeof(Pedido),1,fp);
        fprintf(stdout, "%s|%c|%d\n",pedidos[i].codPedido,pedidos[i].sector,pedidos[i].cant);
    }

    fclose(fp);
    return TODO_OK;
}
int cargarLoteEnLista_ALU(const char * pathName, Lista *l)
{

    Pedido pedido;

    FILE * fp = fopen(pathName,"rb");
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    fread(&pedido,sizeof(Pedido),1,fp);
    while(!feof(fp) && !listaLlena_ALU(l,sizeof(Pedido)))
    {
        //insertarEnListaOrd_ALU(l,&pedido,sizeof(Pedido),cmpPedido_ALU,actualizarPedido_ALU);
        insertarEnListaAlFinal_ALU(l,&pedido,sizeof(pedido));
        fread(&pedido,sizeof(Pedido),1,fp);
    }
//    if(listaVacia_ALU(l))
//        insertarEnListaOrd_ALU(l,&pedido,sizeof(Pedido),cmpPedido_ALU,actualizarPedido_ALU);
    if(listaVacia_ALU(l))
        insertarEnListaAlFinal_ALU(l,&pedido,sizeof(Pedido));
    fclose(fp);
    return TODO_OK;

}

int procesarArchivo_ALU(const char * pathName)
{

    Pedido pedido;

    FILE * fp = fopen(pathName,"rb");
    FILE * fpAux = fopen("temp.dat", "wb");
    Lista listaAux;
    Arbol arbolPedidos;
    crearArbol_ALU(&arbolPedidos);
    crearLista_ALU(&listaAux);
    if(!fp || !fpAux)
    {
        fclose(fp);
        fclose(fpAux);
        return ERR_ARCHIVO;
    }
    while(!feof(fp))
    {
        fread(&pedido,sizeof(Pedido),1,fp);
        insertarEnListaOrd_ALU(&listaAux,&pedido,sizeof(Pedido),cmpPedido_ALU,actualizarPedido_ALU);
    }

    while(!listaVacia_ALU(&listaAux))
    {
        eliminarPrimeroDeLista_ALU(&listaAux,&pedido,sizeof(Pedido));
        fwrite(&pedido,sizeof(Pedido),1,fpAux);

    }

    fclose(fp);
    fclose(fpAux);
    remove(pathName);
    rename("temp.dat",pathName);

    insertarEnArbolDesdeArchivoOrdenado_ALU(pathName,&arbolPedidos,sizeof(Pedido),cmpPedido_ALU,actualizarPedido_ALU);

//    recorrerArbolPreOrdenPorNivel_ALU(&arbolPedidos,mostrarArbol_ALU,2);
    recorrerArbolPreOrdenPorNivel_ALU(&arbolPedidos,mostrarArbol_ALU,0);
//    recorrerArbolPreOrdenPorNivel_ALU(&arbolPedidos,mostrarArbol_ALU,1);

    vaciarArbol_ALU(&arbolPedidos);
    vaciarLista_ALU(&listaAux);
    return TODO_OK;
}

// FUNCIONES PUNTERO
int cmpPedido_ALU(const void * d1, const void * d2)
{
    const Pedido * p1 =(const Pedido *)d1;
    const Pedido * p2 =(const Pedido * )d2;

    return strcmp(p1->codPedido,p2->codPedido);

}
void actualizarPedido_ALU(void * actualizado, const void *actualizador)
{
    Pedido * p1 =(Pedido *)actualizado;
    const Pedido * p2 = (const Pedido *)actualizador;

    p1->cant += p2->cant;

}
void mostrarPedido_ALU(void * dato, FILE * stream)
{
    Pedido * p = (Pedido *)dato;
    fprintf(stream, "%s|%c|%d\n",p->codPedido,p->sector,p->cant);

}

void mostrarArbol_ALU(void *dato,FILE* stream,int nivel)
{
    int i=0;
    Pedido * p = (Pedido *)dato;
    for (; i<nivel ; i++ )
    {
        fprintf(stream,"\t");
    }
    fprintf(stream, "%s|%c|%d\n",p->codPedido,p->sector,p->cant);
}

// FUNCIONES LISTA
NodoD * crearNodoD_ALU(void * dato, size_t tamDato)
{
    NodoD * nue =(NodoD * )calloc(1,sizeof(NodoD));
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
    *l = NULL;
}
int vaciarLista_ALU(Lista *l)
{
    NodoD * act =*l;
    NodoD * nae;
    int cne =0;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        while(act)
        {
            nae =act;
            act =nae->sig;

            cne++;
            free(nae->dato);
            free(nae);
        }
        *l = NULL;
    }
    return cne;
}

int listaLlena_ALU(const Lista *l,size_t tamDato)
{
    NodoD * nodo=(NodoD *)calloc(1,sizeof(NodoD));
    void * dato = calloc(1,tamDato);

    free(dato);
    free(nodo);

    return !nodo|| !dato;
}
int listaVacia_ALU(const Lista *l)
{

    return *l == NULL;
}
int recorreLista_ALU(const Lista *l, Mostrar mostrar, FILE * fp)
{
    NodoD * act = *l;
    if(!act)
        return -1;

    while(act->ant)
        act =act->ant;

    while(act)
    {
        mostrar(act->dato,fp);
        act =act->sig;
    }

    return TODO_OK;
}

int insertarEnListaOrd_ALU(Lista *l, const void * dato, size_t tamDato, Cmp cmp,Actualizar actualizar)
{
    NodoD * act =*l;
    NodoD * nue = crearNodoD_ALU((NodoD*)dato,tamDato);
    NodoD * sig = NULL;
    NodoD * ant = NULL;

    int resultado;
    if(act)
    {
        while(act->ant && cmp(dato,act->dato)<0)
            act =act->ant;

        while(act->sig && cmp(dato,act->dato) >0)
            act = act->sig;

        resultado = cmp(dato,act->dato);

        if(resultado == 0)
        {
            if(actualizar)
            {
                actualizar(act->dato,dato);

                return TODO_OK;
            }
        }
        // si el dato a insertar es menor al dato actual
        if(resultado <0)
        {
            sig = act;
            ant = act->ant;
        }
        else // si el dato a insertar es mayor al dato actual
        {
            sig =act->sig;
            ant =act;
        }
    }
    nue->sig = sig;
    nue->ant =ant;

    if(sig)
        sig->ant = nue;
    if(ant)
        ant->sig =nue;

    *l =nue;


    return TODO_OK;
}

int insertarEnListaAlFinal_ALU(Lista *l, const void * dato, size_t tamDato)
{
    NodoD * act =*l;
    NodoD  * nue =crearNodoD_ALU((NodoD*)dato,tamDato);
    if(!nue)    return -1;


    if(act)
    {
        while(act->sig)
            act =act->sig;

        act->sig = nue;
        nue->ant =act;
    }

    *l = nue;


    return TODO_OK;
}

int eliminarDuplicadosDeListaDes_ALU(Lista *l,Cmp cmp, Actualizar actualizar)
{
    NodoD * act =*l;
    NodoD * sig;
    NodoD * nae;
    int cne= 0;

    if(!act)
        return cne=-1;


    // te pone al inicio de la lista

    while(act->ant)
        act =act->ant;


    while(act)
    {
        sig =act->sig;
        while(sig)
        {
            if(cmp(act->dato,sig->dato)==0)
            {
                if(actualizar)
                    actualizar(act->dato,sig->dato);
                cne++;
                nae = sig;
                sig = nae->sig;

                if(nae == *l)
                    *l = nae->ant?nae->ant:nae->sig;

                if(nae->ant)
                    nae->ant->sig = nae->sig;
                if(nae->sig)
                    nae->sig->ant = nae->ant;

                free(nae->dato);
                free(nae);

            }
            else
            {
                sig =sig->sig;
            }
        }
        act =act->sig;

    }

    return cne;
}

int eliminarPrimeroDeLista_ALU(Lista *l, void * dato, size_t tamDato)
{
    NodoD * act = *l;
    NodoD * nae;

    if(!act)
        return -1;

    while(act->ant)
        act= act->ant;

    nae =act;
    act = nae->sig;

    if(act)
        act->ant = NULL;
    if(nae ==*l)
        *l =nae->sig;

    memcpy(dato,nae->dato,MIN(nae->tamDato,tamDato));
    free(nae->dato);
    free(nae);

    return TODO_OK;
}


// FUNCIONES ARBOL
NodoA* crearNodoA(const void * dato, size_t tamDato)
{

    NodoA * nue =(NodoA * )calloc(1,sizeof(NodoA));
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
int vaciarArbol_ALU(Arbol *t)
{
    int cne =0;
    if(!*t)
        return cne;


    cne+= vaciarArbol_ALU(&(*t)->hIzq);
    cne+= vaciarArbol_ALU(&(*t)->hDer);
    return cne+1;

}

int insertarEnArbol_ALU(Arbol *t, void * dato, size_t tamDato,Cmp cmp,Actualizar actualizar)
{
    int resultado;
    if(!*t)
    {
        *t = crearNodoA(dato,tamDato);
        if(!*t)
        {
            return -1;
        }
        return TODO_OK;
    }
    resultado = cmp(dato,(*t)->dato);
    if(resultado ==0)
    {
        if(actualizar)
            actualizar((*t)->dato,dato);
    }

    return insertarEnArbol_ALU(resultado<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp,actualizar);

}
int insertarEnArbolDesdeArchivoOrdenado_ALU(const char * nombreArchivo, Arbol *t, size_t tamDato, Cmp cmp,Actualizar actualizar)
{
    int cantBytes;
    int cantReg;
    FILE * fp = fopen(nombreArchivo,"rb" );
    if(!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    fseek(fp,0L,SEEK_END);
    cantBytes = ftell(fp);
    cantReg= cantBytes/tamDato;


    insertarEnArbolDesdeArchivoOrdenadoRec_ALU(t,0,cantReg-1,fp,tamDato,cmp,actualizar);
    fclose(fp);

    return TODO_OK;
}
int insertarEnArbolDesdeArchivoOrdenadoRec_ALU(Arbol *t, int li,int ls, FILE * fp, size_t tamDato, Cmp cmp,Actualizar actualizar)
{
    void * dato = calloc(1,tamDato);
    int mitad;
    if(!dato)
    {
        free(dato);
        return -1;
    }
    if(li > ls)
        return -1;

    mitad =(li + ls)/2;
    fseek(fp,(long)mitad*tamDato,SEEK_SET);
    fread(dato,tamDato,1,fp);
    insertarEnArbol_ALU(t,dato,tamDato,cmp,actualizar);

    insertarEnArbolDesdeArchivoOrdenadoRec_ALU(t,li,mitad-1,fp,tamDato,cmp,actualizar);
    insertarEnArbolDesdeArchivoOrdenadoRec_ALU(t,mitad+1,ls,fp,tamDato,cmp,actualizar);

    free(dato);
    return TODO_OK;
}

int recorrerArbolPreOrdenPorNivel_ALU(const Arbol *t,MostrarA mostrar,int nivel)
{
    if(!*t)
        return -1;

    recorrerArbolPreOrdenPorNivelRec_ALU(t,mostrar,0,nivel);

    return TODO_OK;
}

int recorrerArbolPreOrdenPorNivelRec_ALU(const Arbol *t, MostrarA mostrar, int nivel,int nivelDeseado)
{
    if(!*t)
        return -1;

    recorrerArbolPreOrdenPorNivelRec_ALU(&(*t)->hIzq,mostrar,nivel+1,nivelDeseado);
    if(nivel == nivelDeseado  )
        mostrar((*t)->dato,stdout,nivel);
    recorrerArbolPreOrdenPorNivelRec_ALU(&(*t)->hDer,mostrar,nivel+1,nivelDeseado);

    return TODO_OK;
}
