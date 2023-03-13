#ifndef BANCO_H_INCLUDED
#define BANCO_H_INCLUDED
#include<stdio.h>
#include<tipos.h>

void actualizar_stock(FILE * arch_libros, FILE * arch_stock, FILE * arch_err);

//int isbn_valido_res(const char * isbn);
int isbn_valido(const char * isbn);

//int cmp_stock_libro_res(const t_libro * l1, const t_libro * l2);
int cmp_stock_libro(const t_libro * l1, const t_libro_stock * l2);

#endif // BANCO_H_INCLUDED
