#ifndef CIRCULO_H
#define CIRCULO_H

#include "FiguraGeometrica.h"


class Circulo : public FiguraGeometrica
{
public:
    Circulo();  Circulo(const char * nombre, double radio);
    virtual ~Circulo();

    double area()const override ;
    double perimetro()const override;

protected:

private:
    double radio;
};

#endif // CIRCULO_H
