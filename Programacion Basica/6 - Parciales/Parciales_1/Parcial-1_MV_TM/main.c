#include <stdio.h>
#include "include/pila.h"
#include "include/descifrar.h"
#include "include/my_strings.h"

int main(int argc, char *argv[])
{
    FILE *ofsFile,
		 *newFile;

    char str[SIZE];
    int maxLenght = 0;

    tPila pila;

    if(argc < 3) {
		return 1;
    }

	ofsFile = fopen(argv[1], "rt");
	newFile = fopen(argv[2], "wt");

	if(!ofsFile || !newFile) {
		printf("[ERROR] No se pudo abrir archivo %s\n",
				(ofsFile)? argv[2] : argv[1]);
		return -1;
	}

    crearPila(&pila);

    while(fgets(str, sizeof(str), ofsFile)) {

		str[str_cspn(str, "\r\n")] = 0;
        descifrarLinea(str, &maxLenght, &pila);
        fprintf(newFile, "%s\n", str);

    }

    while(!pilaVacia(&pila)) {
		char aux[51];
		sacarDePila(&pila, &aux, sizeof(aux));
		puts(aux);
    }

    fclose(ofsFile);
    fclose(newFile);

    return 0;
}
