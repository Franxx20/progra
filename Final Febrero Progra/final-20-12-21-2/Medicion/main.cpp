#include <iostream>
#include "Medicion.h"
using namespace std;

int main()
{
    Medicion m1mv(100,"Mv");
    Medicion m2mv(20,"Mv");
    Medicion m4amp(3,"Amp");
    Medicion m3mv = m1mv - m2mv;

    cout << "resultado 1: "<<m1mv <<endl;
    cout << "resultado 2: "<<m2mv <<endl;
    cout << "resultado 3: "<<m4amp<<endl;
    cout << "resultado 4: "<<180+m3mv <<endl;

    try{
    cout<<m3mv - m4amp<<endl;
    }catch(...)
    {
        cout <<"No se puede restar mediciones de distinta unidad de medida"<<endl;
    }

    return 0;
}
