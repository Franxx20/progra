#ifndef CIRCULO_H
#define CIRCULO_H
#include<iostream>
#include "FiguraGeometrica.h"
using namespace std;

class Circulo : public FiguraGeometrica
{
    private:
        double radio;

    public:
        Circulo():FiguraGeometrica(),radio(0){ };
        Circulo(const char *nombre,double radio):FiguraGeometrica(nombre),radio(radio){};
        virtual ~Circulo(){
        cout << "llamando al destructor de circulo" <<endl;
        };

        double area()const override{
        return 3.14 * radio * radio;
        };

        double perimetro()const override{
        return 2*3.14 * radio;
        };


};

#endif // CIRCULO_H
