#include "Hora.h"
#include <iomanip>
Hora::Hora(){
    this->segundos = 0;
    this->minutos = 0;
    this->horas = 0;
}
Hora::Hora( int segundos ){
    // 1 hora son 3600 segundos
    this->segundos =  segundos % 60;
    this->minutos = ( segundos % 3600 ) / 60;
    int horasTemp = segundos / 3600;

    if( horasTemp >=24 ){
        this->horas = horasTemp - 24;
    } else{
        this->horas = horasTemp;
    }

}
Hora::Hora( Hora& hora ){
    this->segundos =  hora.segundos;
    this->minutos = hora.minutos;
    this->horas = hora.horas;
}

Hora::~Hora()
{
    //dtor
}

Hora Hora ::operator + ( const Hora& sumador ){
    int sumaSegOp1 = this->segundos + (this->minutos * 60) + (this->horas * 3600);
    int sumaSegOp2 = sumador.segundos + (sumador.minutos * 60) + (sumador.horas * 3600);
    Hora sumaHora ( sumaSegOp1+sumaSegOp2 );

    return sumaHora;
}
Hora& Hora ::operator = ( const Hora& horaOrigen ){
    this->segundos =  horaOrigen.segundos;
    this->minutos = horaOrigen.minutos;
    this->horas = horaOrigen.horas;

    return *this;
}
Hora Hora ::operator ++ (){
    int preIncr = (this->segundos + (this->minutos * 60) + (this->horas * 3600)) + 1;
    Hora preHora( preIncr );

    return preHora;
}

Hora Hora::operator ++ (int){
    Hora tempHora(*this);

    this->segundos++;
    if( this->segundos > 59 ){
        this->segundos = 0;
        this->minutos++;

        if( this->minutos > 59 ){
            this->minutos = 0;
            this->horas++;

            if( this->horas > 23 ){
            this->horas = 0;
            }
        }
    }
    return tempHora;
}

ostream& operator << ( ostream& out, const Hora& hora ){
    return out
              << setfill('0') << setw(2) << hora.horas << ":"
              << setfill('0') << setw(2) << hora.minutos << ":"
              << setfill('0') << setw(2) << hora.segundos;
}
