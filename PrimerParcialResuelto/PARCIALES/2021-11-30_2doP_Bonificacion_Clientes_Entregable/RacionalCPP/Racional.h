#ifndef RACIONAL_H
#define RACIONAL_H

#include "ostream"

using namespace std;

class Racional
{
    private:
        int numerador;
        int denominador;

    public:
        Racional( );
        Racional( int numerador, int denominador );

        void racionalIrreducible( int *numerador, int *denominador );
        float real( );

        Racional& operator =( Racional racOrigen );
        Racional operator *( Racional racProducto );
        Racional operator +( Racional racSumador );

        friend Racional operator +( const int entero, const Racional& racional );
        friend ostream& operator <<( ostream& out, const Racional& racional );

};

#endif // RACIONAL_H
