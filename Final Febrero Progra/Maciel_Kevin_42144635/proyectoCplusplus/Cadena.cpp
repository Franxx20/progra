///Maciel_Kevin_42144635
#include "Cadena.h"

    Cadena::Cadena()
    {
        char *aux = new char[1];
        aux[0] = '\0';
        _cadena = aux;
    }

Cadena::Cadena(const char *cad)
{
    char *aux = new char[strlen(cad) + 1];
    strcpy(aux,cad);
    _cadena = aux;
}
Cadena::Cadena(const Cadena &obj)
{
    char *aux = new char[strlen(obj._cadena) + 1];
    strcpy(aux,obj._cadena);
    _cadena = aux;
}

Cadena& Cadena::operator = (const char * cad)
{
    char *aux = new char[strlen(cad) + 1];
    strcpy(aux, cad);
    delete[] _cadena;
    _cadena = aux;
    return *this;
}
Cadena& Cadena::operator = (const Cadena &obj)
{
    char *aux = new char[strlen(_cadena) + strlen(obj._cadena) + 1];
    strcpy(aux,_cadena);
    strcat(aux, obj._cadena);
    delete[] _cadena;
    _cadena = aux;
    return *this;
}
Cadena& Cadena::operator + (const char *cad)
{
    char *aux = new char[strlen(_cadena) + strlen(cad) + 1];
    strcpy(aux, _cadena);
    strcat(aux,cad);
    delete[] _cadena;
    _cadena = aux;
    return *this;
}

ostream& operator << (ostream &o, const Cadena &obj)
{
    o << obj._cadena;
    return o;
}

Cadena::~Cadena()
{
    delete[] _cadena;
}
