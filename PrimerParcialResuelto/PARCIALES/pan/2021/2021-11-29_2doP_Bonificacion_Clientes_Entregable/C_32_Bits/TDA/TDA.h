#ifndef TDA_H
#define TDA_H


#define reservarMemoriaNodo(nodo, tamNodo, tamElem) \
( ( (nodo) = (typeof(nodo) ) malloc(tamNodo) ) == NULL || ( (nodo)->elem = malloc(tamElem) ) == NULL ? free(nodo), 0 : 1)


#endif // TDA_H
