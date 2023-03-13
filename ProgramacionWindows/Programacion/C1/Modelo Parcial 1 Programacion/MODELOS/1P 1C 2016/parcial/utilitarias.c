#include <stdio.h>
#include <string.h>
#include <utilitarias.h>
#include <banco.h>
#include <stdlib.h>

void texto_a_movimiento(const char * cad,t_movimiento_banco * pmov)
{
    sscanf(cad,"%s|%c|%f",pmov->cod_cta,pmov->tipo_mov,pmov->importe);
}

