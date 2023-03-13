#include <iostream>
#include "Hora.h"

using namespace std;

int main()
{
    Hora h1 (86399);
    Hora h2 (3601);
    Hora h3;

    cout << "h1 debe decir 23:59:59 - dice <" << h1 << ">" << endl;
    cout << "h2 debe decir 01:00:01 - dice <" << h2 << ">" << endl;

    h3 = h1 + h2;

    cout << "h3 debe decir 01:00:00 - dice <" << h3 << ">" << endl;

    Hora h4(172799);
    cout << "h4 - dice <" << h4 << ">" << endl;
    cout << "h4 debe decir 00:00:00 - dice <" << ++h4 << ">" << endl;

    return 0;
}
