#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Descomentar lo que corresponda. Si Recupera parcial 1: TDA_LISTA_IMPL_DINAMICA. Si es parcial 2: TDA_LISTA_IMPL_DINAMICA_DOBLE.
#define TDA_LISTA_IMPL_DINAMICA
//#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDAlista.h"

#include "../SolucionAlumnos/SolucionAlumnos.h"
#include "../SolucionAlumnos/EstadoAlumnoMateria.h"

#define NOMBRE_ARCHIVO_NOTAS "Notas.dat"

#define MINIMO(a,b) ((a) < (b) ? (a) : (b))

void procesarLista_ALU(Lista* plAM);
int compararDniMateria(const void* dato1, const void* dato2);
int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar);
int compararNota(const void* dato1, const void* dato2);
void actualizarNotas(void* dato1, const void* dato2);
int eliminarDeListaDesordDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar);
int verPrimeroDeLista_ALU(const Lista* pl, void* dato, size_t tamDato);
void mostrarAlumno2(void * alum1);
Lista* buscarMenorDeLista_ALU(Lista* pl, Cmp cmp);
void accEstadoAlumno(void* dato1, void* dato2);
void ordenarLista_ALU(Lista *pl, Cmp cmp);
void recorrerLista_ALU(Lista* pl, Accion accion, void* datosAccion);
static char* enumStrings[] = {"PR","CU","RE","AU"};

int main()
{
	generarArchivo(NOMBRE_ARCHIVO_NOTAS);

	Lista listaAM;
	crearLista(&listaAM);

	cargarLista(&listaAM, NOMBRE_ARCHIVO_NOTAS);

	puts("Lista antes de procesar:");
	recorrerLista(&listaAM, mostrarEstadoAM, NULL);

    procesarLista_ALU(&listaAM);
 	//procesarLista(&listaAM);

	puts("\nLista despues de procesar:");
	recorrerLista_ALU(&listaAM, mostrarEstadoAM, NULL);

	return 0;
}


void procesarLista_ALU(Lista* plAM)
{
	/// Desarrolle esta función y todas las que invoque. Puede usar funciones de la biblioteca estándar.
	/// Coloque el sufijo _ALU a todas las funciones que desarrolle.
	/// No use ni modifique otro archivo que no sea
//	main.c. Será el que deberá entregar en formato comprimido con nombre "Apellido_Nombre_DNI.zip".
    ordenarLista_ALU(plAM, compararDniMateria);

    /*printf("\nLista despues de ordenar y antes de eliminar:\n");

    recorrerLista_ALU(plAM, mostrarEstadoAM, NULL);*/

    /*EstadoAlumnoMateria alumno;

    verPrimeroDeLista_ALU(plAM, &alumno, sizeof(EstadoAlumnoMateria));
    printf("\nprimer alumno %d\n", alumno.dni);*/

    //eliminarDeListaOrdDuplicados(plAM, compararDniMateria, actualizarNotas);
    eliminarDeListaOrdDuplicados_ALU(plAM, compararDniMateria, actualizarNotas);

   /* printf("\nLista despues de eliminar:\n");

    recorrerLista_ALU(plAM, mostrarEstadoAM, NULL);*/

    recorrerLista_ALU(plAM, accEstadoAlumno, NULL);

    /*printf("\nLista despues de actualizar los estados:\n");

    recorrerLista_ALU(plAM, mostrarEstadoAM, NULL);*/

    ordenarLista_ALU(plAM, compararNota);

   /* printf("\nLista despues de ordenar por nota final:\n");

    recorrerLista_ALU(plAM, mostrarEstadoAM, NULL);*/

}


Lista* buscarMenorDeLista_ALU(Lista* pl, Cmp cmp)
{
    Lista* plMenor = pl;
    Lista* plAct = &(*plMenor)->sig;

    while(*plAct)
    {
        if(cmp((*plAct)->elem, (*plMenor)->elem) < 0)
            plMenor = plAct;

        plAct = &(*plAct)->sig;
    }
    return plMenor;
}

void ordenarLista_ALU(Lista *pl, Cmp cmp)
{
    Lista lOrd;
    Lista* plUlt = &lOrd;
    Lista* plMenor;

    while(*pl)
    {
        plMenor = buscarMenorDeLista_ALU(pl, cmp);
        *plUlt = *plMenor;
        *plMenor = (*plMenor)->sig;
        plUlt = &(*plUlt)->sig;
    }
    *pl = lOrd;
}


int eliminarDeListaDesordDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar)
{
    if(*pl == NULL)
         return 1;

    Nodo* actual;
    Nodo* nae;
    Nodo* ant;

    while(*pl)
    {
        ant = *pl;
        actual = (*pl)->sig;
        while(actual)
        {
            if(cmp((*pl)->elem, actual->elem) == 0)
            {
                actualizar((*pl)->elem, actual->elem);
                nae = actual;
                actual = nae->sig;
                ant->sig = actual;
                free(nae->elem);
                free(nae);
            }
            else
            {
                ant = actual;
                actual = actual->sig;
            }
        }
        pl = &(*pl)->sig;
    }

    return TODO_OK;
}


