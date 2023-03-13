#include <stdio.h>
#include <stdlib.h>

#include "D:\Programacion\C\tp2\ListaDoble6\lista.h"
int compararNumeros(const void *n1, const void *n2);
void mostrarNumeros(void *num, void *datos);
int main()
{

    int numerosOrd[18] = {1, 4,4, 2, 3, 6, 87, 5, 4, 2, 1,4, 4,65,4, 9, 9, 99};
    Lista lOrd;
    crearLista(&lOrd);
    for (int i =0; i<sizeof(numerosOrd)/sizeof(int) ; i++ )
        insertarEnListaAlFinal(&lOrd,&numerosOrd[i],sizeof(int));

    puts("LISTA DESORDENADA");
    recorrerLista(&lOrd,mostrarNumeros,NULL);

    puts("LISTA ORDENADA");
    ordenarLista(&lOrd,compararNumeros);
    recorrerLista(&lOrd,mostrarNumeros,NULL);

    puts("LISTA SIN DUPS");
    eliminarDuplicadosListaOrd(&lOrd,compararNumeros,NULL);
    recorrerLista(&lOrd,mostrarNumeros,NULL);

    vaciarLista(&lOrd);
//    //////// LISTA2 //////
    int numerosDes[18] = {1, 4,4, 2, 3, 6, 87, 5, 4, 2, 1,4, 4,65,4, 9, 9, 99};

    Lista lDes;
    crearLista(&lDes);
    for (int i =0; i<sizeof(numerosOrd)/sizeof(int) ; i++ )
        insertarEnListaAlFinal(&lDes,&numerosDes[i],sizeof(int));

    puts("LISTA 2 DESORDENADA");
    recorrerLista(&lDes,mostrarNumeros,NULL);

    puts("LISTA 2 SIN DUPS");
    eliminarDuplicadosListaDes(&lDes,compararNumeros,NULL);
    recorrerLista(&lDes,mostrarNumeros,NULL);


    vaciarLista(&lDes);


    //////// LISTA3 ////////
    Lista l;
    crearLista(&l);

    int num0 = 0;
    int num1 = 2;
    int num2 = 1;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;
    int num6 = 6;

    puts("LISTA 3");
    insertarEnListaAlFinal(&l,&num1,sizeof(int));
    insertarEnListaAlInicio(&l,&num2,sizeof(int));
    insertarEnListaOrdenada(&l,&num3,sizeof(int),compararNumeros,NULL);
    insertarEnListaPorPos(&l,&num4,sizeof(int),3);
    insertarEnListaAlFinal(&l,&num5,sizeof(int));
    eliminarDeListaAlFinal(&l,&num5,sizeof(int));
    insertarEnListaAlInicio(&l,&num0,sizeof(int));
    eliminarDeListaAlInicio(&l,&num5,sizeof(int));
    insertarEnListaPorPos(&l,&num6,sizeof(int),5);
    eliminarDeListaPorPos(&l,&num6,sizeof(int),5);

    recorrerLista(&l,mostrarNumeros,NULL);

    vaciarLista(&l);
    return 0;
}

int compararNumeros(const void *n1, const void *n2)
{
    return *(int *)n1 - *(int *)n2;
}

void mostrarNumeros(void *num, void *datos)
{
    printf("El numero es: %d\n", *(int *)num);
}
