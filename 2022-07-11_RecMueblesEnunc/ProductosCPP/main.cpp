/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
* DNI:
***************************************************************************************/

#include <iostream>

#include <string.h>

/*#include "Producto.h"
#include "ProductoConDescuento.h"
*/
using namespace std;

class Producto
{
protected:
    char* codigo;
    char* descripcion;
    float precio;
    int stock;

public:
    Producto();
    ~Producto();
    Producto(const char* cod,const char* descrip,const float pre,const int sto);
    float getPrecio() const;
    Producto& operator+= (const int cantidad);
    friend ostream& operator<<(ostream& os, const Producto& prod);
};

class ProductoConDescuento : public Producto
{
private:
    float descuento;
public:
    ProductoConDescuento();
    ProductoConDescuento(const char* cod, const char* des, const float precio, const int stock, const float descuento);
    float getDes() const;
    ProductoConDescuento& operator=(const ProductoConDescuento& prod);
    friend ProductoConDescuento operator+(const int cantidad, const ProductoConDescuento& prod);
    friend ostream& operator<<(ostream& os, const ProductoConDescuento& prod);
};

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

Producto::Producto()
{
    this->codigo = new char[1];
    this->codigo[0] = '\0';

    this->descripcion = new char[1];
    this->descripcion[0] = '\0';

    this->precio = 0;
    this->stock = 0;
}

Producto::Producto(const char* cod,const char* descrip,const float pre,const int sto)
{
    this->codigo = new char[strlen(cod) + 1];
    strcpy(this->codigo,cod);
    strcat(this->codigo,"\0");

    this->descripcion = new char[strlen(descrip) + 1];
    strcpy(this->descripcion,descrip);
    strcat(this->descripcion,"\0");

    this->precio = pre;
    this->stock = sto;
}

ProductoConDescuento::ProductoConDescuento()
{
    this->descuento = 0;
}

ProductoConDescuento::ProductoConDescuento(const char* cod, const char* des, const float precio, const int stock, const float descuento)
    : Producto(cod,des,precio,stock)
{
    this->descuento = descuento;
}

ostream& operator<<(ostream& os, const Producto& prod)
{
    os<<"Codigo: "<<prod.codigo<<endl<<"Descripcion: "<<prod.descripcion<<endl<<"Precio: "<<prod.precio<<endl<<"Stock: "<<prod.stock<<endl;
    return os;
}

ostream& operator<<(ostream& os, const ProductoConDescuento& prod)
{
    os<<(Producto&)prod<<"Precio con descuento: "<<(1 - (prod.getDes()/100))*prod.getPrecio()<<endl;
    return os;
}

float Producto::getPrecio() const
{
    return this->precio;
}

float ProductoConDescuento::getDes() const
{
    return this->descuento;
}

Producto& Producto::operator+=(const int cantidad)
{
    this->stock+=cantidad;
    return *this;
}

ProductoConDescuento operator+(const int cantidad, const ProductoConDescuento& prod)
{
    ProductoConDescuento pRes(prod.codigo,prod.descripcion,prod.precio,prod.stock + cantidad,prod.descuento);

    return pRes;
}

Producto::~Producto()
{
    delete[] this->codigo;
    delete[] this->descripcion;
}
