#define  VEC_LLENO 1
#define  DUPLICADO 2
#define   TODO_OK 0
#include <stdio.h>
#include<stdbool.h>

int InsertarOrdElemento(int *vec, int *ce, int TAM, int elem)
{
    if (*ce == TAM)
        return VEC_LLENO;
    int i = 0;
    while (i < *ce &&elem >vec[i])
    {
        i++;
    }
    if (i < *ce && elem == vec[i])
    {
        return DUPLICADO;
    }

    for (int j = (*ce) - 1; j >= i; j--)
    {
        vec[j + 1] = vec[j];
    }
    vec[i] = elem;
    (*ce)++;

    return TODO_OK;
}

bool EliminarOrdElemento(int *vec, int *ce, int TAM, int elem)
{
    int i = 0;
    while (i < *ce && elem > vec[i])
    {
        i++;
    }
    if (i == *ce || elem < vec[i])
    {
        return false;
    }
    for (int j = i; j <= *ce - 2; j++)
    {
        vec[j] = vec[j + 1];
    }
    (*ce)--;
    return true;
}
bool EliminarOrdRepetido(int *vec, int *ce)
{
    int i = 0;
    int j = 0;
    int posRepe = 0;
    int cantRepe = 0;
    while (i < *ce && vec[i] != vec[i + 1])
    {
        i++;
    }
    j = i;
    cantRepe++;
    while (j < *ce && vec[j] == vec[j + 1])
    {
        printf("cant Repe: %d\n", cantRepe);
        j++;
    }
    posRepe = i;
    printf("\n pos repe %d\n cant repeeees %d", posRepe, cantRepe);

    for (int k = posRepe; k < *ce - 1; k++)
    {
        vec[k + 1] = vec[k + cantRepe + 1];
    }
    *ce -= cantRepe;
    return true;
}

void mostrarVector(int *vec, int TAM)
{
    for (int i = 0; i < TAM; i++)
    {
        printf("%d\n", *vec);
        vec++;
    }
}

