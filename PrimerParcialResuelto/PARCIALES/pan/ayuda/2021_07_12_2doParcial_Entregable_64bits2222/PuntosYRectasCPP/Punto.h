#ifndef PUNTO_H
#define PUNTO_H



#include <iostream>


using namespace std;

class Punto
{
private:
    double x;
    double y;

public:

    Punto(double x = 0, double y = 0);

    double getX() const { return x; };
    void setX(double x){ this->x = x; };
    double getY() const { return y; };
    void setY(double y){ this->y = y; };

    friend ostream& operator <<(ostream& os, const Punto);
};

#endif // PUNTO_H
