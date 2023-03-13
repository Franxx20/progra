#include "Persona.h"

Persona::Persona(const string nombre,const unsigned int edad)
{
    _Nombre=nombre;
    _Edad=edad;
}
Persona::~Persona()
{
}
const string Persona::GetNombre()const
{
    return _Nombre;
}
const unsigned int Persona::GetEdad()const
{
    return _Edad;
}
