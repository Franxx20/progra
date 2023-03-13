#include "tipos.h"
#include <string.h>
#include <stdio.h>

int comparar(int dato1, int dato2)
{
    return dato1-dato2;
}

int comp_info(const t_info *d1,const t_info *d2)
{
    return d1->dni-d2->dni;
}

void texto_a_nota(const char *cadena,t_nota *pnota)
{
    char aux[90];
    sscanf(cadena,"%8ld %2[^\n] %2d",&pnota->dni,aux,&pnota->nota);
    strncpy(pnota->tipo,aux,sizeof(pnota->tipo));
}
