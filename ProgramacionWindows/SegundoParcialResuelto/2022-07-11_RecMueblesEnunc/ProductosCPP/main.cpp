/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
* DNI:
***************************************************************************************/

#include <iostream>
#include "Producto.h"
#include "ProductoConDescuento.h"

using namespace std;


int main()
{
    Producto p1("123", "Pizza", 10.0, 15);
    Producto p2("456", "Pollo", 20.0, 25);
    ProductoConDescuento p3("789", "Hamburguesa", 30.0, 35, 10);
    ProductoConDescuento p4("012", "Arroz", 40.0, 45, 20);

    p2 += 100;
    ProductoConDescuento p5 = 200 + p3;

    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    cout << p4 << endl;
    cout << p5 << endl;

    return 0;
}
