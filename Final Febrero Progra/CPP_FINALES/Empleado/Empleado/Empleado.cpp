#include "Empleado.h"

Empleado::Empleado(const string nombre,const unsigned int edad,const string legajo)
    :Persona(nombre,edad),_Legajo(legajo)
{
    if(!(edad>=18&&edad<=65))
        throw EdadEmpleadoInvalidaException();
}
const string Empleado::getLegajo()const
{
    return _Legajo;
}
