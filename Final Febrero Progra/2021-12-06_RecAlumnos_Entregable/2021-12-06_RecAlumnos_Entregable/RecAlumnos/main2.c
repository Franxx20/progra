#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
/// Descomentar lo que corresponda. Si Recupera parcial 1: TDA_LISTA_IMPL_DINAMICA. Si es parcial 2: TDA_LISTA_IMPL_DINAMICA_DOBLE.
//#define TDA_LISTA_IMPL_DINAMICA
#define TDA_LISTA_IMPL_DINAMICA_DOBLE
//#include "../TDALista/TDAlista.h"

#include "../TDALista/TDALista.h"

#include "../SolucionAlumnos/SolucionAlumnos.h"

#include "../Matematica/Matematica.h"

#define NOMBRE_ARCHIVO_NOTAS "Notas.dat"



// FUNCIONES GENERALES

void procesarLista_ALU(Lista* plAM);
void procesarLista2_ALU(Lista *l);

// FUNCIONES LISTA
NodoD * crearNodoD_ALU(const void *dato, size_t tamDato);
booleano listaLlena_ALU(const Lista *l, size_t tamDato);
int insertarOActualizarEnListaOrd_ALU(Lista *l, const void * dato, size_t tamDato, Cmp cmp,Actualizar actualizar);
int eliminarDeListaPrimero_ALU(Lista *l, void * dato, size_t tamDato);
int ordenarLista_ALU(Lista *l,Cmp cmp);
int recorrerLista_ALU(Lista *l,Accion accion, void * datosAccion);
int vaciarLista_ALU(Lista *l);
int eliminarDeListaOrdDuplicados_ALU(Lista *l, Cmp cmp,Actualizar actualizar);

// FUNCIONES PUNTERO
int cmpAlumnos_ALU(const void * d1, const void * d2);
void actualizarNotasAlumnos_ALU(void *actualizado, const void * actualizador);
void actualizarCondicionAlumnos_ALU(void * dato, void * datosAccion);
int cmpNotas_ALU(const void * d1,const void * d2);

int main()
{
    generarArchivo(NOMBRE_ARCHIVO_NOTAS);

    Lista listaAM;
    crearLista(&listaAM);

    cargarLista(&listaAM, NOMBRE_ARCHIVO_NOTAS);

    puts("Lista antes de procesar:");
    recorrerLista(&listaAM, mostrarEstadoAM, NULL);

    procesarLista2_ALU(&listaAM);
    //procesarLista(&listaAM);

    puts("\nLista despues de procesar:");
    recorrerLista(&listaAM, mostrarEstadoAM, NULL);

    return 0;
}
// FUNCIONES GENERALES

void procesarLista_ALU(Lista* plAM)
{
    Lista listaAux;
    crearLista(&listaAux);

    EstadoAlumnoMateria eam;

    // eliminarDeListaPrimero_ALU(plAM,&eam,sizeof(EstadoAlumnoMateria));
    while(!listaVacia(plAM) && !listaLlena_ALU(&listaAux,sizeof(EstadoAlumnoMateria)))
    {
        eliminarDeListaPrimero_ALU(plAM,&eam,sizeof(EstadoAlumnoMateria));
        insertarOActualizarEnListaOrd_ALU(&listaAux,&eam,sizeof(EstadoAlumnoMateria),cmpAlumnos_ALU,actualizarNotasAlumnos_ALU);
    }

    // insertarOActualizarEnListaOrd_ALU(&listaAux,&eam,sizeof(EstadoAlumnoMateria),cmpAlumnos_ALU,actualizarNotasAlumnos_ALU);


    recorrerLista_ALU(&listaAux,actualizarCondicionAlumnos_ALU,NULL);




    eliminarDeListaPrimero_ALU(&listaAux,&eam,sizeof(EstadoAlumnoMateria));
    while(!listaVacia(&listaAux) && !listaLlena_ALU(plAM,sizeof(EstadoAlumnoMateria)))
    {
        insertarOActualizarEnListaOrd_ALU(plAM,&eam,sizeof(EstadoAlumnoMateria),cmpNotas_ALU,actualizarNotasAlumnos_ALU);
        eliminarDeListaPrimero_ALU(&listaAux,&eam,sizeof(EstadoAlumnoMateria));
    }
    //ordenarLista_ALU(plAM,cmpNotas_ALU);
    vaciarLista_ALU(&listaAux);
}
void procesarLista2_ALU(Lista *l)
{
    ordenarLista_ALU(l,cmpAlumnos_ALU);

    eliminarDeListaOrdDuplicados_ALU(l,cmpAlumnos_ALU,actualizarNotasAlumnos_ALU);

    recorrerLista_ALU(l,actualizarCondicionAlumnos_ALU,NULL);

    ordenarLista_ALU(l,cmpNotas_ALU);
}

