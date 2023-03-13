#include <stdio.h>
#include <stdlib.h>
#include "../include/virus.h"
#include "../include/my_strings.h"


int main(int argc, char *argv[])
{
    tPila tamBloques;
    char str[SIZE];
    FILE* fp;

    if(argc < 3) {
        puts("./virus <archivo> <separadores>");
        return 1;
    }

    if( !(fp = fopen(argv[1], "r+t")) ) {
        printf("[ERROR] - No se pudo abrir el archivo %s\n", argv[1]);
        return -1;
    }

    crearPila(&tamBloques);


    while(fgets(str, sizeof(str), fp)) {

		/* Removemos el salto de linea */
        str[str_cspn(str, "\n")] = '\0';

        separarPorBloques(str, argv[2], &tamBloques);
        daniarBloque(str, argv[2], &tamBloques);

        /* Re-escribimos la linea en el archivo */
        fseek(fp, -1L * (str_len(str) + 1), SEEK_CUR);
        fprintf(fp, "%s\n", str);
        fseek(fp, 0, SEEK_CUR);

        /* Solo para asegurarnos */
        puts(str);
    }


    fclose(fp);
    vaciarPila(&tamBloques);
    return 0;
}


void separarPorBloques(char *str, char *separadores, tPila *tamBloques)
{
    char *p_aux = str_ntok(str, separadores);

    do {

        int tam = str_len(p_aux);

        if(tam && !pilaLlena(sizeof(int))) {
            ponerEnPila(tamBloques, &tam, sizeof(int));
        }

        /* Hay que liberar el puntero cada vez que se usa
		 * str_ntok */
        free(p_aux);

    } while( (p_aux = str_ntok(NULL, separadores)) );
}


void daniarBloque(char *str, char *separadores, tPila *tamBloques)
{
    int offset, i, desp;
    char *p_len, *p_aux = str_ntok(str, separadores);

    do {

		/* Si la cadena esta vacia saltamos,
		 * La cadena puede estar vacia debido a
		 * tener varios separadores juntos */
        if(*p_aux == '\0') {
			free(p_aux);
			continue;
        }

        if(pilaVacia(tamBloques)) {
            break;
        }

        sacarDePila(tamBloques, &offset, sizeof(int));

        /* Calculamos la posicion del bloque a editar
         * en la cadena original */
        p_len = str_str(str, p_aux);
        desp = p_len - str;

        i = 0;

        while(*(p_aux + i)) {

            if(ESLETRA(*(p_aux + i))) {
                *(p_aux + i) = daniarCaracter(*(p_aux + i), offset);
            }
            i++;
        }

        /* Copiamos el bloque modificado devuelta a la cadena */
        mem_move(str + desp, p_aux, i);

        free(p_aux);

    } while( (p_aux = str_ntok(NULL, separadores)) );
}


/*char daniarCaracter(char c, int offset)
{
    char rc = c - offset;

    if(rc < 'A') {
        rc = 'z' + ((c - 'A') - offset) + 1;
    }

    if( (c > 'a' && rc <= 'Z') || (rc < 'a' && rc > 'Z') ) {
        rc -= ('a' - 'Z') - 1;
    }

    return rc;
}*/

char daniarCaracter(char c, int offset)
{
    static const char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int i;

    for(i = 0; i < str_len(abc); i++) {
        if(c == *(abc + i)) {
            break;
        }
    }

    i -= offset;
    while(i < 0) {
        i += str_len(abc);
    }

    return *(abc + i);
}


