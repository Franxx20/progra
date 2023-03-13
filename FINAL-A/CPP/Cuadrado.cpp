#include "Cuadrado.h"

Cuadrado::Cuadrado():FiguraGeometrica(),lado(0)
{
    //ctor
}

Cuadrado::Cuadrado(const char * nombre, double lado):FiguraGeometrica(nombre),lado(lado)
{

}
Cuadrado::~Cuadrado()
{
    //dtor
}

double Cuadrado::area()const
{
    return this->lado * this->lado;
}
double Cuadrado::perimetro()const
{
    return 4*this->lado;
}
