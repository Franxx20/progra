#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED
#include<banco.h>
#define TAM_LINEA 50

void crear_archivo_cuentas(const char * path);
void crear_archivo_movimientos(const char * path);

void mostrar_archivo_cuentas(const char * path);
void mostrar_archivo_movimientos(const char * path);
void mostrar_archivo_errores(const char * path);


void texto_a_movimiento_res(const char * cadena,t_movimiento_banco * pmov);
void texto_a_movimiento(const char * cadena,t_movimiento_banco * pmov);
#endif // UTILITARIAS_H_INCLUDED
