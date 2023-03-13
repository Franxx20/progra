#ifndef PUNTO_H
#define PUNTO_H

#include <iostream>

using namespace std;

class Punto
{
    public:
        Punto();
        Punto(double x, double y);

        double getX() const {return x; };
        double getY () const {return y; };

        void setPunto(double x, double y);

        friend ostream& operator <<(ostream& sal, const Punto& p);

    private:
        double x;
        double y;
};

#endif // PUNTO_H
