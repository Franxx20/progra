#ifndef HORA_H
#define HORA_H

#include <iostream>

using namespace std;

class Hora
{
    private:

        int segundos;
        int minutos;
        int horas;

    public:
        Hora();
        Hora( Hora& hora );
        Hora( int segundos );

        virtual ~Hora();

        Hora operator + ( const Hora& second );
        Hora& operator = ( const Hora& second );
        Hora operator ++ ( );
        Hora operator ++ (int);

    friend ostream& operator << ( ostream& out, const Hora& hora );
};


#endif // HORA_H
