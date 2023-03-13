#include <iostream>
#include <windows.h>
#include "HoraDelDia.h"

using namespace std;

int main()
{
    HoraDelDia inicio(0,40,00),fin(0,41,0);  ///ctor () y (x,x,x)
    cout<<"Ingrese el horario de inicio: "<<endl;
    cin>>inicio; ///friend operator >> istream
    cout<<endl<<"Ingrese el horario de fin: "<<endl;
    cin>>fin; ///friend operator >> istream
    cout<<inicio<<endl;
    if(inicio>=fin) ///operadores >=
    {
        cout<<endl<<"ERROR! EL HORORIO DEL INICIO DEBE SER MENOR";
        return 0;
    }
    while(inicio<fin) ///operadores y friend ostream < (x<y)
    {
        system("CLS");
        cout<<"Actual: "<<inicio++<<endl<<"Fin: "<<fin;
        Sleep(1000);
    }
    cout<<"FIN"<<endl;
    HoraDelDia h1(22,54,21),h2(1,20,55),h3;
    h3=h1+h2;  ///operadores = y +
    cout<<h3<<endl;
    h3+=2; ///segundos ///operadores +=
    cout<<h3<<endl;
    h3=3+h3; ///friend num+obj
    cout<<h3<<endl;
    return 0;
}
