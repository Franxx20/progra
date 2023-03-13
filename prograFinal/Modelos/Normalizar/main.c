#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

#define ESMIN(a) ((a) >= 'a' && (a) <='z')
#define ESMAY(a) ((a) >= 'A' && (a) <= 'Z')
#define ESLETRA(a) (ESMIN(a) || ESMAY(a)? (1) : (0) )



int normalizarCadena(char * cad);
char * normalizarPalabra(char * aux, char * normalizada,unsigned * cantCaracteres,int * primeraPalabra);

int main()
{
    char cad[] = "       hOla.   esta eS LA caDenA.    ";
    int cantPalabras =0;
    printf("sizeof %d strlen %d\n",(int)sizeof(cad),(int)strlen(cad));
    printf("cadena original %s", cad);
    cantPalabras =normalizarCadena(cad);
    printf("\ncadena normalizada %s cantPalabras %d",cad,cantPalabras);


    return 0;
}


int  normalizarCadena(char * cad)
{
    int cantPalabras = 0;
    unsigned cantCaracteres  =0;
    int primeraPalabra = 1;
    char * normalizada = (char*)malloc(strlen(cad)+1);
    char * aux = cad;

    if(!*aux)
        return cantPalabras;

    while(*aux)
    {
        while(*aux == ' ')
            aux ++;

        if(ESLETRA(*aux))
        {
            aux = normalizarPalabra(aux,normalizada,&cantCaracteres,&primeraPalabra);
            cantPalabras++;
        }

    }

    strcpy(cad,normalizada);
    free(normalizada);




    return cantPalabras;
}

char *  normalizarPalabra(char * aux, char * normalizada,unsigned * cantCaracteres,int * primeraPalabra)
{
    normalizada+= *cantCaracteres;

    if(*normalizada == '\0')
    {
        *normalizada = ' ';
        normalizada++;
        (*cantCaracteres)++;

    }


    if(ESLETRA(*aux) && *primeraPalabra == 1)
    {
            *normalizada = toupper(*aux);
            *primeraPalabra =0;
    }
    else
        *normalizada = *aux;

    normalizada++;
    (*cantCaracteres)++;
    aux++;

    while(*aux!= ' ' && *aux != '\0')
    {
        if(ESLETRA(*aux))
            *normalizada = tolower(*aux);
        else
            *normalizada = *aux;

        normalizada++;
        (*cantCaracteres)++;
        aux++;
    }

    *normalizada =  '\0';


    return aux;
}


