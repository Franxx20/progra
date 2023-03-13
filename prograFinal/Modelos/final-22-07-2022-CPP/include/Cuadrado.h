#ifndef CUADRADO_H
#define CUADRADO_H

#include "FiguraGeometrica.h"


class Cuadrado : public FiguraGeometrica
{
    public:
        Cuadrado();
        Cuadrado(const char * nombre, int lado);
        virtual ~Cuadrado();

        double area()const override;
        double perimetro()const override;






    private:
        int lado;
};

#endif // CUADRADO_H
