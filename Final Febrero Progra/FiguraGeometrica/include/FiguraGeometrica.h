#ifndef FIGURAGEOMETRICA_H
#define FIGURAGEOMETRICA_H
#include<string.h>
#include<iostream>

class FiguraGeometrica
{
    protected:
        char *nombre;
    public:
        FiguraGeometrica();
        FiguraGeometrica(const char * nombre);
        virtual ~FiguraGeometrica();

        char * getNombre()const {return this->nombre;}

        virtual double area()const=0;
        virtual double perimetro()const=0;
};

#endif // FIGURAGEOMETRICA_H
