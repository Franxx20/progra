#include <stdio.h>
#include <stdlib.h>

/// Descomentar lo que corresponda. Si Recupera parcial 1: TDA_LISTA_IMPL_DINAMICA. Si es parcial 2: TDA_LISTA_IMPL_DINAMICA_DOBLE.
#define TDA_LISTA_IMPL_DINAMICA
//#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDAlista.h"

#include "../SolucionAlumnos/SolucionAlumnos.h"
#include "../SolucionAlumnos/EstadoAlumnoMateria.h"
#include "../SolucionAlumnos/Nota.h"

#define NOMBRE_ARCHIVO_NOTAS "Notas.dat"

#include <string.h>

int eliminarDeListaDesordDuplicados_ALU(Lista *pl, Cmp cmp, Actualizar actualizar);
int eliminarDeListaOrdDuplicados_ALU(Lista *pl, Cmp cmp, Actualizar actualizar);
void ordenarLista_ALU(Lista* pl, Cmp cmp);
void recorrerLista_ALU(Lista* pl, Accion accion, void* datosAccion);
void procesarLista_ALU(Lista* plAM);
int ingresarNodoPri(Lista* pl, void* elem, unsigned tamElem);
int compararDNIYMateria(const void* alum1, const void* alum2);
void actualizarNotas(void* alum1, const void* alum2);
int compararNotas(const void* alum1, const void* alum2);

int main()
{
    generarArchivo(NOMBRE_ARCHIVO_NOTAS);

    Lista listaAM;
    crearLista(&listaAM);

    cargarLista(&listaAM, NOMBRE_ARCHIVO_NOTAS);

    puts("Lista antes de procesar:");
    recorrerLista(&listaAM, mostrarEstadoAM, NULL);

    procesarLista_ALU(&listaAM);
//    procesarLista(&listaAM);

    puts("\nLista despues de procesar:");
    recorrerLista_ALU(&listaAM, mostrarEstadoAM, NULL);

    return 0;
}

int ingresarNodoPri(Lista* pl, void* elem, unsigned tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));
    void* elemento = malloc(tamElem);

    if(!nue || !elemento)
    {
        free(nue);
        free(elemento);
        return -1;
    }

    memcpy(nue->elem,elem,tamElem);
    nue->tamElem = tamElem;

    if(!*pl)
    {
        *pl = nue;
        nue->sig = NULL;
    }
    else
    {
        nue->sig = (*pl);
        (*pl) = nue;
    }

    return TODO_OK;
}

void procesarLista_ALU(Lista* plAM)
{
    /// Desarrolle esta función y todas las que invoque. Puede usar funciones de la biblioteca estándar.
    /// Coloque el sufijo _ALU a todas las funciones que desarrolle.
    /// No use ni modifique otro archivo que no sea main.c. Será el que deberá entregar en formato comprimido con nombre "Apellido_Nombre_DNI.zip".

///    EstadoAlumnoMateria regAlumno;

///    ordenarLista_ALU(plAM,compararDNIYMateria);

    eliminarDeListaDesordDuplicados_ALU(plAM,compararDNIYMateria,actualizarNotas);

///    eliminarDeListaOrdDuplicados_ALU(plAM,compararDNIYMateria,actualizarNotas);

    ordenarLista_ALU(plAM,compararNotas);

///    eliminarDeListaDesordDuplicados(plAM,compararDNIYMateria,actualizarNotas);

///    ordenarLista(plAM,compararNotas);
}

void recorrerLista_ALU(Lista* pl, Accion accion, void* datosAccion)
{
    while(*pl)
    {
        accion((*pl)->elem,datosAccion);
        pl = &(*pl)->sig;
    }
}

void ordenarLista_ALU(Lista* pl, Cmp cmp)
{
    Lista lOrd = NULL;
    Lista* plOrd;
    Nodo* nodo;

    while(*pl)
    {
        nodo = *pl;
        *pl = nodo->sig;

        plOrd = &lOrd;
        while(*plOrd && cmp(nodo->elem, (*plOrd)->elem) > 0)
            plOrd = &(*plOrd)->sig;

        nodo->sig = *plOrd;
        *plOrd = nodo;
    }

    *pl = lOrd;
}

