#ifndef RECTA_H
#define RECTA_H

#include "Punto.h"

#include <iostream>


using namespace std;

class Recta
{
private:
    Punto p1;
    Punto p2;

public:

    Recta(Punto p1, Punto p2);

    double operator -(const Punto& otro) const;
    Punto operator &&(const Recta& otro) const;


    friend ostream& operator <<(ostream& os, const Recta);
};

#endif // RECTA_H
