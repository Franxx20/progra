#include <iostream>
#include"FiguraGeometrica.h"
#include "Cuadrado.h"
#include "Circulo.h"
using namespace std;


void calcularAreaYPerimetro(const FiguraGeometrica* figura);

int main()
{
Cuadrado cuad("cuadrado", 10);
Circulo cir("circulo",12);

calcularAreaYPerimetro(&cuad);
calcularAreaYPerimetro(&cir);
    return 0;
}

void calcularAreaYPerimetro(const FiguraGeometrica* figura)
{
    cout <<"nombre " << figura->getNombre() <<
         " area " << figura->area() <<" perimetro " << figura->perimetro()
         << endl;

}
