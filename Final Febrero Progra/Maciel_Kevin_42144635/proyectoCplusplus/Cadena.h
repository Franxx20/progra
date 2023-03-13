#ifndef CADENA_H_INCLUDED
#define CADENA_H_INCLUDED
///Maciel_Kevin_42144635
#include <string.h>
#include <iostream>
using namespace std;

class Cadena
{
private:
    char *_cadena;
public:
    Cadena();
    Cadena(const char *cad);
    Cadena(const Cadena &obj);

    Cadena& operator = (const char * cad);
    Cadena& operator = (const Cadena &obj);
    Cadena& operator + (const char *cad);
    friend ostream& operator << (ostream &o, const Cadena &obj);
    ~Cadena();
};

#endif // CADENA_H_INCLUDED
