#include <stdio.h>
#include <stdlib.h>
#include "cadenas.h"

int main()
{
    //  char cad []={"neuquen"}; SIN ESPACIOS
    char cad []={"Anita lava la tina"};
    if(esPalindromo(cad))
        printf(" %s Es palindromo \n",cad);
    else
        printf("%s No es palindromo idiota \n",cad);

    char sol[] = "nacionalista";
    char los[] = "altisonancias";

    printf("%s y %s son anagramas?\n",sol,los);
    if(sonAnagramas(sol, los))
        printf("Son anagramas\n");
    else
        printf("No son anagramas\n");

    return 0;
}
