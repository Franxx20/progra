#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED
#include<banco.h>
#define TAM_LINEA 50
#define TAM_LINEA_MOV 19

void crear_archivo_cuentas(const char * path);
void crear_archivo_movimientos(const char * path, const char * clave);

void mostrar_archivo_cuentas(const char * path);
void mostrar_archivo_movimientos(const char * path, const char * clave);
void mostrar_archivo_errores(const char * path);


void texto_a_movimiento_res(const char * cadena,t_movimiento_banco * pmov);
void texto_a_movimiento(const char * cadena,t_movimiento_banco * pmov);

int buscarPosicion(const char* cad, char letra);
void sumarPalabraClave(char* cad, const char* palabraClave);
void restarPalabraClave(char* cad, const char* palabraClave);
void decodificarRegistro(char* registro, int posRegistro, const char* palabraClave);
void invertirCadena(char* ini, char* fin);
int miStrlen(const char* cad);
void operarSaldos(t_cuenta_banco *cuenta, FILE *pfMov, const char* clave);
int compararNroCuenta(const char* nroCuentaBanco, const char* nroCuentaMov);
#endif // UTILITARIAS_H_INCLUDED
