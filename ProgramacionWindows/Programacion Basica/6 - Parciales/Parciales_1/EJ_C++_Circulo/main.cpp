#include <iostream>
#include "Circulo.h"

using namespace std;

int main()
{
    float r;

    cout << "Ingrese el radio del circulo: " << endl;
    cin >> r;

    Circulo circ1(1);
    Circulo circ2;
    Circulo circ3(circ1);

    circ1 = r;
    circ3 = --circ1;

    cout << "El perimetro del circulo es: " << circ1.perimetro() << endl;
    cout << "El area del circulo es: " << circ1.area() << endl;

    //cout << circ3.mostrar();
    cout << circ1 << endl;
    cout << circ3 << endl;

    cin >> circ2;
    cout << circ2.mostrar() << endl;

    return 0;
}
