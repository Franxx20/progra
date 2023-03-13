#include <cmath>

#include "Recta.h"

using namespace std;

Recta::Recta(const Punto& p1, const Punto& p2)
: p1(p1), p2(p2)
{}

Punto operator &&(const Recta& r1, const Recta& r2)
{
    Punto p;
    int x, y;

    x = (((r1.p1.getX() * r1.p2.getY() - r1.p1.getY() * r1.p2.getX()) * (r2.p1.getX() - r2.p2.getX())) -
         ((r2.p1.getX() * r2.p2.getY() - r2.p1.getY() * r2.p2.getX()) * (r1.p1.getX() - r1.p2.getX()))) /
                (((r1.p1.getX() - r1.p2.getX()) * (r2.p1.getY() - r2.p2.getY())) -
                 ((r1.p1.getY() - r1.p2.getY()) * (r2.p1.getX() - r2.p2.getX())));
    y = (((r1.p1.getX() * r1.p2.getY() - r1.p1.getY() * r1.p2.getX()) * (r2.p1.getY() - r2.p2.getY())) -
         ((r2.p1.getX() * r2.p2.getY() - r2.p1.getY() * r2.p2.getX()) * (r1.p1.getY() - r1.p2.getY()))) /
                (((r1.p1.getX() - r1.p2.getX()) * (r2.p1.getY() - r2.p2.getY())) -
                 ((r1.p1.getY() - r1.p2.getY()) * (r2.p1.getX() - r2.p2.getX())));

    p.setPunto(x,y);
    return p;
}
double operator - (const Recta& r, const Punto& p)
{
    double dist = abs((r.p2.getY() - r.p1.getY())*p.getX() -
                      (r.p2.getX() - r.p1.getX())*p.getY() +
                      ((r.p2.getX() * r.p1.getY()) - (r.p2.getY() * r.p1.getX()))) /
                  sqrt(pow((r.p2.getY() - r.p1.getY()),2) + pow((r.p2.getX() - r.p1.getX()),2));

    return dist;
}

ostream& operator <<(ostream& sal, const Recta& r)
{
    return sal << "r={" << (const Punto&)r.p1 << "," << (const Punto&)r.p2 << "}";
}

