#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol/arbol.h"

int cmp_float(const void *, const void *);
void mostrarFloat(const void* data, unsigned tam);
void treeFormat(const void* data, unsigned tam);
int cargarDesdeDatosOrdenadosRec(tArbol *tree, float *data, int li, int ls, comparar cmp);

int main()
{
    tArbol tree;
	int li, ls, ls_2;

	float vec[] = {1,2,3,4,5,6,7,8,9,15},
		  vec_2[] = {0,8.5,16};

	crearArbol(&tree);

	li = 0; ls = sizeof(vec)/sizeof(vec[0]);
    ls_2 = sizeof(vec_2)/sizeof(vec_2[0]);
	cargarDesdeDatosOrdenadosRec(&tree, vec, li, ls - 1, cmp_float);
	cargarDesdeDatosOrdenadosRec(&tree, vec_2, 0, ls_2 - 1, cmp_float);

	/*{
        int rc;
        puts("Esta el arbol balanceadoAVL?");
	    rc = arbol_esAVL(&tree);
	    (rc == 1)? puts("Si.") : puts("No.");

        arbol_recorrerPreOrden(&tree, mostrar);
    }

    {
        float aux;
        arbol_mayorNodo(&tree, &aux, sizeof(float));
        printf("Mayor: %.2f\n", aux);

        arbol_menorNodo(&tree, &aux, sizeof(float));
        printf("Menor: %.2f\n", aux);
    }

    {
        size_t rc[5] = {0};

        rc[0] = arbol_altura(&tree);
        rc[1] = arbol_cantNodos(&tree);
        rc[2] = arbol_cantNodosHastaNivel(&tree, 2);
        rc[3] = arbol_cantNodosHastaNivel(&tree, 3);

        printf(
            "Altura: %ld\n"
            "cantNodos: %ld\n"
            "cantNodos cuarto nivel: %ld\n",
            rc[0], rc[1], rc[3] - rc[2]
        );
    }*/

   /* {
        float aux;

        arbol_eliminarRaiz(&tree);

        arbol_mayorNodo(&tree, &aux, sizeof(float));
        arbol_eliminaNodo(&tree, &aux, sizeof(float), cmp_float);

        arbol_menorNodo(&tree, &aux, sizeof(float));
        arbol_eliminaNodo(&tree, &aux, sizeof(float), cmp_float);

        arbol_recorrerPreOrden(&tree, mostrar);
    }

    {
        float aux = 99;
        tArbol *t_aux = arbol_buscar(&tree, &aux, sizeof(float), cmp_float);
        if(t_aux) {
            arbol_recorrerPreOrden(t_aux, mostrar);
        }
    }*/


    arbol_levelOrder(&tree, treeFormat);
    

	vaciarArbol(&tree);
	return 0;
}


void mostrarFloat(const void* data, unsigned tam)
{
    float *d = (float *)data;

    printf("> %.2f\n", *d);
}

void treeFormat(const void* data, unsigned tam)
{
    float *d = (float *)data;

    printf(" %*.2f ", 6*tam, *d);
}


int cmp_float(const void *d1, const void *d2)
{
	int *_d1 = (int *)d1,
	    *_d2 = (int *)d2;
	return  (*_d1) - (*_d2);
}


int cargarDesdeDatosOrdenadosRec(tArbol *tree, float *data, int li, int ls, comparar cmp)
{
    int m = (li+ls)/2;

	if(li > ls) {
		return 1;
	}

	arbol_insertarRecursivo(tree, data + m, sizeof(float), cmp);

    cargarDesdeDatosOrdenadosRec(&(*tree)->izq, data, li, m-1, cmp);
    return cargarDesdeDatosOrdenadosRec(&(*tree)->der, data, m+1, ls, cmp);
}
