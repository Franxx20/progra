#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Descomentar lo que corresponda. Si Recupera parcial 1: TDA_LISTA_IMPL_DINAMICA. Si es parcial 2: TDA_LISTA_IMPL_DINAMICA_DOBLE.
//#define TDA_LISTA_IMPL_DINAMICA
#define TDA_LISTA_IMPL_DINAMICA_DOBLE
//#include "../TDALista/TDAlista.h"

#include "../TDALista/TDALista.h"

#include "../SolucionAlumnos/SolucionAlumnos.h"

#include "../Matematica/Matematica.h"

#define NOMBRE_ARCHIVO_NOTAS "Notas.dat"

void procesarLista_ALU(Lista* plAM);
void crearLista_ALU( Lista* lista );

int cmpDni_ALU( const void* first, const void* second );
int cmpDniYMateria_ALU( const void* first, const void* second );
void actAlumno_ALU(void* actualizado, const void* actualizador);
void accActEstadoAlumno_ALU( void* elem, void* datosAccion);
void recorrerLista_ALU( Lista* plAM, Accion accion, void* datosAccion );
booleano verPrimeroDeLista_ALU(const Lista* pl, void* elem, size_t tamElem);
int cmpNotasDec_ALU( const void* first, const void* second );
void ordenarLista_ALU(Lista* pl, Cmp cmp);
int eliminarDeListaDesordDuplicados_ALU(Lista *pl, Cmp cmp, Actualizar actualizar);
NodoD* buscarNodo_ALU( Lista *pl, void *elem, Cmp cmp );
NodoD* buscarMenor_ALU(NodoD* act, Cmp cmp);

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
    /// Desarrolle esta función y todas las que invoque. Puede usar funciones de la biblioteca estándar.
    /// Coloque el sufijo _ALU a todas las funciones que desarrolle.
    /// No use ni modifique otro archivo que no sea main.c. Será el que deberá entregar en formato comprimido con nombre "Apellido_Nombre_DNI.zip".

    //eliminarDeListaDesordDuplicados_ALU( plAM, cmpDni_ALU, actAlumno_ALU );
    //EN EL CASO QUE TUVIERA QUE ANALIZAR TODAS LAS MATERIAS decada alumno:
    eliminarDeListaDesordDuplicados( plAM, cmpDniYMateria_ALU, actAlumno_ALU );
    float promAlumno;
    recorrerLista_ALU( plAM, accActEstadoAlumno_ALU, &promAlumno);
    ordenarLista_ALU(plAM, cmpNotasDec_ALU);
}

int eliminarDeListaDesordDuplicados_ALU(Lista *pl, Cmp cmp, Actualizar actualizar){
    NodoD *elim, *auxSig, *auxAnt;
    if( !*pl ){
        return falso;
    }
    while( (*pl)->ant ){
        pl = &(*pl)->ant;
    }

    while( (*pl)->sig ){
        elim = buscarNodo_ALU( &(*pl)->sig, (*pl)->elem, cmp );
        if( elim ){
            actualizar( (*pl)->elem, elim->elem );
            auxAnt = elim->ant;
            auxSig = elim->sig;

            if( auxAnt ){
                auxAnt->sig = auxSig;
            }
            if( auxSig ){
                auxSig->ant = auxAnt;
            }

            free( elim->elem );
            free( elim );
        } else {
            pl = &(*pl)->sig;
        }
    }
    return verdadero;
}

NodoD* buscarNodo_ALU( Lista *pl, void *elem, Cmp cmp ){
    int comp = cmp( (*pl)->elem, elem );
    while( (*pl)->sig && comp!=0 ){
        pl = &(*pl)->sig;
        comp = cmp( (*pl)->elem, elem );
    }
    if( comp == 0 ){
        return *pl;
    }

    return NULL;
}

void ordenarLista_ALU(Lista* pl, Cmp cmp){
    NodoD *act = *pl, *sig, *ant, *ini=*pl ,*menor;
    if(*pl == NULL){
        return;
    }
    while(act->ant){
        act = act->ant;
    }
    //ini = *pl;

    while(act){
        menor = buscarMenor_ALU(act, cmp);
        if(menor != act){
            ant = menor->ant;
            sig = menor->sig;

            if(ant){
                ant->sig = act;
            }
            if(sig){
                sig->ant = act;
            }
            //intercambio
            menor->ant = act->ant;
            menor->sig = act->sig;
            act->ant = ant;
            act->sig = sig;

            ant = menor->ant;
            sig = menor->sig;

            if(ant){
                ant->sig = menor;
            }
            if(sig){
                sig->ant = menor;
            }
        }
        act = menor->sig;
    }

    *pl = ini;
}

NodoD* buscarMenor_ALU(NodoD* act, Cmp cmp){
    NodoD* menor = act;
    if(act->sig){
        act = act->sig;
    }
    while(act){
        if(cmp(act->elem, menor->elem) < 0){
            menor = act;
        }
        act = act->sig;
    }
    return menor;
}

