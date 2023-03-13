#ifndef RECTA_H
#define RECTA_H

#include <iostream>

#include "Punto.h"

using namespace std;

class Recta : public Punto
{
    public:
        Recta(const Punto& p1, const Punto& p2);

        friend Punto operator &&(const Recta& r1, const Recta& r2);
        friend double operator - (const Recta& r, const Punto& p);

        friend ostream& operator <<(ostream& sal, const Recta& r);

    private:
        Punto p1;
        Punto p2;
};

#endif // RECTA_H
