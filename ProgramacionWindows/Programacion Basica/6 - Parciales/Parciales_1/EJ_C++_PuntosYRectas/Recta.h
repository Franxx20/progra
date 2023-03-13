#ifndef RECTA_H_INCLUDED
#define RECTA_H_INCLUDED

#include "Punto.h"
using namespace std;

class Recta : public Punto
{
	private:
		Punto p1, p2;

	public:
		Recta(const Punto& p1, const Punto& p2);
		friend Punto operator &&(Recta& r1, Recta& r2);
		friend double operator -(Recta& r1, Punto& p0);
		friend ostream& operator <<(ostream& out, const Recta r1);
};


#endif // RECTA_H_INCLUDED
