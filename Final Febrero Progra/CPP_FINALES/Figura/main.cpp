#include <iostream>
#include "Triangulo.h"
#include "Cuadrado.h"
#include "Figura.h"
using namespace std;

int main()
{
    unsigned int cantidadLados = 5;
    unsigned int perimetro = 123;
    unsigned int lado1 = 2;
    unsigned int lado2 = 3;
    unsigned int lado3 = 3;
    Figura f1(cantidadLados, perimetro);
    Cuadrado c1(lado1, lado2);
    Triangulo t1(lado1, lado2, lado3);
    cout << "Esperado - Figura : 5 - 123" << endl;
    cout << "Actual - Figura : "
         << f1.cantidadLados() << " - "
         << f1.perimetro() << endl;
    cout << endl;
    cout << "Esperado - Cuadrado : 2 - 10" << endl;
    cout << "Actual - Cuadrado : "
         << c1.cantidadLados() << " - "
         << c1.perimetro() << endl;
    cout << endl;
    cout << "Esperado - Triangulo : 3 - 8" << endl;
    cout << "Actual - Triangulo : "
         << t1.cantidadLados() << " - "
         << t1.perimetro() << endl;
    return 0;
}
