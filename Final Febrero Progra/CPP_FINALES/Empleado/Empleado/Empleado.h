#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

#include "Persona.h"
#include "EdadEmpleadoInvalidaException.h"

class Empleado : public Persona
{
private:
    string _Legajo;
public:
    Empleado(const string nombre,const unsigned int edad,const string legajo);
    const string getLegajo()const;
};

#endif // EMPLEADO_H_INCLUDED
