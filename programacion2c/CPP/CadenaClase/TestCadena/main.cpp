#include <iostream>
#include <fstream>
#include "../Cadena/Cadena.h"


using namespace std;


void funcionQueRecibeCopia(Cadena cCopia);


int main()
{
    system("chcp 1252 > nul");

    Cadena c1("Chau que mal");

    Cadena c4(c1);
    Cadena c5 = c4;
    Cadena c6 = "Hola mundo";
    Cadena c7;
    c7 = c1;
    funcionQueRecibeCopia(c7);

//    cout << c3 << endl;

    // cout << "Ingrese una cadena:" << endl;
    // cin >> c1;
    // cout << "La cadena ingresada es: " << c1 << endl;

    // cout << "Ingrese una cadena (2):" << endl;
    // cin >> c1;
    // cout << "La cadena ingresada es: " << c1 << endl;

    Cadena c11("chau que mal");

    int pos = 200;

    cout<< "La longitud de la cadena c11 -- " << c11.getCadenaC() << " -- es "<< c11.getLongitud() <<endl;

    cout<< "El caracter en la posicion "<< pos + 1 << " de la cadena c11 es " << c11[pos] <<endl;

    const char* messi = "Messi";

    cout<< "El caracter en la posicion "<< pos + 1 << " de la cadena messi es " << messi[pos] <<endl;

    if(c1 < c11)
        cout <<"c1 es menor a c11" << endl;
    else
        cout << "c1 es mayor o igual a c11" <<endl;


    c1 += c11;
    cout << "c1 += c11 " << c1 <<endl;


    fstream archivo("archivo.txt", ios::in);
    fstream archivoSal("archivoSal.txt", ios::out);

    archivo >> c1;
    while(!archivo.eof())
    {
        cout << c1 << endl;
        archivoSal << c1 << endl;
        archivo >> c1;
    }

    archivo.close();
    archivoSal.close();

    return 0;
}


void funcionQueRecibeCopia(Cadena cCopia)
{
//    cout << cCopia << endl;

    Cadena c2("Mundo");
    Cadena c3 = "Hola" + c2 + "!!!" + ' ' + 123;
    cout << c3 << endl;
}
