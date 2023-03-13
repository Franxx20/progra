#include <iostream>
#include "Cadena.h"
using namespace std;

int main()
{
//
    Cadena cad1 = "Final Programacion 1110";
    Cadena cfinal;
    cout << cad1 << endl;
    cout << cfinal << endl;
    cout <<"cadFinal "<< (cfinal = cad1 + " UNLAM. 25/02/2023") << endl;
    cout <<"cad1 " << cad1 << endl;

    return 0;
}
