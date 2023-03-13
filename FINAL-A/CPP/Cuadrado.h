#ifndef CUADRADO_H
#define CUADRADO_H

#include "FiguraGeometrica.h"


class Cuadrado : public FiguraGeometrica
{
    public:
        Cuadrado();
        Cuadrado(const char * nombre, double lado);
        virtual ~Cuadrado();

           double area()const override ;
         double perimetro()const override;

    protected:

    private:
        double lado;
};

#endif // CUADRADO_H
