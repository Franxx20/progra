#include <iostream>

#include "Circulo.h"

using namespace std;

int main()
{
    Circulo c1(10.5, 20.0, 1, "Rojo intenso"), c2, c3;
    c2 = c1--;
    c3 = c2++;

    Circulo c4 = c3++;
    c4.CambiarColor("Amarillo patito fluo");
    cout<< c1 << c2 << c3 << (c4 = c3) <<endl;

    return 0;
}
