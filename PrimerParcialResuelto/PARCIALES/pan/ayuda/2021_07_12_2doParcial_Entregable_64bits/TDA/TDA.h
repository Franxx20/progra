#ifndef TDA_H
#define TDA_H

#define VERDADERO	1
#define FALSO		0

#define TODO_OK		0
#define DUPLICADO	1
#define SIN_MEM		2

#define reservarMemoriaNodo(nodo, tamNodo, tamElem) \
( ( (nodo) = (typeof(nodo) ) malloc(tamNodo) ) == NULL || ( (nodo)->dato = malloc(tamElem) ) == NULL ? free(nodo), 0 : 1)


typedef int (*Cmp)(const void* e1, const void* e2);

typedef int (*Condicion)(const void* elem);

typedef void (*Actualizar)(void* actualizado, const void* actualizador);

typedef void (*Accion)(void* dato, void* datosAccion);


#endif // TDA_H