// FUNCIONES LISTA

NodoD * crearNodoD_ALU(const void *dato, size_t tamDato)
{
    NodoD * nue = (NodoD *)calloc(1,sizeof(NodoD));
    if(!nue || !(nue->elem = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->elem,dato,tamDato);
    nue->tamElem = tamDato;
    nue->sig = NULL;
    nue->ant = NULL;

    return nue;
}

booleano listaLlena_ALU(const Lista *l, size_t tamDato)
{
    NodoD * nodo = (NodoD *)calloc(1,sizeof(NodoD));
    void * dato = calloc(1,tamDato);
    free(nodo);
    free(dato);

    return !nodo ||!dato;
}

int insertarOActualizarEnListaOrd_ALU(Lista *l, const void * dato, size_t tamDato, Cmp cmp,Actualizar actualizar)
{
    NodoD * nue = crearNodoD_ALU(dato,tamDato);
    NodoD * act = *l;
    NodoD * sig = NULL;
    NodoD * ant = NULL;
    int resultado;

    if(act)
    {
        while(act->ant && cmp(dato,act->elem) < 0 )
            act = act->ant;

        while(act->sig && cmp(dato,act->elem)>0)
            act =act->sig;

        resultado = cmp(dato,act->elem);
        if(resultado ==0)
        {
            if(actualizar)
                actualizar(act->elem,dato);
            return TODO_OK;

        }
        // si el dato insertar es menor al dato actual
        if(resultado <0)
        {
            sig = act;
            ant = act->ant;
        }
        else // el dato a  insertar es mayor al dato actual
        {
            sig = act->sig;
            ant = act;
        }
    }
    nue->sig = sig;
    nue->ant = ant;

    if(sig)
        sig->ant =nue;
    if(ant)
        ant->sig = nue;

    *l = nue;

    return TODO_OK;

}

int eliminarDeListaPrimero_ALU(Lista *l, void * dato, size_t tamDato)
{
    NodoD * act = *l;
    NodoD * nae;
    if(!act)
        return -1;

    while(act->ant)
        act =act->ant;

    nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;
    if(nae == *l)
        *l = nae->sig;

    memcpy(dato,nae->elem,min(tamDato,nae->tamElem));
    free(nae->elem);
    free(nae);

    return TODO_OK;
}

int recorrerLista_ALU(Lista *l,Accion accion, void * datosAccion)
{
    NodoD * act = *l;
    if(!act)
        return -1;

    while(act->ant)
        act =act->ant;

    while(act)
    {
        accion(act->elem,datosAccion);
        act = act->sig;
    }

    return TODO_OK;
}

int vaciarLista_ALU(Lista *l)
{
    NodoD * act =*l;
    NodoD * nae;
    int cne =0;

    if(!act)
        return cne;

    while(act)
    {
        nae = act;
        act = nae->sig;
        free(nae->elem);
        free(nae);
        cne++;
    }

    *l = NULL;
    return cne;

}

int eliminarDeListaOrdDuplicados_ALU(Lista *l, Cmp cmp,Actualizar actualizar)
{
    NodoD * act =*l;
    NodoD * nae ;
    NodoD * sig;
    int cne =0;

    if(!act)
        return -1;

    while(act->ant)
        act =act->ant;

    while(act)
    {
        sig =act->sig;

        while(sig && cmp(act->elem,sig->elem)==0)
        {
            nae =sig;
            sig = nae->sig;

            if(nae == *l)
                *l = nae->ant?nae->ant:nae->sig;

            if(nae->ant)
                nae->ant->sig = nae->sig;
            if(nae->sig)
                nae->sig->ant = nae->ant;

            if(actualizar)
                actualizar(act->elem,nae->elem);
            free(nae->elem);
            free(nae);
            cne++;
        }
        act =act->sig;
    }

    return cne;
}

int ordenarLista_ALU(Lista *l,Cmp cmp)
{
    int ordenado;
    NodoD * act  = *l;
    void * auxDato;
    size_t auxTam;

    if(!act)
        return -1;

    do
    {
        while(act->ant)
            act = act->ant;
        ordenado =0;

        while(act->sig)
        {
            // si el dato actual es mas grande que el dato siguiente;
            if(cmp(act->elem,act->sig->elem)>0)
            {
                auxDato = act->elem;
                auxTam = act->tamElem;
                act->elem = act->sig->elem;
                act->tamElem = act->sig->tamElem;

                act->sig->elem = auxDato;
                act->sig->tamElem = auxTam;
                ordenado =1;
            }
            act = act->sig;

        }
    }
    while (ordenado);



    return TODO_OK;
}

// FUNCIONES PUNTERO
int cmpAlumnos_ALU(const void * d1, const void * d2)
{
    EstadoAlumnoMateria * e1 =(EstadoAlumnoMateria * )d1;
    EstadoAlumnoMateria * e2 = (EstadoAlumnoMateria * )d2;


    if (strcmp(e1->apyn,e2->apyn)==0)
        return strcmp(e1->materia,e2->materia);

    return strcmp(e1->apyn,e2->apyn);
}
void actualizarNotasAlumnos_ALU(void *actualizado, const void * actualizador)
{
    EstadoAlumnoMateria * e1 =(EstadoAlumnoMateria*)actualizado;
    const EstadoAlumnoMateria * e2 = (const EstadoAlumnoMateria*)actualizador;

    if(e2->notaP1 > e1->notaP1)
        e1->notaP1 = e2->notaP1;
    if(e2->notaP2 > e1->notaP2)
        e1->notaP2 = e2->notaP2;
    if(e2->notaR1 > e1->notaR1)
        e1->notaR1 = e2->notaR1;
    if(e2->notaR2 > e1->notaR2)
        e1->notaR2 = e2->notaR2;
}
void actualizarCondicionAlumnos_ALU(void * dato, void * datosAccion)
{
    EstadoAlumnoMateria * e1 =(EstadoAlumnoMateria * )dato;
    //EstadoAlumnoMateria * e2 = (EstadoAlumnoMateria * )datosAccion;

    int mayor1=0,mayor2=0;
    double notaFinal;

    mayor1 = e1->notaP1> e1->notaR1?e1->notaP1:e1->notaR1;
    mayor2 = e1->notaP2> e1->notaR2?e1->notaP2:e1->notaR2;



    if(mayor1 >= 7 && mayor2 >=7)
    {
        e1->condicion = PR;
        notaFinal = ceil((double)(mayor1 + mayor2)/2);
        e1->notaFinal =notaFinal ;
    }

    else if(mayor1 >=4 && mayor2 >=4)

    {
        e1->condicion = CU;
        notaFinal = ceil((double)(mayor1 + mayor2)/2);
        e1->notaFinal = notaFinal;
    }
    else if((mayor1>0 && mayor1 <4) || (mayor2>0 && mayor2 <4))
    {
        e1->condicion = RE;
        e1->notaFinal =2;

    }

}

int cmpNotas_ALU(const void * d1,const void * d2)
{

    EstadoAlumnoMateria * e1 =(EstadoAlumnoMateria * )d1;
    EstadoAlumnoMateria * e2 = (EstadoAlumnoMateria * )d2;

    if(( e2->notaFinal - e1->notaFinal)==0)
        return strcmp(e2->apyn,e1->apyn);

    return e2->notaFinal - e1->notaFinal;
}

