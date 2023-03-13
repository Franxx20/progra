#ifndef RECTA_H
#define RECTA_H

#include "float.h"
#include "stdlib.h"
#include "math.h"
#include "Punto.h"

using namespace std;

class Recta
{
    private:
        Punto iniRec; //(x,y)
        Punto finRec;
    public:

        Recta();
        Recta( const Punto& iniRec, const Punto& finRec );

        Punto operator &&( const Recta& rect2 );
        double operator -( const Punto& punto );

        double obtPendiente( );
        float obtIndependiente( );

        friend ostream& operator <<( ostream& out, const Recta& recta );
};

#endif // RECTA_H
