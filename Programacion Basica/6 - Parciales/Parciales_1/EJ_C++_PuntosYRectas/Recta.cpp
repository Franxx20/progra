#include "Recta.h"

Recta::Recta(const Punto& p1, const Punto& p2) : p1(p1), p2(p2)
{
}


Punto operator &&(Recta& r1, Recta& r2)
{
	Punto pInt;
	double 	x1 = r1.p1.getX(), y1 = r1.p1.getY(),
			x2 = r1.p2.getX(), y2 = r1.p2.getY(),
			x3 = r2.p1.getX(), y3 = r2.p1.getY(),
			x4 = r2.p2.getX(), y4 = r2.p2.getY();

	double _x = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) /
				((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

	double _y = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) /
				((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

	pInt.setX(_x);
	pInt.setY(_y);

	return pInt;
}


double operator -(Recta& r1, Punto& p0)
{
	double 	x1 = r1.p1.getX(), y1 = r1.p1.getY(),
			x2 = r1.p2.getX(), y2 = r1.p2.getY(),
			x0 = p0.getX()	 , y0 = p0.getY();
	return abs((y2 - y1)*x0 - (x2 - x1)*y0 + x2*y1 - y2*x1) /
	sqrt( pow((y2 - y1),2) + pow((x2 - x1),2) );
}


ostream& operator <<(ostream& out, const Recta r1)
{
	double 	x1 = r1.p1.getX(), y1 = r1.p1.getY(),
			x2 = r1.p2.getX(), y2 = r1.p2.getY();
    return out << "[" << "(" << setprecision(3) << x1 << "," << y1 << ")" << "," << "(" << x2 << "," << y2 << ")" << "]";
}
