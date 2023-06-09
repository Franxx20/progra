#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED
#include<tipos.h>
#define TAM_LINEA 50

void crear_archivo_alumnos(const char * path);

void mostrar_archivo_alumnos(const char * path);
void mostrar_archivo_notas(const char * path);
void mostrar_archivo_acta(const char * path);
void mostrar_archivo_errores(const char * path);


void texto_a_nota_res(const char * cadena,t_nota * pnota);
void texto_a_nota(const char * cadena,t_nota * pnota);

int comparar(int dato1, int dato2); ///necesario para actas
int comp_info(const t_info *d1,const t_info *d2);

#endif // UTILITARIAS_H_INCLUDED
