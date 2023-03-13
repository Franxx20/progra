#include <iostream>


#include "Hora.h"

using namespace std;

Hora::Hora()
{
    this->horas = 0;
    this->minutos = 0;
    this->segundos =0;
}
Hora::Hora(Hora & otro)
{
    this->horas = otro.horas;
    this->minutos =otro.minutos;
    this->segundos = otro.segundos;
}

Hora::Hora (int segundos)
{
    this->horas = (segundos/3600) % 24; // 1h
    this->minutos = (segundos%3600)/60; //1 m
    this->segundos = (segundos%3600)%60; //40s
}
Hora::~Hora()
{

}


Hora Hora::operator++(int)  // postIncremento HORA++
{
    Hora horaAnterior(*this);

    this->segundos++;
    this->correcionValores();
    return horaAnterior;
}

Hora&Hora:: operator++() // preIncremento ++HORA
{
    ++this->segundos;
    this->correcionValores();
    return *this;
}

Hora& Hora::operator=(const Hora & otro)
{
    this->horas = otro.horas;
    this->minutos = otro.minutos;
    this->segundos = otro.segundos;

    return *this;
}

Hora Hora::operator+(const Hora & otro)
{

    int segundosIzq = this->horas* 3600 + this->minutos * 60 + this->segundos;
    int segundosDer = otro.horas * 3600 + otro.minutos * 60 + otro.segundos;

    Hora horaNueva(segundosDer + segundosIzq);



    horaNueva.correcionValores();

    return horaNueva;
}

Hora& Hora::correcionValores()
{
    if(this->segundos>59)
    {
        this->segundos=0;
        this->minutos++;
    }
    if(this->minutos>59)
    {
        this->minutos =0;
        this->horas++;
    }
    if(this->horas > 23)
        this->horas = 0;

    return *this;
}

ostream& operator<<(ostream & out,const Hora & hora)
{
    out <<  hora.horas <<":" << hora.minutos << ":" << hora.segundos ;
    return out;
}
