#ifndef EDADEMPLEADOINVALIDAEXCEPTION_H_INCLUDED
#define EDADEMPLEADOINVALIDAEXCEPTION_H_INCLUDED
#include <iostream>
using namespace std;

class EdadEmpleadoInvalidaException : public exception
{
public:
    EdadEmpleadoInvalidaException () throw() :exception () {}
    const char *what() throw()
    {
        return "El empleado debe tener una edad entre 18 y 65 inclusive";
    }
};

#endif // EDADEMPLEADOINVALIDAEXCEPTION_H_INCLUDED
