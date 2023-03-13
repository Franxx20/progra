// MARCO_AGUSTIN_41572925
#include <string.h>
#include "Cadena.h"

#define ES_MAYUS(X)     ((X) >= 'A' && (X) <= 'Z')
#define ES_MINUS(X)     ((X) >= 'a' && (X) <= 'z')
#define ES_ESPACIO(X)   ((X) == ' ')
#define AMAYUS(X)       ((ES_MINUS(X))? ((X) - 32) : (X))

Cadena::Cadena(const char *cad)
{
    tam = strlen(cad);
    str = new char[tam+1];

    memcpy(str, cad, tam);
    str[tam] = '\0';
}


Cadena::~Cadena()
{
    delete []str;
}


int Cadena::primeraAparicion(const char c)
{
    int pos = 0;
    char *aux = str;

    while(*aux && *aux != c) {
        aux++;
        pos++;
    }

    if(*aux == '\0') {
        pos = -1;
    }

    return pos;
}


Cadena Cadena::operator ()(const int& li, const int& ls)
{
    int l_size = (ls - li)+1;
    char aux[l_size+1];

    memcpy(aux, str+li, l_size);
    aux[l_size] = '\0';

    return Cadena(aux);
}


Cadena Cadena::aMayusculas()
{
    char aux[tam+1];
    memcpy(aux, str, tam);
    aux[tam] = '\0';
    for(unsigned i = 0; i < tam; i++) {
        aux[i] = AMAYUS(aux[i]);
    }
    return Cadena(aux);
}


Cadena Cadena::podarIzquierda()
{
    char *aux = str;

    while(*aux && ES_ESPACIO(*aux)) {
        aux++;
    }
    return Cadena(aux);
}


std::ostream& operator <<(std::ostream& out, const Cadena& cad)
{
    out << cad.str;
    return out;
}

