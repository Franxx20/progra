#ifndef ACTAS_H_INCLUDED
#define ACTAS_H_INCLUDED
#include<tipos.h>
#include<stdio.h>

void generar_acta(const char * path_alus, const char * arch_notas, const char * arch_acta, const char * arch_obs);
void generar_acta_res(const char * path_alus, const char * arch_notas, const char * arch_acta, const char * arch_obs);

void calcular_nota_final_res(t_acta *a);
void calcular_nota_final(t_acta *a);

void validar_nota_final_res(const t_acta *a, FILE * arch_obs);
void validar_nota_final(const t_acta *a, FILE * arch_obs);

#endif // BANCO_H_INCLUDED
