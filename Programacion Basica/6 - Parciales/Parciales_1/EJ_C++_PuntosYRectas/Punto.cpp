#include "Punto.h"

Punto::Punto(double x, double y): x(x), y(y){}


double Punto::getX()const
{
	return this->x;
}

double Punto::getY()const
{
	return this->y;
}


void Punto::setX(double& val)
{
	this->x = val;
}

void Punto::setY(double& val)
{
	this->y = val;
}


ostream& operator <<(ostream& out, const Punto p1)
{
    return out << "(" << setprecision(3) << p1.x << "," << setprecision(2) << p1.y << ")";
}
