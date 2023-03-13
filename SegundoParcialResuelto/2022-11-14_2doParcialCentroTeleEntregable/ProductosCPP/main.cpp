/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:

* DNI:


***************************************************************************************/

#include <iostream>
#include <string.h>
//#include "Producto.h"
//#include "ProductoConDescuento.h"

using namespace std;
class Producto
{
protected:
    char *codigo;
    char *descripcion;
    float precio;
    int stock;

public:
    Producto();
    Producto(const char *codigo,const  char *descripcio, float precio, int stock);

    ~Producto();
    Producto &operator+=(int stock);

    friend ostream &operator<<(ostream &out, Producto &p);
};

class ProductoConDescuento : public Producto
{
protected:
    float descuento;

public:
    ProductoConDescuento();
    ProductoConDescuento(const char *codigo, const char *descripcio, float precio, int stock, float descuento);

    ~ProductoConDescuento();

    friend ostream &operator<<(ostream &out, const ProductoConDescuento &p);
    friend ProductoConDescuento operator+(int stock, const ProductoConDescuento &p);
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

Producto::Producto() : precio(0), stock(0)
{
    this->codigo = new char[1];
    this->codigo[0] = '\0';

    this->descripcion = new char[1];
    this->descripcion[0] = '\0';
}
Producto::Producto(const char *codigo, const char *descripcion, float precio, int stock) : precio(precio), stock(stock)
{
    int tamCod = strlen(codigo) + 1;
    int tamDesc = strlen(descripcion) + 1;

    this->codigo = new char[tamCod];
    strncpy(this->codigo,codigo,tamCod);
    this->descripcion = new char[tamDesc];
    strncpy(this->descripcion, descripcion, tamDesc);
}

Producto::~Producto()
{
    delete[] this->codigo;
    delete[] this->descripcion;
}

Producto &Producto::operator+=(int stock)
{
    this->stock += stock;

    return *this;
}

ostream &operator<<(ostream &out, Producto &p)
{

    out << "Codigo: " << p.codigo << endl
        << "Descripcion: " << p.descripcion << endl
        << "Precio: " << p.precio << endl
        << "Stock: " << p.precio << endl;

    return out;
}

ProductoConDescuento::ProductoConDescuento() : Producto(), descuento(0) {}
ProductoConDescuento::ProductoConDescuento(const char *codigo, const char *descripcion, float precio, int stock, float descuento) : Producto(codigo, descripcion, precio, stock), descuento(descuento)
{
}

ProductoConDescuento::~ProductoConDescuento() {}

ostream &operator<<(ostream &out, const ProductoConDescuento &p)
{
    out << "Codigo: " << p.codigo << endl
        << "Descripcion: " << p.descripcion << endl
        << "Precio: " << p.precio << endl
        << "Stock: " << p.precio << endl
        << "Precio Con Descuento: " << p.precio - (p.precio * p.descuento) / 100 << endl;

    return out;
}
ProductoConDescuento operator+(int stock,const ProductoConDescuento &p)
{
    ProductoConDescuento nuevo(p.codigo,p.descripcion,p.precio,p.stock + stock, p.descuento);

    return nuevo;
}
