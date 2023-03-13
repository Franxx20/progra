#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

#define MIN(a,b) ((a)<(b)?(a):(b))
#define SIN_MEM -1
#define TODO_OK 0
#define DUPLICADO -2
#define SIN_NODOS -5
#define ERR_ARCHIVO -6
#define ERR_LIMITES -7

typedef void (*Mostrar) (const void * dato, int nivel);
typedef int (*Cmp) (const void * d1,const void * d2);
typedef void (*Actualizar) (void *actualizado, void * actualizador);

#endif
