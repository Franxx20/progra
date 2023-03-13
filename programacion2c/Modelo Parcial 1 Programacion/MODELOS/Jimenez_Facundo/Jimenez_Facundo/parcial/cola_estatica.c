#include "../include/cola_estatica.h"
#include <string.h>
///yo pondria string.h en el archivo header, pero preferí no meter mano ahi por las dudas

void crear_cola(tCola* pc){
    pc->pri = TAM_COLA - 70;
    pc->ult = TAM_COLA - 70;
    pc->tamDisp = TAM_COLA;
}

int frente_de_cola(const tCola * pc, void * pd, unsigned tam){

    unsigned    tamInfo,
                ini,
                fin,
                priAux = pc->pri; ///guarda la info de el pri actualizado para no modificarlo
    if(pc->tamDisp == TAM_COLA){
        return 0;
    }

    ini = MINIMO(sizeof(unsigned), TAM_COLA - priAux);
    memcpy(&tamInfo, pc->cola + priAux, ini);
    fin = sizeof(unsigned) - ini;

    if(fin != 0){
        memcpy((char*)&tamInfo + tamInfo, pc->cola, fin);
    }

    priAux = (fin!=0)? fin : priAux + sizeof(unsigned);
    tamInfo = MINIMO(tam, tamInfo); ///la info que quiero sacar, es la misma que esta grabada en la pila?

    ///ahora voy a extraer la info
    ini = MINIMO(tamInfo, TAM_COLA - priAux);
    memcpy(pd, pc->cola + priAux, ini);
    fin = tamInfo - ini;
    if(fin != 0){
        memcpy((char*)pd + ini, pc->cola, fin);
    }
    return 1;
}

int cola_llena(const tCola* pc, unsigned tam){
    return pc->tamDisp < (tam + sizeof(unsigned));
}

int cola_vacia(const tCola* pc){
    return pc->tamDisp == TAM_COLA;
}

int poner_en_cola(tCola *pc, const void* pd, unsigned tam){

   int  ini,        //ini y fin representan la parte inicial y final de lo que quiero copiar
        fin;
    if(pc->tamDisp < (tam + sizeof(unsigned))) //verifico que haya espacio disponible
        return 0;
    if((ini = MINIMO(TAM_COLA - pc->ult, sizeof(unsigned))) > 0) //si tengo espacio para copiar ALGO o TODO el dato del unsigned TamInfo
        memcpy(pc->cola + pc->ult, &tam, ini);
    if((fin = sizeof(unsigned) - ini) > 0)
        memcpy(pc->cola, (char*)(&tam) + ini, fin); //en caso de que haya quedado el unsigned por la mitad, le cargo la parte que le faltó, en el principio de la cola

    pc->ult = (fin == 0) ? pc->ult + sizeof(unsigned) : fin;
    /// ya copié el tam, ahora me queda copiar el dato en si

    if((ini = MINIMO(TAM_COLA - pc->ult, tam)) > 0)
        memcpy(pc->cola + pc->ult, pd, ini);
    if((fin = tam - ini) > 0)
        memcpy(pc->cola, pd + ini, fin);

    pc->ult = (fin == 0) ? pc->ult + tam : fin;

    pc->tamDisp -= (tam + sizeof(unsigned));
    return 1;
}

int sacarDeCola(tCola* pc, void* pd, unsigned tam){
    unsigned auxTamInfo;
    int ini,
        fin;
    if(pc->tamDisp == TAM_COLA)
        return 0;

    if((ini = MINIMO(sizeof(unsigned), TAM_COLA - pc->pri)) > 0)
        memcpy(&auxTamInfo, pc->cola + pc->pri, ini);
    if((fin = sizeof(unsigned) - ini) > 0)
        memcpy((char*)(&auxTamInfo) + ini, pc->cola, fin);

    pc->pri = (fin == 0) ? pc->pri + sizeof(unsigned) : fin;

    //ya copié el unsigned

    if((ini = MINIMO(tam, TAM_COLA - pc->pri)) > 0)
        memcpy(pd, pc->cola + pc->pri, ini);
    if((fin = tam - ini) > 0)
        memcpy(pd + ini, pc->cola, fin);
    pc->pri = (fin == 0) ? pc->pri + tam : fin;

    pc->tamDisp += tam + sizeof(unsigned);
    return 1;
}


void vaciar_cola(tCola* pc){
    pc->pri = pc->ult;
    pc->tamDisp = TAM_COLA;
}