void recorrerLista_ALU( Lista* pl, Accion accion, void* datosAccion ){
    if( !*pl ){
        return;
    }
    while( *pl && (*pl)->ant ){
        pl = &(*pl)->ant;
    }
    while( *pl && (*pl)->sig ){
        accion( (*pl)->elem, datosAccion );
        pl = &(*pl)->sig;
    }
    accion( (*pl)->elem, datosAccion );
}

booleano verPrimeroDeLista_ALU(const Lista* pl, void* elem, size_t tamElem){
    if( !*pl ){
        return falso;
    }
    NodoD *primeroLista = *pl;
    memcpy( elem, primeroLista->elem, min(primeroLista->tamElem,tamElem) );

    return verdadero;
}

//void (*Accion)(void* elem, void* datosAccion);
void accActEstadoAlumno_ALU(void* elem, void* datosAccion){
//verPrimeroDeLista_ALU( plAM, &alumnoActual, sizeof(EstadoAlumnoMateria) );
    EstadoAlumnoMateria *alumnoActual= (EstadoAlumnoMateria*)elem;
    int notaP1;
    if( alumnoActual->notaP1 > alumnoActual->notaR1 ){
        notaP1 = alumnoActual->notaP1;
    } else {
        notaP1 = alumnoActual->notaR1;
    }

    int notaP2;
    if( alumnoActual->notaP2 > alumnoActual->notaR2 ){
        notaP2 = alumnoActual->notaP2;
    } else {
        notaP2 = alumnoActual->notaR2;
    }

    *(float*)datosAccion = (notaP1 + notaP2) / (float)2;
    float promedioAlumno = *(float*)datosAccion;
    if( (notaP1 + notaP2)%2 >= 0.5 ){
        promedioAlumno++;
    }
    if( notaP1==0 || notaP2==0 ){
        alumnoActual->notaFinal = 0; ///Alumno ausente
        alumnoActual->condicion = AU;
    } else if( notaP1<4 || notaP2<4 ){
        alumnoActual->notaFinal = 2; ///Alumno reprobado
        alumnoActual->condicion = RE;
    } else if( (notaP1>=4 && notaP1<7) || (notaP2>=4 && notaP2<7) ){
        if( promedioAlumno >=7){
            promedioAlumno--;///Alumno que no puede tener 7 porque no promociono
        }
        alumnoActual->notaFinal = promedioAlumno;
        alumnoActual->condicion = CU;
    } else {
        alumnoActual->notaFinal = (int)promedioAlumno;
        alumnoActual->condicion = PR;
    }

    //printf("prom: %f\n", *(float*)datosAccion);
    /*printf("alumno: %d,%s,%s,\n\tP1:%d\tP2:%d\n\tR1:%d\tR2:%d\n\t%d,%d\n",
            alumnoActual.dni,
            alumnoActual.apyn,
            alumnoActual.materia,
            alumnoActual.notaP1, alumnoActual.notaP2,
            alumnoActual.notaR1, alumnoActual.notaR2,
            alumnoActual.condicion,
            alumnoActual.notaFinal);*/
}
//int (*Cmp)(const void* e1, const void* e2);
int cmpDni_ALU( const void* first, const void* second ){
    return ((EstadoAlumnoMateria*)(first))->dni - ((EstadoAlumnoMateria*)(second))->dni;
}

int cmpDniYMateria_ALU( const void* first, const void* second ){
    int difDNI = ((EstadoAlumnoMateria*)(first))->dni - ((EstadoAlumnoMateria*)(second))->dni;
    if (difDNI == 0){
        return strcmp( ((EstadoAlumnoMateria*)(first))->materia, ((EstadoAlumnoMateria*)(second))->materia );
    }
    return difDNI;
}

int cmpNotasDec_ALU( const void* first, const void* second ){
    return -(((EstadoAlumnoMateria*)(first))->notaFinal - ((EstadoAlumnoMateria*)(second))->notaFinal);
}

//void (*Actualizar)(void* actualizado, const void* actualizador);
void actAlumno_ALU(void* actualizado, const void* actualizador){
    EstadoAlumnoMateria *regFinal = (EstadoAlumnoMateria*)(actualizado);
    EstadoAlumnoMateria *regActualizador = (EstadoAlumnoMateria*)(actualizador);

    if( strcmp(regFinal->materia,regActualizador->materia) ==0 ){
        if ( regFinal->notaP1 < regActualizador->notaP1 ){
            regFinal->notaP1 = regActualizador->notaP1;
        } else if( regFinal->notaR1 < regActualizador->notaR1 ){
            regFinal->notaR1 = regActualizador->notaR1;
        }

        if ( regFinal->notaP2 < regActualizador->notaP2 ){
            regFinal->notaP2 = regActualizador->notaP2;
        } else if( regFinal->notaR2 < regActualizador->notaR2 ){
            regFinal->notaR2 = regActualizador->notaR2;
        }
    }
}

void crearLista_ALU( Lista* lista ){
    *lista = NULL;
}
