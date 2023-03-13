#include <stdio.h>
#include <stdlib.h>

#include "ListaDoble.h"

/*                                                                                              FUNCIONA?
void crearLista(Lista* pl);                                                                     SI
void vaciarLista(Lista* pl);                                                                    SI
int listaVacia(const Lista* pl);                                                                SI
int listaLlena(const Lista* pl, size_t tamDato);                                                SI

int insertarEnListaAlInicio(Lista *pl, const void* dato, size_t tamDato);                       SI
int insertarEnListaAlFinal(Lista* pl, const void* dato, size_t tamDato);                        SI
int insertarEnListaPosicion(Lista* pl, const void* dato, size_t tamDato, unsigned pos);         PROBAR
int insertarEnListaOrd(Lista* pl, const void* dato, size_t tamDato, Cmp cmp);                   SI

int verPrimeroDeLista(const Lista* pl, void* dato, size_t tamDato);                             SI
int verUltimoDeLista(const Lista* pl, void* dato, size_t tamDato);                              SI
int verPosicionDeLista(const Lista* pl, void* dato, size_t tamDato, unsigned pos);              PROBAR

int eliminarPrimeroDeLista(Lista* pl, void* dato, size_t tamDato);                              SI
int eliminarUltimoDeLista(Lista* pl, void* dato, size_t tamDato);                               SI
int eliminarPosicionDeLista(Lista* pl, void* dato, size_t tamDato, unsigned pos);               PROBAR
int eliminarDeListaOrd(Lista* pl, void* dato, size_t tamDato, Cmp cmp);                         SI

int eliminarDupDeListaOrd(Lista* pl, Cmp cmp);                                                  SI
int eliminarDupDeListaDes(Lista* pl, Cmp cmp);                                                  SI

void recorrerLista(Lista* pl, Accion accion, void* datosAccion);                                SI
void recorrerListaInvertido(Lista* pl, Accion accion, void* datosAccion);                       SI

int buscarEnListaOrd(const Lista* pl, void* dato, size_t tamDato, Cmp cmp);                     SI

void ordenarLista(Lista* pl, Cmp cmp);                                                          SI

*/

#define tam 9

void mostrarInt(void* dato, void* datoAccion);
int compararInt(const void* dato1, const void* dato2);

int main()
{
    Lista p;
    crearLista(&p);

    int num;
    for(int i = 0; i < tam; i++)
    {
        printf("Ingrese un numero:");
        scanf("%d",&num);
        insertarEnListaAlFinal(&p,&num, sizeof(int));

    }

    printf("\nLista:\n");
    recorrerLista(&p, mostrarInt, NULL);

    /*
    if(eliminarDupDeListaDes(&p, compararInt))
    {
        printf("\nLista despues de eliminar duplicados:\n");
        recorrerLista(&p, mostrarInt, NULL);
    }
    */

    /*
    if(eliminarDupDeListaOrd(&p, compararInt))
    {
        printf("\nLista despues de eliminar duplicados:\n");
        recorrerLista(&p, mostrarInt, NULL);
    }
    */

     /*
    printf("\nLista Invertida:\n");
    recorrerListaInvertido(&p, mostrarInt, NULL);
    */

    /*
    ordenarLista(&p, compararInt);
    printf("\n\nLista ordenada:\n");
    recorrerLista(&p, mostrarInt, NULL);
    */

    /*
    int num5;
    if(eliminarPrimeroDeLista(&p, &num5, sizeof(int)))
    {
        printf("\n\nPrimero de lista eliminado : %d\n",num5);
        printf("\nLista despues de eliminar: %d\n",num5);
        recorrerLista(&p, mostrarInt, NULL);
    }
    */

    /*
    int num6;
    if(eliminarUltimoDeLista(&p, &num6, sizeof(int)))
    {
        printf("\n\nUltimo de lista eliminado : %d\n",num6);
        printf("\nLista despues de eliminar: %d\n",num6);
        recorrerLista(&p, mostrarInt, NULL);
    }
    */

    /*
    int num3 = 5;
    if(buscarEnListaOrd(&p,&num3, sizeof(int), compararInt))
        printf("\n\n%d esta en la lista\n",num3);
    */

    /*
    if(eliminarDeListaOrd(&p, &num3, sizeof(int), compararInt))
    {
        printf("\nValor %d eliminado\n", num3);
        printf("\nLista habiendo borrado: %d:\n", num3);
        recorrerLista(&p, mostrarInt, NULL);
    }
    */

    /*
    int num2;

    verPrimeroDeLista(&p, &num2, sizeof(int));
    printf("\n\nPrimero de lista: %d\n",num2);
    verUltimoDeLista(&p, &num2, sizeof(int));
    printf("\nUltimo de lista: %d\n",num2);
    */


    vaciarLista(&p);

    if(listaVacia(&p))
        printf("\nla lista se vacio correctamente\n");


    return 0;
}


void mostrarInt(void* dato, void* datoAccion)
{
    int* num = (int*)dato;

    printf("%d\t", *num);
}

int compararInt(const void* dato1, const void* dato2)
{
    return *(int*)dato1 - *(int*)dato2;
}
