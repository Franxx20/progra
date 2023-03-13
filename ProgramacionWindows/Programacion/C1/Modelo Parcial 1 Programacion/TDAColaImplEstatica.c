#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TDA_COLA_IML_ESTATICA //Importante que este antes
#include "../TDACola/TDACola.h"


void* copiarAVector(void* vecLIzq, void* vecLDer, void* destino, const void* origen, size_t tamDato);
void* copiarDeVector(const void* vecLIzq, const void* vecLDer, void* destino, const void* origen, size_t tamDatoDestino, size_t tamDatoOrigen);
void* calcularFinDato(const void* vecLIzq, const void* vecLDer, const void* origen, size_t tamDatoOrigen);

void crearCola(Cola* pc)
{
    pc->frente = pc->fondo = pc->vCola;
    pc->tamDisponible = TAM_COLA;
}

booleano encolar(Cola* pc, const void* elem, size_t tamElem)
{
    if(tamElem + sizeof(size_t) > pc->tamDisponible)
        return FALSO;

    pc->fondo = copiarAVector(pc->vCola, pc->vCola + TAM_COLA, pc->fondo, &tamElem, sizeof(size_t)); // Coloco un entero que indica lca cantidad de bytes que ocupa el elemento
    pc->fondo = copiarAVector(pc->vCola, pc->vCola + TAM_COLA, pc->fondo, elem, tamElem); // Coloco el elemento

    pc->tamDisponible -= tamElem + sizeof(size_t);

    return VERDADERO;
}

booleano desencolar(Cola* pc, void* elem, size_t tamElem)
{
    if(pc->tamDisponible == TAM_COLA)
        return FALSO;

    size_t tamElemEncolado;

    pc->frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, &tamElemEncolado, pc->frente, sizeof(size_t), sizeof(size_t));
    pc->frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, elem, pc->frente, tamElem, tamElemEncolado);

    pc->tamDisponible += tamElemEncolado + sizeof(size_t);

    return VERDADERO;
}

booleano verFrenteDeCola(const Cola* pc, void* elem, size_t tamElem)
{
    if(pc->tamDisponible == TAM_COLA)
        return FALSO;

    size_t tamElemEncolado;

    void* frente = pc->frente;

    frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, &tamElemEncolado, frente, sizeof(size_t), sizeof(size_t));
    frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, elem, frente, tamElem, tamElemEncolado);

    return VERDADERO;
}

booleano colaVacia(const Cola* pc)
{
    return pc->tamDisponible == TAM_COLA;
}

booleano colaLlena(const Cola* pc, size_t tamElem)
{
    return tamElem + sizeof(size_t) > pc->tamDisponible;
}

void vaciarCola(Cola* pc)
{
    pc->frente = pc->fondo = pc->vCola;
    pc->tamDisponible = TAM_COLA;
}

void* copiarAVector(void* vecLIzq, void* vecLDer, void* destino, const void* origen, size_t tamDato)
{
    size_t cantACopiar = tamDato;
    size_t cantACopiar1erMC = vecLDer - destino;


    if(cantACopiar > cantACopiar1erMC) //Agregue yo
    {
        memcpy(destino, origen, cantACopiar1erMC);
        cantACopiar -= cantACopiar1erMC; // Resto lo que ya copie --> Se rompe

        if(cantACopiar > 0) // Si es 0 significa que pudo copiar todo entero
        {
            destino = vecLIzq;
            //memcpy(destino, vecLIzq, )
            origen += cantACopiar1erMC; // Avanzo hasta donde se haya copiado el elemento --> Porque se corto
            memcpy(destino, origen, cantACopiar); // El fondo (destino) quedo despues de los bytes que se puderion copiar
        }
    }
    else
        memcpy(destino, origen, cantACopiar);


    return destino + cantACopiar; // Voy al final de donde se copio lo ultimo, para el siguiente dato
}

void* copiarDeVector(const void* vecLIzq, const void* vecLDer, void* destino, const void* origen, size_t tamDatoDestino, size_t tamDatoOrigen)
{
    size_t cantACopiar = min(tamDatoOrigen, tamDatoDestino);
    size_t cantACopiar1erMC = vecLDer - origen;

    void* finDato = calcularFinDato(vecLIzq, vecLDer, origen, tamDatoOrigen);

    if(cantACopiar > cantACopiar1erMC) //Agregue yo
    {
        memcpy(destino, origen, cantACopiar1erMC);

        if(cantACopiar > 0)
        {
            origen = vecLIzq;
            destino += cantACopiar1erMC;
            memcpy(destino, origen, cantACopiar);
        }
    }
    else
        memcpy(destino, origen, cantACopiar);

    return finDato;
}

void* calcularFinDato(const void* vecLIzq, const void* vecLDer, const void* origen, size_t tamDatoOrigen)
{
    const void* finDato = origen + tamDatoOrigen;

    if(finDato > vecLDer)
        finDato = vecLIzq + (finDato - vecLDer);

    return (void*)finDato;
}
