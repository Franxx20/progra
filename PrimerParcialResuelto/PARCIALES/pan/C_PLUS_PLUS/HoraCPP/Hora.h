#ifndef HORA_H
#define HORA_H

#include <iostream>

using namespace std;

class Hora
{
    private:
        int horas;
        int minutos;
        int segundos;
    public:
        Hora();
        Hora( int segundos );

        Hora operator +( const Hora& horaSum );
        Hora operator ++( );
        Hora& operator =( const Hora& horaOrigen );

        Hora& correccionValores();

        friend ostream& operator <<( ostream& out, const Hora& hora );
};


#endif // HORA_H
