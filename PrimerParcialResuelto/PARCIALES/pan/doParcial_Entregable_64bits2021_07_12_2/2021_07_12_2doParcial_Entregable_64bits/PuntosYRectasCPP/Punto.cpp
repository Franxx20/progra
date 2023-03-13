#include <math.h>

#include "Punto.h"

Punto::Punto(double x, double y)
: x(x), y(y)
{}

ostream& operator <<(ostream& os, const Punto p1)
{
    return os<<'('<< p1.x << ','<<p1.y<<')';

}

