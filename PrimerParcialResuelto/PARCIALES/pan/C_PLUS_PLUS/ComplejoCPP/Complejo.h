#ifndef COMPLEJO_H
#define COMPLEJO_H

#include "iostream"

using namespace std;

class Complejo
{
    private:
        int real;
        int imaginario;
    public:
        Complejo();
        Complejo( int real, int imaginario );

        virtual ~Complejo();

        Complejo operator +( const Complejo& compOp );
        friend Complejo operator *( const int escalar, const Complejo& compOp );
        friend Complejo operator *( const Complejo& compOp1,  const Complejo& compOp2 );
        Complejo& operator =( const Complejo& compIg );

        friend ostream& operator <<( ostream& out, const Complejo& comp );
};

#endif // COMPLEJO_H
