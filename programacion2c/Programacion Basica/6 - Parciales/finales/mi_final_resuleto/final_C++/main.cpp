#include <iostream>
#include "Llamada/llamada.h"

using namespace std;

int main()
{
    Llamada com1("1165551234", "1165559876", 21);
    Llamada com2("1165551234", "2265554567", 10);
    Llamada com3("3365556543", "2265551234", 9);

    Llamada com6;
    {
        Llamada com5 = com2;
        com6 = com5;
        cout << com6 << endl;
    }
    cout << com6 << endl;

    try {
        Llamada com4 = com1 + com2;

        cout << "Llamada con recargo=" << 9 + com1 << endl;
        cout << "comunicacion 4=" << com4 << endl;
        cout << com2 + com3 << endl;
    } catch(...) {
        cout << "No se puede realizar la operacion solicitada, no coinciden los numeros de origen" << endl;
    }

    return 0;
}
