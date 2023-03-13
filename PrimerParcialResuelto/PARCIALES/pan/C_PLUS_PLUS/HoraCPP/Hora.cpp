#include <iostream>
#include "Hora.h"

using namespace std;

Hora::Hora(){
    this->horas = 0;
    this->minutos = 0;
    this->segundos = 0;
}

Hora::Hora( int segundos ){
    this->horas = (segundos / 3600) % 24;
    this->minutos = (segundos % 3600) / 60;
    this->segundos = (segundos % 3600) % 60;
}

Hora Hora::operator +( const Hora& horaSum ){
    int sumSegsOp1 = this->horas*3600 + this->minutos*60 + this->segundos;
    int sumSegsOp2 = horaSum.horas*3600 + horaSum.minutos*60 + horaSum.segundos;
    Hora sumHora( sumSegsOp1+ sumSegsOp2 );

    sumHora.correccionValores();

    return sumHora;
}

Hora Hora::operator ++( ){
    //int incSegs = this->horas*3600 + this->minutos*60 + (this->segundos + 1);
    //Hora incHora ( incSegs );
    this->segundos++;
    this->correccionValores();

    return *this;
}

Hora& Hora::operator =( const Hora& horaOrigen ){
    this->horas = horaOrigen.horas;
    this->minutos = horaOrigen.minutos ;
    this->segundos = horaOrigen.segundos ;

    return *this;
}

Hora& Hora::correccionValores(){
    if( this->segundos > 59 ){
        this->segundos = 0;
        this->minutos++;
    }
    if( this->minutos > 59 ){
        this->minutos = 0;
        this->horas ++;
    }
    if( this->horas > 23 ){
        this->horas = 0;
    }

    return *this;
}

ostream& operator <<( ostream& out, const Hora& hora ){
    return out << hora.horas << ":" << hora.minutos << ":" << hora.segundos;
}
