#ifndef BANCO_H_INCLUDED
#define BANCO_H_INCLUDED
#include<stdio.h>
#include<tipos.h>
#include<lista.h>

void actualizar_cuentas(FILE * arch_ctas, const char * path_movs, const char * clave);
void actualizar_cuentas_res(FILE * arch_ctas, const char * path_movs, const char * clave);

#endif // BANCO_H_INCLUDED
