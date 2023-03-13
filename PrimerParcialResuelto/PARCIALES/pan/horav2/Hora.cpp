#include "Hora.h"

Hora::Hora()
{
    this->segundos = 0;
    this->minutos = 0;
    this->horas = 0;

}
Hora::Hora( int segundos ){
    int horasTotales = segundos / 3600;
    if( horasTotales>23 ){
        this->horas = horasTotales - 24;
    } else {
        this->horas = horasTotales;
    }
    this->minutos = (segundos % 3600) /60;
    this->segundos = (segundos % 3600) %60;
}

Hora Hora::operator =(const Hora& horaIgualar){
    this->horas = horaIgualar.horas;
    this->minutos =  horaIgualar.minutos;
    this->segundos = horaIgualar.segundos;

    return (*this);
}
Hora Hora::operator +(const Hora& horaSumador){
    int segsOp1 = this->horas*3600 + this->minutos*60 + this->segundos;
    int segsOp2 = horaSumador.horas*3600 + horaSumador.minutos*60 + horaSumador.segundos;
    Hora sumaHora( segsOp1 + segsOp2 );

    return sumaHora;
}
//Pre-increment (++i) − Before assigning the value to the variable, the value is incremented by one.
Hora Hora::operator ++(){
    int segsInc = this->horas*3600 + this->minutos*60 + (this->segundos + 1);
    Hora horaAux (segsInc);
    return horaAux;
}
//Post-increment (i++) − After assigning the value to the variable, the value is incremented.

Hora::~Hora()
{
    //dtor
}

ostream& operator << (ostream& out, const Hora& hora){
    return out << hora.horas << ":" << hora.minutos << ":" << hora.segundos;
}
