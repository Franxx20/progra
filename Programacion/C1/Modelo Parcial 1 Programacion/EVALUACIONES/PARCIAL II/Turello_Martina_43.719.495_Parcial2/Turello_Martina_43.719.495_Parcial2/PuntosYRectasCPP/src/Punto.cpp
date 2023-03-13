#include "Punto.h"

Punto::Punto()
{
    this->x = 0;
    this->y = 0;
}
Punto::Punto(double x, double y)
: x(x), y(y)
{}

void Punto::setPunto(double x, double y)
{
    this->x = x;
    this->y = y;
}

ostream& operator <<(ostream& sal, const Punto& p)
{
    return sal << '(' << p.getX() << ',' << p.getY() << ')';
}
