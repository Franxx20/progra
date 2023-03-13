#include "HoraDelDia.h"

HoraDelDia::HoraDelDia()
{
    this->horas = 0;
    this->minutos = 0;
    this->segundos = 0;
}

HoraDelDia::HoraDelDia(int h, int m, int s)
{
    this->horas = h;
    this->minutos = m;
    this->segundos = s;

    if(this->segundos > 59)
    {
        this->segundos -=60;
        this->minutos++;
    }
    if(this->minutos > 59)
    {
        this->minutos -= 60;
        this->horas++;
    }
    if(this->horas > 23)
        this->horas-=24;
}

HoraDelDia HoraDelDia::getHoraMaxima()
{
    return HoraDelDia(23,59,59);
}

int HoraDelDia::operator<(const HoraDelDia& dia1)
{
    if(this->horas == dia1.horas)
        if(this->minutos == dia1.minutos)
            return this->segundos<dia1.segundos?1:0;
        else
            return this->minutos<dia1.minutos?1:0;
    else
        return this->horas<dia1.horas?1:0;
}

int HoraDelDia::operator>=(const HoraDelDia& dia1)
{
    if(this->horas == dia1.horas)
        if(this->minutos == dia1.minutos)
            return this->segundos>=dia1.segundos?1:0;
        else
            return this->minutos>=dia1.minutos?1:0;
    else
        return this->horas>=dia1.horas?1:0;
}

HoraDelDia HoraDelDia::operator++(int a)
{
    HoraDelDia horaAnterior(this->horas,this->minutos,this->segundos);

    this->segundos++;
    if(this->segundos > 59)
    {
        this->segundos-=60;
        this->minutos++;
    }
    if(this->minutos > 59)
    {
        this->minutos-=60;
        this->horas++;
    }
    if(this->horas > 23)
        this->horas-=24;

    return horaAnterior;
}

HoraDelDia operator+(const int s, const HoraDelDia& dia)
{
    return HoraDelDia(dia.horas,dia.minutos,dia.segundos+s);
}

HoraDelDia& HoraDelDia::operator+=(const int segundos)
{
    this->segundos += segundos;
    if(this->segundos > 59)
    {
        this->segundos-=60;
        this->minutos++;
    }
    if(this->minutos > 59)
    {
        this->minutos-=60;
        this->horas++;
    }
    if(this->horas > 23)
        this->horas-=24;

    return *this;
}

HoraDelDia HoraDelDia::operator+(const HoraDelDia& dia)
{
    return HoraDelDia(this->horas+dia.horas,this->minutos+dia.minutos,this->segundos+dia.segundos);
}

HoraDelDia& HoraDelDia::operator=(const HoraDelDia& dia)
{
    this->horas = dia.horas;
    this->minutos = dia.minutos;
    this->segundos = dia.segundos;

    return *this;
}

ostream& operator<<(ostream& os, const HoraDelDia& dia)
{
    os << dia.horas <<":"<<dia.minutos<<":"<<dia.segundos;
    return os;
}
istream& operator>>(istream& in, HoraDelDia& dia)
{
    in >> dia.horas;
    in >> dia.minutos;
    in >> dia.segundos;

    return in;
}
