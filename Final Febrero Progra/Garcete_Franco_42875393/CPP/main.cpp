///////// GARCETE FRANCO JAVIER 42875393
#include <iostream>
#include "Medicion.h"
using namespace std;

int main()
{
    Medicion m1mv(100,"Mv");
    Medicion m2mv(20,"Mv");
    Medicion m4amp(3,"Amp");

    Medicion m3mv = m1mv - m2mv;



    cout <<"resultado 1: "<< 180+m3mv<<endl;

    try
    {
        // esto va a fallar porque son elementos de distinta unidad
        cout << m3mv - m4amp<<endl;
    }
    catch(...)
    {
        cout <<"No se pueden restar mediciones de distintas unidades de medida"<<endl;
    }
    return 0;
}
