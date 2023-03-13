#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int Obtener_clave(char *cad);

int main()
{
    char cad[]= {"ab--ab++ab"};
    char linea[56]= {"ccC++d-- aRRarRa"};
    char linea2[56] = {"+++___**+"};
    char linea3[56] = {"ab++ab--ab"};
    char linea4[56]= { "abab"};

    printf("CALVE OFUSCADA: %s\n",cad);
    while(Obtener_clave(cad)) {}
    printf("CLAVE: %s\n",cad);
    printf("CALVE OFUSCADA: %s\n",linea);
    while(Obtener_clave(linea)) {}
    printf("CLAVE: %s\n",linea);

    printf("CALVE OFUSCADA: %s\n",linea2);
    while(Obtener_clave(linea2)) {}
    printf("CLAVE: %s\n",linea2);

    printf("CALVE OFUSCADA: %s\n",linea3);
    while(Obtener_clave(linea3)) {}
    printf("CLAVE: %s\n",linea3);

    printf("CALVE OFUSCADA: %s\n",linea4);
    while(Obtener_clave(linea4)) {}
    printf("CLAVE: %s\n",linea4);


    return 0;
}
int Obtener_clave(char *cad)
{
    char*aux=cad;
    char *inicio=cad;
    aux++;
    while(*inicio)
    {
        if(aux-1==inicio&&tolower(*aux)==tolower(*inicio))
        {
            inicio=aux+1;
            aux=inicio+1;
        }
        *cad=*inicio;
        cad++;
        inicio++;
        aux=inicio;
        aux++;
    }
    if((inicio>cad))
    {
        *cad='\0';
        return 1;
    }
    else
        return 0;

}
