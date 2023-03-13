#ifndef CADENA_H_INCLUDED
#define CADENA_H_INCLUDED

#include <iostream>
#include <string.h>
using namespace std;
class Cadena
{
private:
    char *_cad;
public:
    Cadena(const char *cad);
    Cadena(const Cadena &obj);
    Cadena();
    ~Cadena();
    const unsigned int longitud()const;
    Cadena& operator=(const char *cad);
    Cadena& operator=(const Cadena &obj);
    Cadena operator+(const char *cad)const;
    Cadena operator+(const Cadena &obj)const;
    friend ostream& operator<<(ostream& sal,const Cadena& obj);
    friend istream& operator>>(istream &sal,Cadena &obj);
    friend Cadena operator+(const char *cad,const Cadena &obj);
};

#endif // CADENA_H_INCLUDED
