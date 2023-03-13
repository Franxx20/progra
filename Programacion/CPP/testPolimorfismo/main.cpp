#include <iostream>
#include "D:\Programacion\CPP\testPolimorfismo\include\Gato.h"
using namespace std;

int main()
{
    Gato gato((char*)"Gris",(char*)"Pepe", 4);

    cout << gato;
    gato.comer();
    gato.correr();
    gato.dormirSiesta();
    gato.saltar();

cout << "EL GATO ES DE COLOR " << gato.getColor()<< endl;
    return 0;
}
