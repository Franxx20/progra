#ifndef UNIVERSALLIBRARY_H_INCLUDED
#define UNIVERSALLIBRARY_H_INCLUDED

typedef enum { FALSO, VERDADERO } booleano;
void clean_stdin(void);
booleano continuar(const char *mensaje);
char menuSinError(const char *msj, const char *opc);
char menuConError(const char *msj, const char *opc);

#endif // UNIVERSALLIBRARY_H_INCLUDED
