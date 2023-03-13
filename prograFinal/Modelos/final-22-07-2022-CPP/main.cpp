#include <iostream>
#include"Circulo.h"
#include"Cuadrado.h"

using namespace std;

void calcularAreaYPerimetro(const FiguraGeometrica* figura);

void calcularAreaYPerimetro2(const FiguraGeometrica& figura);

int main()
{
    Cuadrado cuadrado("Cuadrado",2);
    Circulo circulo("Circulo",4);

    calcularAreaYPerimetro(&cuadrado);
    calcularAreaYPerimetro(&circulo);
    calcularAreaYPerimetro2(cuadrado);
    return 0;
}

void calcularAreaYPerimetro(const FiguraGeometrica* figura)
{
    cout << "Nombre " << figura->Getnombre() << endl;
    cout << "Area " << figura->area() << endl;
    cout << "Perimetro " << figura->perimetro() << endl;

}

void calcularAreaYPerimetro2(const FiguraGeometrica& figura)
{
 cout << "Nombre " << figura.Getnombre() << endl;
    cout << "Area " << figura.area() << endl;
    cout << "Perimetro " << figura.perimetro() << endl;

}
