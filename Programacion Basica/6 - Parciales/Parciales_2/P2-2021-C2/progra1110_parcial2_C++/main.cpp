// MARCO_AGUSTIN_41572925
#include <iostream>
#include "Cadena.h"

using namespace std;

int main()
{
    int li, ls;
    Cadena cad1 = "    Hola Mundo!    ";
    li = cad1.primeraAparicion('H');
    ls = cad1.primeraAparicion('a');
    if((li!=-1) && (ls!=-1)){
        cout<<"Prueba 1: "<<cad1(li,ls).aMayusculas()<<endl;
        cout<<"Prueba 2: "<<cad1<<endl;
    }
    cout<<"Prueba 3: "<<cad1.podarIzquierda()<<endl;
    cout<<"Prueba 4: "<<cad1<<endl;
    return 0;
}
