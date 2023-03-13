#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED
#include<banco.h>
#include<stdio.h>
#define TAM_LINEA 50

void crear_archivo_cuentas_res(const char * path);
void crear_archivo_movimientos_res(const char * path, const char * clave);

void mostrar_archivo_cuentas_res(const char * path);
void mostrar_archivo_movimientos_res(const char * path, const char * clave);
void mostrar_archivo_movimientos_descubierto_res(const char * path);

void texto_a_movimiento_res(const char * cadena,t_movimiento_banco * pmov);
void texto_a_movimiento(const char * cadena,t_movimiento_banco * pmov);

char * encriptar_res (char * cad, const char * clave);
char * encriptar (char * cad, const char * clave);

char * desencriptar_res (char * cad, const char * clave);
char * desencriptar (char * cad, const char * clave);

int leer_movimiento_res(t_movimiento_banco * mov, FILE * arch_mov, const char * clave);
int leer_movimiento(t_movimiento_banco * mov, FILE * arch_mov, const char * clave);

#endif // UTILITARIAS_H_INCLUDED
