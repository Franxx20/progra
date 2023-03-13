#include <stdio.h>
#include <stdlib.h>
#include "Ejercicio 2.h"

int main()
{
    char cad[]="A cavar a Caravaca";
    borra_todos_espacios(cad);
    if(es_palindromo(cad))
        printf("La cadena es palindromo");
    else
        printf("La cadena no es palindromo");
    return 0;
}
