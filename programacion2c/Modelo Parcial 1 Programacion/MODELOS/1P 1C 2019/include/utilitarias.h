#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED
#include<biblioteca.h>

#include <string.h>

void crear_archivo_libros();
void crear_archivo_stock();

void mostrar_archivo_libros();
void mostrar_archivo_stock();
void mostrar_archivo_errores();


//void texto_a_stock_res(const char * cad,t_libro_stock * pstock);
void texto_a_stock(const char * cad,t_libro_stock * pstock);
#endif // UTILITARIAS_H_INCLUDED
