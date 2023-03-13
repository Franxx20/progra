#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include <iostream>

using namespace std;

class Persona
{
private:
    string _Nombre;
    unsigned int _Edad;
public:
    Persona(const string nombre,const unsigned int edad);
    virtual ~Persona();
    const string GetNombre()const;
    const unsigned int GetEdad()const;
};

#endif // PERSONA_H_INCLUDED
