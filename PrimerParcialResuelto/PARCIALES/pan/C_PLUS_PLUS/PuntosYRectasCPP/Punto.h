#ifndef PUNTO_H
#define PUNTO_H

#include "ostream"

using namespace std;

class Punto
{
    private:
        double x;
        double y;
    public:
        Punto();
        Punto( double x, double y );

        double getX() const ;
        double getY() const ;

        virtual ~Punto();

        friend ostream& operator <<( ostream& out, const Punto& punto );

};

#endif // PUNTO_H
