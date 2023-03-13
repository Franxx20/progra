#include <stdio.h>
#include <stdlib.h>

/// Descomentar lo que corresponda. Si Recupera parcial 1: TDA_LISTA_IMPL_DINAMICA. Si es parcial 2: TDA_LISTA_IMPL_DINAMICA_DOBLE.
#define TDA_LISTA_IMPL_DINAMICA
//define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDAlista.h"

#include "../SolucionAlumnos/SolucionAlumnos.h"
#include"../SolucionAlumnos/EstadoAlumnoMateria.h"
#define NOMBRE_ARCHIVO_NOTAS "Notas.dat"

#include<string.h>
#include<stdlib.h>

static char* enumStrings[] =
{
    "PR", "CU",

    "RE", "AU"
};

int compararDniMateria(const void *alum1, const void *alum2);
int cmpDniYMateria_ALU( const void* first, const void* second );

int compararNotaFinal(const void *alumn1, const void *alum2);
int actualizarYeliminarListaDes_AlU(Lista *pl, Cmp cmp, Actualizar actualizar);

int eliminarDeListaDesordDuplicados_ALU(Lista *l, Cmp cmp, Actualizar actualizar);
int eliminarDeListaOrdDuplicados_ALU(Lista *l, Cmp cmp, Actualizar actualizar);

void ordenarALU( Lista *l, Cmp cmp);

void acumularNotas(void * alum1, const void * alum2);
void mostrarAlumno(void * alum1, void* alum2);
void mostrarAlumno2(void*alum1);
Nodo * buscarNodo_Alu(Lista *l,void * elem, Cmp cmp);

void procesarLista_ALU(Lista* plAM);
int main()
{
    generarArchivo(NOMBRE_ARCHIVO_NOTAS);

    Lista listaAM;
    crearLista(&listaAM);

    cargarLista(&listaAM, NOMBRE_ARCHIVO_NOTAS);

    puts("Lista antes de procesar:");
    recorrerLista(&listaAM, mostrarEstadoAM, NULL);

    procesarLista_ALU(&listaAM);
    //  procesarLista(&listaAM);

    puts("\nLista despues de procesar:");
    recorrerLista(&listaAM, mostrarEstadoAM, NULL);

    return 0;
}


void procesarLista_ALU(Lista* plAM)
{
    /// Desarrolle esta función y todas las que invoque. Puede usar funciones de la biblioteca estándar.
    /// Coloque el sufijo _ALU a todas las funciones que desarrolle.
    /// No use ni modifique otro archivo que no sea main.c. Será el que deberá entregar en formato comprimido con nombre "Apellido_Nombre_DNI.zip".

    ordenarLista(plAM,cmpDniYMateria_ALU);
    //ordenarALU(plAM, compararDniMateria);
    eliminarDeListaOrdDuplicados_ALU(plAM,compararDniMateria,acumularNotas);
    // eliminarDeListaOrdDuplicados(plAM,cmpDniYMateria_ALU,acumularNotas);

    //ordenarLista(plAM,compararNotaFinal);

}

int compararDniMateria(const void *alum1, const void *alum2)
{
    EstadoAlumnoMateria * alumno1 = (EstadoAlumnoMateria*)alum1;
    EstadoAlumnoMateria * alumno2 = (EstadoAlumnoMateria*)alum2;

    int cmp = alumno1->dni - alumno2->dni;

    if(cmp == 0)
        return strcmp(alumno1->materia, alumno2->materia);

    return cmp;
}

int compararNotaFinal(const void *alum1, const void *alum2)
{
    EstadoAlumnoMateria * alumno1 = (EstadoAlumnoMateria*)alum1;
    EstadoAlumnoMateria * alumno2 = (EstadoAlumnoMateria*)alum2;

    return alumno1->notaFinal - alumno2->notaFinal;
}

void mostrarAlumno(void * alum1, void* alum2)
{
    EstadoAlumnoMateria * alumno1 = (EstadoAlumnoMateria*)alum1;
    EstadoAlumnoMateria * alumno2 = (EstadoAlumnoMateria*)alum2;

    fprintf(stdout,"\n%s  %d %s  %d\n",alumno1->apyn,alumno1->dni, alumno2->apyn,alumno2->dni);
}

void acumularNotas(void * alum1, const void * alum2)
{
    EstadoAlumnoMateria * alumno1 = (EstadoAlumnoMateria*)alum1;
    EstadoAlumnoMateria * alumno2 = (EstadoAlumnoMateria*)alum2;

    alumno1->notaP1=alumno2->notaP1 != 0? alumno2->notaP1: alumno1->notaP1;
    alumno1->notaP2=alumno2->notaP2 != 0? alumno2->notaP2: alumno1->notaP2;
    alumno1->notaR1=alumno2->notaR1 != 0? alumno2->notaR1: alumno1->notaR1;
    alumno1->notaR2=alumno2->notaR2 != 0? alumno2->notaR2: alumno1->notaR2;

    alumno1->notaFinal = alumno1->notaP1 >= alumno1->notaR1?alumno1->notaP1: alumno1->notaR1;
    alumno1->notaFinal += alumno1->notaP2 >= alumno1->notaR2?alumno1->notaP2: alumno1->notaR2;

    if(alumno1->notaP1>= 7 && alumno1->notaP2>=7)
    {
        alumno1->condicion=PR;
    }
    else if( alumno1->notaP1>=4 ||  alumno1->notaP2>=4)
    {
        alumno1->condicion = CU;
    }
    else if(alumno1->notaP1!=0 ||alumno1->notaP2!=0)
    {
        alumno1->condicion = RE;
    }
    alumno1->notaFinal/=2;
    if((alumno1->notaP1 + alumno1->notaP2) %2 >=0.5)
        alumno1->notaFinal++;
}