int eliminarDeListaOrdDuplicados_ALU(Lista *pl, Cmp cmp, Actualizar actualizar)
{
    if(!*pl)
        return 1;

    Nodo* nod;

    while(*pl)
    {
        nod =(*pl)->sig;

        while(nod && cmp((*pl)->elem,nod->elem) == 0)
        {
            actualizar((*pl)->elem,nod->elem);
            Nodo* nae = nod;
            nod = nae->sig;
            free(nae->elem);
            free(nae);
        }
        (*pl)->sig = nod;
        pl = &(*pl)->sig;
    }
    return TODO_OK;
}

int eliminarDeListaDesordDuplicados_ALU(Lista *pl, Cmp cmp, Actualizar actualizar)
{
    if(!*pl)
        return 0;

    while(*pl)
    {
        Nodo* act = (*pl)->sig;
        Nodo* ant = (*pl);
        while(act)
        {
            if(cmp((*pl)->elem,act->elem) == 0)
            {
                actualizar((*pl)->elem,act->elem);
                Nodo* nae = act;
                act = act->sig;
                free(nae->elem);
                free(nae);
                ant->sig = act;
            }
            else
            {
                ant = ant->sig;
                act = act->sig;
            }
        }

        pl = &(*pl)->sig;
    }

    return TODO_OK;
}

int compararDNIYMateria(const void* alum1, const void* alum2)
{
    EstadoAlumnoMateria *alumno1 = (EstadoAlumnoMateria*) alum1;
    EstadoAlumnoMateria *alumno2 = (EstadoAlumnoMateria*) alum2;

    if((alumno1->dni- alumno2->dni) == 0)
        return strcmp(alumno1->materia,alumno2->materia);
    else
        return alumno1->dni-alumno2->dni;
}

void actualizarNotas(void* alum1, const void* alum2)
{
    EstadoAlumnoMateria *alumno1 = (EstadoAlumnoMateria*) alum1;
    EstadoAlumnoMateria *alumno2 = (EstadoAlumnoMateria*) alum2;

    if(alumno1->notaP1 == 0)
        alumno1->notaP1 = alumno2->notaP1;
    if(alumno1->notaP2 == 0)
        alumno1->notaP2 = alumno2->notaP2;
    if(alumno1->notaR1 == 0)
        alumno1->notaR1 = alumno2->notaR1;
    if(alumno1->notaR2 == 0)
        alumno1->notaR2 = alumno2->notaR2;

    int nota1 = alumno1->notaP1 >= alumno1->notaR1? alumno1->notaP1 : alumno1->notaR1;
    int nota2 = alumno1->notaP2 >= alumno1->notaR2? alumno1->notaP2 : alumno1->notaR2;

    if(nota1 >= 7 && nota2 >= 7)
    {
        alumno1->condicion = PR;
        alumno1->notaFinal = (nota1+nota2)/2;
    }
    if(nota1 >= 4 && nota2>=4)
    {
        alumno1->condicion = CU;
        alumno1->notaFinal = (nota1+nota2)/2;
        if(alumno1->notaFinal >= 7)
            alumno1->notaFinal = nota1 >= nota2 ? nota1 : nota2;
    }
    if(nota1 == 0 || nota2 == 0)
    {
        alumno1->condicion = AU;
        alumno1->notaFinal = 0;
    }
    if(nota1<4 || nota2<4)
    {
        alumno1->condicion = RE;
        alumno1->notaFinal = 2;
    }
}

int compararNotas(const void* alum1, const void* alum2)
{
    EstadoAlumnoMateria *alumno1 = (EstadoAlumnoMateria*) alum1;
    EstadoAlumnoMateria *alumno2 = (EstadoAlumnoMateria*) alum2;

    return alumno2->notaFinal - alumno1->notaFinal;
}
