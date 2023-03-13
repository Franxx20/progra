#include "HoraDelDia.h"

HoraDelDia::HoraDelDia()
{

    this->_tiempoEnSegundos = 0;
}

HoraDelDia::HoraDelDia(int hora,int minuto,int segundo)
{
    int horaEnSegundos = segundo + minuto  * MINUTOSEGUNDOS + hora*HORASEGUNDOS;
    if(horaEnSegundos > DIASEGUNDOS)
        horaEnSegundos %=  HORASEGUNDOS;

    this->_tiempoEnSegundos = horaEnSegundos;
}

HoraDelDia::HoraDelDia(int horaEnSegundos)
{
    if(horaEnSegundos > DIASEGUNDOS)
        horaEnSegundos %=HORASEGUNDOS;

    this->_tiempoEnSegundos = horaEnSegundos;
}

HoraDelDia::~HoraDelDia()
{
    //dtor
}

//HoraDelDia::HoraDelDia(const HoraDelDia& other)
//{
//    //copy ctor
//}

HoraDelDia& HoraDelDia::operator=(const HoraDelDia& otro)
{
    if (this == &otro) return *this; // handle self assignment
    //assignment operator

    unsigned horaEnSegundos = otro._tiempoEnSegundos;
    if(horaEnSegundos > DIASEGUNDOS)
        horaEnSegundos %=  HORASEGUNDOS;

    this->_tiempoEnSegundos = horaEnSegundos;

    return *this;
}

bool HoraDelDia::operator>= (const HoraDelDia & otro)const
{
    return this->_tiempoEnSegundos >= otro._tiempoEnSegundos;
}

bool HoraDelDia::operator< (const HoraDelDia & otro)const
{
    return this->_tiempoEnSegundos<otro._tiempoEnSegundos;
}

HoraDelDia HoraDelDia::operator+(const HoraDelDia & otro)const
{
    HoraDelDia nue(this->_tiempoEnSegundos+ otro._tiempoEnSegundos);

    return nue;


}
HoraDelDia& HoraDelDia::operator+=(int segundos)
{
    this->_tiempoEnSegundos+=segundos;
    if(this->_tiempoEnSegundos>DIASEGUNDOS);
    this->_tiempoEnSegundos%=HORASEGUNDOS;

    return *this;
}

HoraDelDia HoraDelDia::operator++(int)
{

    HoraDelDia anterior (this->_tiempoEnSegundos);
    ++this->_tiempoEnSegundos;

    return anterior;
}

void HoraDelDia::getHoraMinutoySegundo(int *h,int *m,int * s)const
{
    int horaEnSegundos;
    horaEnSegundos = this->_tiempoEnSegundos;

    *h  = horaEnSegundos/HORASEGUNDOS;
    horaEnSegundos%=(HORASEGUNDOS);

    *m = horaEnSegundos/(MINUTOSEGUNDOS);
    horaEnSegundos%=MINUTOSEGUNDOS;

    *s = horaEnSegundos;
}

HoraDelDia HoraDelDia::getHoraMaxima()
{
    HoraDelDia nue(DIASEGUNDOS -1);

    return nue;
}

ostream & operator<<(ostream & out, const HoraDelDia&otro)
{
    int hora,minuto,segundo;
    otro.getHoraMinutoySegundo(&hora,&minuto,&segundo);
    return out << "horas: "<<hora << " minutos: "<< minuto << " segundos: "<< segundo;

    return out;
}

istream & operator>>(istream & in,  HoraDelDia&otro)
{
    int hora,minuto,segundo;
    in >> hora >> minuto >> segundo;
    otro._tiempoEnSegundos = segundo + minuto * MINUTOSEGUNDOS + hora * HORASEGUNDOS;

//    return in >> otro._hora >> otro._minuto >> otro._segundo;

    return in;
}


HoraDelDia  operator+(int segundo, const HoraDelDia&otro)
{
    HoraDelDia nuevo(otro._tiempoEnSegundos+segundo);


    return nuevo;
}
