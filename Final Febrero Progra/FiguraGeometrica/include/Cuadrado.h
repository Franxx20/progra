#ifndef CUADRADO_H
#define CUADRADO_H

#include "FiguraGeometrica.h"

using namespace std;
class Cuadrado : public FiguraGeometrica
{
private:
    double lado;

public:
    Cuadrado():FiguraGeometrica(),lado(0) {};
    Cuadrado(const char * nombre,double lado):FiguraGeometrica(nombre),lado(lado)
    {

    };

    virtual ~Cuadrado()
    {
        cout <<"llamando al constructor cuadrado"<<endl;
    };

    double area()const override
    {
        return this->lado * this->lado;
    };
    double perimetro()const override
    {
        return this->lado *4;
    }


};

#endif // CUADRADO_H
