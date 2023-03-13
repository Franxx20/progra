#ifndef NODO_H
#define NODO_H

#include <stddef.h>


typedef struct SNodo
{
	void* dato;
	size_t tamElem;
	struct SNodo* sig;
}
Nodo;


#endif // NODO_H
