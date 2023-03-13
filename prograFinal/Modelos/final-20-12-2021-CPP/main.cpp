#include <iostream>
#include<string>
#include"Medicion.h"


using namespace std;



int main()
{
    Medicion m1mv(100,"Mv");
    Medicion m2mv(20,"Mv");
    Medicion m4amp(3,"AMP");
    Medicion m3mv = m1mv - m2mv;
    Medicion m5mv(m3mv);

    cout << m1mv<< endl;
    cout << m2mv<< endl;
    cout << m3mv<< endl;
    cout << m5mv<< endl;

    cout << "Resultado  1:" << 180+m3mv<<endl;

    try
    {
        cout <<m3mv-m4amp<< endl;
    }
    catch(...)
    {
        cout << "No se pueden restar mediciones de distinta unidad de medida" << endl;
    }

    return 0;
}
