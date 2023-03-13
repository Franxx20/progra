#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
/// Descomentar lo que corresponda. Si Recupera parcial 1: TDA_LISTA_IMPL_DINAMICA. Si es parcial 2: TDA_LISTA_IMPL_DINAMICA_DOBLE.
#define TDA_LISTA_IMPL_DINAMICA
//#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDAlista.h"

#include "../SolucionAlumnos/SolucionAlumnos.h"
#include "../SolucionAlumnos/Nota.h"
#include "../SolucionAlumnos/EstadoAlumnoMateria.h"
#include <string.h>
#include <math.h>
#define NOMBRE_ARCHIVO_NOTAS "Notas.dat"

void procesarLista_ALU(Lista* plAM);
int cmpAlumno_alu(const void* e1, const void* e2);
void actNota_alu(void* actualizado, const void* actualizador);
void notaFinal(void* elem, void* datosAccion);
int cmpNota_alu(const void* e1, const void* e2);
bool eliminarDuplicadosListaDesConAcum(Lista *l, Cmp cmp, Actualizar actualizar);

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
	recorrerLista(&listaAM, mostrarEstadoAM, NULL);

	return 0;
}

void procesarLista_ALU(Lista* plAM)
{
    eliminarDeListaDesordDuplicados(plAM, cmpAlumno_alu, actNota_alu);
  //  eliminarDuplicadosListaDesConAcum(plAM,cmpAlumno_alu,actNota_alu);
    recorrerLista(plAM, notaFinal, NULL);
    ordenarLista(plAM, cmpNota_alu);
}

int cmpAlumno_alu(const void* e1, const void* e2)
{
    EstadoAlumnoMateria* a1 = (EstadoAlumnoMateria*)e1;
    EstadoAlumnoMateria* a2 = (EstadoAlumnoMateria*)e2;

    return a1->dni - a2->dni + strcmp(a1->materia, a2->materia);
}

void actNota_alu(void* actualizado, const void* actualizador)
{
    EstadoAlumnoMateria* a1 = (EstadoAlumnoMateria*)actualizado;
    EstadoAlumnoMateria* a2 = (EstadoAlumnoMateria*)actualizador;

    if(a2->notaP1)
        a1->notaP1 = a2->notaP1;
    else if(a2->notaP2)
        a1->notaP2 = a2->notaP2;
    else if(a2->notaR1)
        a1->notaR1 = a2->notaR1;
    else
        a1->notaR2 = a2->notaR2;
}

void notaFinal(void* elem, void* datosAccion)
{
    EstadoAlumnoMateria* estado = (EstadoAlumnoMateria*)elem;

    int N1 = estado->notaP1>estado->notaR1? estado->notaP1:estado->notaR1;
    int N2 = estado->notaP2>estado->notaR2? estado->notaP2:estado->notaR2;

    if(!N1 || !N2)
        estado->condicion = AU;
    else if(N1>=7 && N2>=7)
        estado->condicion = PR;
    else if(N1>=4 && N2>=4)
        estado->condicion = CU;
    else
        estado->condicion = RE;

    if(estado->condicion == PR)
        estado->notaFinal = round(((float)N1+N2)/2);
    else if(estado->condicion == CU)
        if(N1+N2/2 >= 7)
            estado->notaFinal = 6;
        else
            estado->notaFinal = round(((float)N1+N2)/2);
    else if(estado->condicion == RE)
        estado->notaFinal = 2;
}

int cmpNota_alu(const void* e1, const void* e2)
{
    EstadoAlumnoMateria* n1 = (EstadoAlumnoMateria*)e1;
    EstadoAlumnoMateria* n2 = (EstadoAlumnoMateria*)e2;

    return n2->notaFinal - n1->notaFinal;
}

bool eliminarDuplicadosListaDesConAcum(Lista *pl, Cmp cmp, Actualizar actualizar)
{
//    if(!*l)
//        return false;
//
//
//    while(*l)
//    {
//        Lista *lSig = &(*l)->sig;
//        while(*lSig)
//        {
//            if(cmp((*l)->elem,(*lSig)->elem)==0)
//            {
//                Nodo * nae = *lSig;
//                (*lSig) = nae->sig;
//                free(nae->elem);
//                free(nae);
//            }
//            else
//            {
//                lSig =&(*lSig)->sig;
//            }
//        }
//        l = &(*l)->sig;
//    }
//

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
    return true;
}
