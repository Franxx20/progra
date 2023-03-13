#ifndef CIRCULO_H
#define CIRCULO_H

#include "FiguraGeometrica.h"


class Circulo : public FiguraGeometrica
{
    public:
        Circulo();
        Circulo(const char *nombre, int radio);

        double area()const override;
        double perimetro()const override;


        virtual ~Circulo();

    protected:

    private:
        int radio;
};

#endif // CIRCULO_H
