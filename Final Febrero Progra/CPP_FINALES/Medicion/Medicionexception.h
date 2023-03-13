#ifndef MEDICIONEXCEPTION_H_INCLUDED
#define MEDICIONEXCEPTION_H_INCLUDED

#include <iostream>
using namespace std;

class Medicionexception : public exception
{
public:
    Medicionexception() throw() : exception() {}
    const char *what() throw()
    {
        return "NO SE PUEDE RESTAR EN DISTINTAS UNIDADES DE MEDIDA";
    }
};

#endif // MEDICIONEXCEPTION_H_INCLUDED
