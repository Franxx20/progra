#include "Punto.h"

Punto::Punto(){
    this->x = 0;
    this->y = 0;
}

Punto::Punto( double x, double y ){
    this->x = x;
    this->y = y;
}

Punto::~Punto(){
    //dtor
}

double Punto::getX() const {
    return this->x;
}
double Punto::getY() const {
    return this->y;
}

ostream& operator <<( ostream& out, const Punto& punto ){
    return out << "(" << punto.x << "," << punto.y << ")";
}
