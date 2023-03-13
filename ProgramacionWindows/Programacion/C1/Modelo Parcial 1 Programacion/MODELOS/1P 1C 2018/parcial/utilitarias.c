#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <utilitarias.h>
#include <banco.h>

void texto_a_movimiento(const char * cadena,t_movimiento_banco * pmov)
{
    char* pos = strchr(cadena, '\n');
    if(!pos)
        return;

    pos = '\0';

///saldo

    pos -= 9;
    sscanf(pos, "%f", &pmov->importe);
    pos = '\0';

///movimiento

    pos -= 1;
    sscanf(pos, "%c", &pmov->tipo_mov);
    pos = '\0';

///codCta

    strcpy(pmov->cod_cta, cadena);
}