int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar)
{
    if(*pl == NULL)
        return 1;

    Nodo* plDup;

    while(*pl)
    {
        plDup = (*pl)->sig;
        while(plDup && cmp((*pl)->elem, plDup->elem) == 0 )
        {
            actualizar((*pl)->elem, plDup->elem);
            Nodo* nae = plDup;
            plDup = nae->sig;
            free(nae->elem);
            free(nae);
        }
        (*pl)->sig = plDup;
        pl = &(*pl)->sig;
    }

    return TODO_OK;
}

void recorrerLista_ALU(Lista* pl, Accion accion, void* datosAccion)
{
    while(*pl)
    {
        accion((*pl)->elem, datosAccion);
        pl = &(*pl)->sig;
    }
}


void actualizarNotas(void* actualizado, const void* actualizador)
{
    EstadoAlumnoMateria* alum1 = (EstadoAlumnoMateria*)actualizado;
    EstadoAlumnoMateria* alum2 = (EstadoAlumnoMateria*)actualizador;

    if(alum2->notaP1 != 0)
        alum1->notaP1 = alum2->notaP1;

    if(alum2->notaP2 != 0)
        alum1->notaP2 = alum2->notaP2;

    if(alum2->notaR1 != 0)
        alum1->notaR1 = alum2->notaR1;

    if(alum2->notaR2 != 0)
        alum1->notaR2 = alum2->notaR2;
    /*
    int nota1 = alum1->notaP1 > alum1->notaR1 ? alum1->notaP1 : alum1->notaR1;
    int nota2 = alum1->notaP2 > alum1->notaR2 ? alum1->notaP2 : alum1->notaR2;

    if(nota1 >= 7 && nota2 >= 7)
    {
        alum1->condicion = PR;
    }
    else if(nota1 >= 4 && nota2 >= 4)
    {
        alum1->condicion = CU;
    }
    else if(nota1 != 0 && nota2 != 0)
    {
        alum1->condicion = RE;
    }
    else
    {
        alum1->condicion = AU;
    }

    alum1->notaFinal = (nota1 + nota2) / 2;
    float parteComa = (nota1 + nota2) / 2;
    alum1->notaFinal = parteComa > 0 ? alum1->notaFinal + 1 : alum1->notaFinal;*/
}

void accEstadoAlumno(void* dato1, void* dato2)
{
    EstadoAlumnoMateria* alum1 = (EstadoAlumnoMateria*)dato1;

    int nota1 = alum1->notaP1 > alum1->notaR1 ? alum1->notaP1 : alum1->notaR1;
    int nota2 = alum1->notaP2 > alum1->notaR2 ? alum1->notaP2 : alum1->notaR2;

    if(nota1 >= 7 && nota2 >= 7)
    {
        alum1->condicion = PR;
    }
    else if(nota1 >= 4 && nota2 >= 4)
    {
        alum1->condicion = CU;
    }
    else if(nota1 != 0 && nota2 != 0)
    {
        alum1->condicion = RE;
    }
    else
    {
        alum1->condicion = AU;
    }

    alum1->notaFinal = (nota1 + nota2) / 2;
    float parteComa = (nota1 + nota2) / 2;
    alum1->notaFinal = parteComa > 0 ? alum1->notaFinal + 1 : alum1->notaFinal;

}


int compararNota(const void* dato1, const void* dato2)
{
    EstadoAlumnoMateria* alum1 = (EstadoAlumnoMateria*)dato1;
    EstadoAlumnoMateria* alum2 = (EstadoAlumnoMateria*)dato2;

    return alum2->notaFinal - alum1->notaFinal;
}


int compararDniMateria(const void* dato1, const void* dato2)
{
    EstadoAlumnoMateria* alum1 = (EstadoAlumnoMateria*)dato1;
    EstadoAlumnoMateria* alum2 = (EstadoAlumnoMateria*)dato2;

    int cmp = alum1->dni - alum2->dni;

    if(cmp == 0)
        return strcmp(alum1->materia, alum2->materia);

    return cmp;
}

int verPrimeroDeLista_ALU(const Lista* pl, void* dato, size_t cantBytes)
{
    if(*pl == NULL)
        return 0;

    memcpy(dato, (*pl)->elem, MINIMO(cantBytes, (*pl)->tamElem));
    return 1;
}

void mostrarAlumno2(void * alum1)
{
    EstadoAlumnoMateria * alumno = (EstadoAlumnoMateria*)alum1;
    fprintf(stdout,"\n%d %s %s %d %d %d %d %s %d\n", alumno->dni,alumno->apyn,alumno->materia, alumno->notaP1, alumno->notaP2, alumno->notaR1, alumno->notaR2,enumStrings[alumno->condicion], alumno->notaFinal);
}
