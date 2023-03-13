#include <stdio.h>
#include <stdlib.h>
#include "../Lista6/Lista.h"
int compararNumeros(const void *n1, const void *n2);
void mostrarNumeros(void *num, void *datos);
int main()
{
    Lista l;
    int numeros[18] = {1, 4,4, 2, 3, 6, 87, 5, 4, 2, 1,4, 4,65,4, 9, 9, 99};
    crearLista(&l);

    for (int i = 0; i < 18; i++)
    {
        insertarEnListaAlFinal(&l, &numeros[i], sizeof(int));
    }

    recorrerLista(&l, mostrarNumeros, NULL);

    ordenarLista(&l, compararNumeros);
    puts("Lista ordenada");
    recorrerLista(&l, mostrarNumeros, NULL);

    puts("Borrando duplicados");
    eliminarDuplicadosListaOrdConAcum(&l,compararNumeros,NULL);
    recorrerLista(&l, mostrarNumeros, NULL);

    //////// LISTA2 //////
    int numeross[18] = {1, 4,4, 2, 3, 6, 87, 5, 4, 2, 1,4, 4,65,4, 9, 9, 99};
    Lista l2;
    crearLista(&l2);
    for (int i = 0; i<18 ; i++ )
    {
        insertarEnListaAlFinal(&l2,&numeross[i], sizeof(int));
    }

    puts("LISTA2");
    recorrerLista(&l2, mostrarNumeros, NULL);
    puts("Borrando duplicados L2");
    eliminarDuplicadosListaDesConAcum(&l2, compararNumeros,NULL);
    recorrerLista(&l2, mostrarNumeros, NULL);

    puts("LISTA3");
    Lista l3;
    crearLista(&l3);
    for (int i =0; i<10 ; i++ )
    {
        insertarEnListaAlInicio(&l3,&i,sizeof(int));

//        insertarEnListaAlFinal(&l3,&i,sizeof(int));
//        ordenarLista(&l3,compararNumeros);
//         eliminarDuplicadosListaOrdConAcum(&l3,compararNumeros,NULL);
    }
    int num =500;
    int num3 =3500;
    int num4=400;
    int num5 =6000;
    int num6 =-1;
    int num7=0;
    insertarEnListaPorPos(&l3,&num,sizeof(int),3);
    ordenarLista(&l3,compararNumeros);
    insertarEnListaOrdConAcum(&l3,&num3,sizeof(int),compararNumeros,NULL);
    insertarEnListaOrdConAcum(&l3,&num5,sizeof(int),compararNumeros,NULL);
    insertarEnListaOrdConAcum(&l3,&num4,sizeof(int),compararNumeros,NULL);
    insertarEnListaOrdConAcum(&l3,&num6,sizeof(int),compararNumeros,NULL);
    int pos =buscarEnListaOrd(&l3,&num4,sizeof(int),compararNumeros);
    eliminarDeListaPorPos(&l3,&num7,sizeof(int),pos);
        eliminarDeListaAlFinal(&l3,&num7,sizeof(int));

    recorrerLista(&l3, mostrarNumeros, NULL);
    fprintf(stdout,"\n numero7 %d\n",num7);

    vaciarLista(&l);
    vaciarLista(&l2);
    vaciarLista(&l3);

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
