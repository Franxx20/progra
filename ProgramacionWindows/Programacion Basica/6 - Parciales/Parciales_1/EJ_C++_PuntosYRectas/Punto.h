#ifndef PUNTO_H_INCLUDED
#define PUNTO_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Punto
{
	private:
		double x, y;
	public:
		Punto(double x = 0, double y = 0);
		void setX(double& val);
		void setY(double& val);
		double getX()const;
		double getY()const;
		friend ostream& operator <<(ostream& out, const Punto p1);
};

#endif // PUNTO_H_INCLUDED