int actualizarYeliminarListaDes_AlU(Lista *l, Cmp cmp, Actualizar actualizar)
{
    Nodo * nae;
    if(!*l)
        return falso;
    while((*l)->sig)
    {
        nae = buscarNodo_Alu(&(*l)->sig,(*l)->elem,cmp);
        if(nae)
        {
            actualizar((*l)->elem,nae->elem);

            free(nae->elem);
            free(nae);
        }
        else
        {
            l = &(*l)->sig;
        }

    }
    return TODO_OK;
}

void mostrarAlumno2(void * alum1)
{
    EstadoAlumnoMateria * alumno = (EstadoAlumnoMateria*)alum1;
    fprintf(stdout,"\n%d %s %s %d %d %d %d %s %d\n", alumno->dni,alumno->apyn,alumno->materia, alumno->notaP1, alumno->notaP2, alumno->notaR1, alumno->notaR2,enumStrings[alumno->condicion], alumno->notaFinal);
}
Nodo * buscarNodo_Alu(Lista *l,void * elem, Cmp cmp)
{
    int comp = cmp((*l)->elem, elem);
    while((*l)->sig && comp!=0)
    {
        l = &(*l)->sig;
        comp = cmp ((*l)->elem, elem);

    }
    if(comp==0)
        return *l;

    return NULL;
}

int eliminarDeListaOrdDuplicados_ALU(Lista *l, Cmp cmp, Actualizar actualizar)
{
//
//    if(!*l)
//        return falso;
//
//    Nodo * actual;
//    //Nodo * aux;
//    Nodo *nae;
//    while(*l)
//    {
//        Lista *lSig = &(*l)->sig;
//        while(*lSig)
//        {
//            if(cmp ((*l)->elem,(*lSig)->elem)==0)
//            {
//
//                Nodo * nae = *lSig;
//                (*lSig) = nae->sig;
//                actualizar((*l)->elem,nae->elem);
//                free(nae->elem);
//                free(nae);
//            }
//            else
//                lSig = &(*lSig)->sig;
//
//        }
//        (*l)->sig = *lSig;
//        l = &(*l)->sig;
//
//    }
//    while(*l)
//    {
//        actual = (*l)->sig;
//        while(actual)
//        {
//            if(cmp((*l)->elem, actual->elem)==0)
//            {
//                actualizar((*l)->elem, actual->elem);
//                nae = actual;
//                actual = nae->sig;
//                free(nae->elem);
//                free(nae);
//            }
//            else
//                actual= actual->sig;
//        }
//        (*l)->sig = actual;
//        l = &(*l)->sig;
//    }

//    while(*l)
//    {
//        actual = (*l)->sig;
//        while(actual && cmp((*l)->elem, actual->elem)==0)
//        {
//            actualizar((*l)->elem,actual->elem);
//            aux = actual;
//            actual= aux->sig;
//            free(aux->sig);
//            free(aux);
//        }
//        (*l)->sig = actual;
//        l = &(*l)->sig;
//    }

    if (!*l)
        return falso;

    while (*l)
    {
        Lista *lSig = &(*l)->sig;
        while (*lSig)
        {
            if (cmp((*l)->elem, (*lSig)->elem) == 0)
            {
                Nodo *nae = *lSig;
                (*lSig) = nae->sig;
                free(nae->elem);
                free(nae);
            }
            else

                lSig = &(*lSig)->sig;

        }
        (*l)->sig = *lSig;
        l = &(*l)->sig;
    }




    return verdadero;
}
int eliminarDeListaDesordDuplicados_ALU(Lista *l, Cmp cmp, Actualizar actualizar)
{

    if(!(*l)))
        return falso;

        while(*l)
    {

        Lista *lSig = &(*l)->sig;
            while(*lSig)
            {
                if(cmp(*l)->elem (*lSig)->elem) ==0)
                {

                    Nodo * nae = *lSig;
                    (*lSig)= nae->sig;
                    free(nae->elem);
                    free(nae);

                }
                else
                    lSig = &(*l)->sig;
                }
        }


    return verdadero;
}
int eliminarDeListaOrdDuplicados_ALU(Lista *l, Cmp cmp, Actualizar actualizar)
{
    if(!*l)
        return falso;

    return verdadero;
}

void ordenarALU( Lista *l, Cmp cmp)
{
    Lista lOrd;
    Lista *plOrd;
    Nodo *nodo;
    while(*l)
    {
        nodo = *l;
        *l = nodo->sig;

        plOrd = &lOrd;
        while(*plOrd && cmp (nodo->elem, (*plOrd)->elem) >0)
            plOrd = &(*plOrd)->sig;

        nodo->sig = *plOrd;
        *plOrd=nodo;
    }
    *l = lOrd;
}


int cmpDniYMateria_ALU( const void* first, const void* second )
{
    int difDNI = ((EstadoAlumnoMateria*)(first))->dni - ((EstadoAlumnoMateria*)(second))->dni;
    if (difDNI == 0)
    {
        return strcmp( ((EstadoAlumnoMateria*)(first))->materia, ((EstadoAlumnoMateria*)(second))->materia );
    }
    return difDNI;
}
