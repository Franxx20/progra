#ifndef MEDICION_H_INCLUDED
#define MEDICION_H_INCLUDED

#include "Medicionexception.h"
#include <iostream>
using namespace std;

class Medicion
{
private:
    float _Volt;
    string _Tipo;
public:
    Medicion(const float volt,const string tipo);
    Medicion();
    Medicion& operator-(const Medicion &obj);
    friend ostream& operator<<(ostream& sal,const Medicion &obj);
    friend Medicion operator+(const float volt,const Medicion & obj);
};

#endif // MEDICION_H_INCLUDED
