#ifndef EXCEPTIONLLAMADA_H_INCLUDED
#define EXCEPTIONLLAMADA_H_INCLUDED

#include <iostream>
using namespace std;

class ExceptionLLamada : public exception
{
public:
    ExceptionLLamada() throw() : exception(){}
    const char *what() throw()
    {
        return "No se puede realizar la operacion solicitada, no coinciden los numeros de origen";
    }
};

#endif // EXCEPTIONLLAMADA_H_INCLUDED
