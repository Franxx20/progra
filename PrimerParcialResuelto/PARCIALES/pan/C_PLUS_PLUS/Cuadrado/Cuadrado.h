#ifndef CUADRADO_H
#define CUADRADO_H

#include "iostream"

using namespace std;

class Cuadrado
{
    private:
        float lado;
    public:
        Cuadrado();
        Cuadrado( const Cuadrado& otroCuadrado );
        Cuadrado( Cuadrado& otroCuadrado );
        virtual ~Cuadrado();

        float getLado() const;

        friend ostream& operator <<( ostream& out, const Cuadrado& cuadrado );
};

#endif // CUADRADO_H
