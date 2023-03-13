#include <stdio.h>
#include <stdlib.h>
#include"arbol.h"
int compararEnteros(const void * d1, const void * d2);
void mostrarEnteros(const void *dato, int nivel);

int main()
{
    int num1 =1;
    int num2 = 2;
    int num3 = 3;
    int num4 =4 ;

    Arbol t ;
    crearArbol(&t);
    insertarEnArbol(&t,&num2,sizeof(int),compararEnteros,NULL);
    insertarEnArbol(&t,&num1,sizeof(int),compararEnteros,NULL);
    insertarEnArbol(&t,&num3,sizeof(int),compararEnteros,NULL);
    insertarEnArbol(&t,&num4,sizeof(int),compararEnteros,NULL);

    mostrarArbolSegunNivel(&t,mostrarEnteros,2);

    vaciarArbol(&t);
    return 0;

}

int compararEnteros(const void * d1, const void * d2)
{
    int * e1 = (int *)d1;
    int * e2 = (int *)d2;

    return *e1 - *e2;
}
void mostrarEnteros(const void *dato, int nivel)
{
    int i=0;
    int * e = (int *)dato;
    for (; i<nivel ; i++ )
    {
        printf("\t");
    }
    printf("%d\n", *e);
}
