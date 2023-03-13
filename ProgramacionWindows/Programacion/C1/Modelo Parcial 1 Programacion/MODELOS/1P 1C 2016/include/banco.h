#ifndef BANCO_H_INCLUDED
#define BANCO_H_INCLUDED
#include<stdio.h>
#include<tipos.h>
#include<lista.h>

void actualizar_cuentas(FILE * arch_ctas, FILE * arch_movs, FILE * arch_err, t_lista *plista);
void actualizar_cuentas_res(FILE * arch_ctas, FILE * arch_movs, FILE * arch_err, t_lista *plista);
int validar_nro_cuenta(const t_movimiento_banco * c1);
int validar_nro_cuenta_res(const t_movimiento_banco * c1);

#endif // BANCO_H_INCLUDED
