#include <math.h>

#include "Punto.h"
#include "Recta.h"

Recta::Recta(Punto p1, Punto p2)
: p1(p1), p2(p2)
{}

Punto Recta::operator &&(const Recta& otro) const
{
    Punto intersec;
    double x1,x2,x3,x4,y1,y2,y3,y4;
    x1=this->p1.getX();
    x2=this->p2.getX();
    y1=this->p1.getY();
    y2=this->p2.getY();
    x3=otro.p1.getX();
    x4=otro.p2.getX();
    y3=otro.p1.getY();
    y4=otro.p2.getY();

    intersec.setX(((x1*y2 - y1*x2)*(x3-x4)-(x1-x2)*(x3*y4 - y3*x4))/(((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4))));
    intersec.setY(((x1*y2 - y1*x2)*(y3-y4)-(y1-y2)*(x3*y4 - y3*x4))/(((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4))));

    return intersec;
}

double Recta::operator -(const Punto& otro) const
{
    double dist,x1,x2,y1,y2,x0,y0;

    x1=this->p1.getX();
    x2=this->p2.getX();
    y1=this->p1.getY();
    y2=this->p2.getY();
    x0= otro.getX();
    y0= otro.getY();
    dist = abs((y2-y1)*x0 - (x2-x1)*y0 + x2*y1 - y2*x1)/sqrt(pow((y2-y1), 2) + pow((x2-x1),2));

    return dist;
}

ostream& operator <<(ostream& os, const Recta r1)
{
    os<<'('<<r1.p1.getX() << ','<<r1.p1.getY()<<')'<<'('<<r1.p2.getX() << ','<<r1.p2.getY()<<')';
    return os;
}
