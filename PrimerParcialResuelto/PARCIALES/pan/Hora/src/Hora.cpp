#include "Hora.h"
#include <iomanip>


Hora::Hora(int seg)
{
    ///86400 es el tope
    ///172.799

    ///seg %= 3600*24+1;
    seg %= 3600*24;

    this->horas = seg/(3600);
    this->minutos = (seg%3600)/60;
    this->segundos = (seg%3600)%60;

}

Hora::Hora()
{
    this->horas = 0;
    this->minutos = 0;
    this->segundos = 0;
}

Hora& Hora::operator = (const Hora& otro)
{
    this->horas = otro.horas;
    this->minutos= otro.minutos;
    this->segundos = otro.segundos;

    return *this;
}

Hora Hora::operator + (Hora& otro) const
{
    int temp;
    temp = (otro.horas + this->horas)*3600 + (otro.minutos + this->minutos)*60 + (otro.segundos + this->segundos);
    Hora horaTemp(temp);
    return horaTemp;
}

Hora Hora::operator ++ ()
{
    int temp;
    temp = (this->horas)*3600 + (this->minutos)*60 + (this->segundos);
    temp+=1;
    Hora horaTemp(temp);
    return horaTemp;
}


ostream& operator << (ostream& sal, const Hora& otro)
{
    return sal << setfill('0') << setw(2) << otro.horas << ":" << setfill('0') << setw(2) << otro.minutos << ":" << setfill('0') << setw(2) << otro.segundos;
}






