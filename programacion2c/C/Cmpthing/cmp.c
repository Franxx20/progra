#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmp.h"

void ordenarSel(void* vec, int ce, size_t tamElem, Cmp cmp)
{
    void* ult = vec + (ce-1) * tamElem;
    void* menor;

    for(void* ini = vec; ini < ult; ini += tamElem)
    {
        menor = buscarMenor(ini, ult, tamElem, cmp);

        if(menor != ini)
            intercambiar(ini,menor,tamElem);
    }
}

void* buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp)
{
    void* menor = ini;

    for(void* j = ini + tamElem; j <= fin; j += tamElem)
    {
        if(cmp(j, menor) < 0)
            menor = j;
    }
    return menor;
}

void intercambiar(void* elem1, void* elem2, size_t tamElem)
{
    void* aux = malloc(tamElem); // dinamica (mas chad)
    //char aux[tamElem]; // estatica(mas segura)
    memcpy(aux, elem1, tamElem);  // aux = elem1
    memcpy(elem1, elem2, tamElem); // elem1 = elem2
    memcpy(elem2, aux, tamElem); // elem2 = aux
    free(aux);

}
void mostrarVec(const void* vec, int ce, size_t tamElem, Mostrar mostrar, FILE * stream)
{
    void* ult = (void*)vec + (ce-1) * tamElem;
    for(void* i = (void*)vec; i < ult ; i += tamElem)
    {
        mostrar(i, stream);
    }
//    for (int i = 0; i<ce ; i++ )
//    {
//        mostrar(vec,stream);
//        vec+=tamElem;
//    }

}
