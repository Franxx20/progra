/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres: Gonzalez, Agustin Elias

* DNI: 42629319

***************************************************************************************/

#include <iostream>
#include <string.h>

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
        Producto(const char* codigo, const char* descripcion, float precio, int stock);
        Producto& operator+=(int stock);
        ~Producto();

        friend ostream& operator<<(ostream& os, const Producto& p);
};


class ProductoConDescuento : public Producto
{
    protected:
        float descuento;

    public:
        ProductoConDescuento();
        ProductoConDescuento(const char* codigo, const char* descripcion, float precio, int stock, float descuento);
        ~ProductoConDescuento();

        friend ProductoConDescuento operator+(int stock, const ProductoConDescuento& p);
        friend ostream& operator<<(ostream& os, const ProductoConDescuento& p);

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
    this->codigo[0] = '\0';
    this->precio = 0;
    this->stock = 0;
}


Producto::Producto(const char* codigo, const char* descripcion, float precio, int stock)
{
    int tamCod = strlen(codigo) + 1;
    int tamDes = strlen(descripcion) + 1;

    this->codigo = new char[tamCod];
    strncpy(this->codigo, codigo, tamCod);

    this->descripcion = new char[tamDes];
    strncpy(this->descripcion, descripcion, tamDes);

    this->precio = precio;
    this->stock = stock;
}

Producto& Producto::operator+=(int stock)
{
    this->stock += stock;
    return *this;
}


Producto::~Producto()
{
    delete [] this->codigo;
    delete [] this->descripcion;
}

ostream& operator<<(ostream& os, const Producto& p)
{
    os << "Codigo: " << p.codigo << "\nDescripcion: " << p.descripcion <<
    "\nPrecio: " << p.precio << "\nStock: " << p.stock << endl;
    return os;
}

ProductoConDescuento::ProductoConDescuento() : Producto(), descuento(0)
{

}

ProductoConDescuento::ProductoConDescuento(const char* codigo, const char* descripcion, float precio, int stock, float descuento)
: Producto(codigo, descripcion, precio, stock), descuento(descuento)
{

}


ProductoConDescuento::~ProductoConDescuento()
{

}

ProductoConDescuento operator+(int stock, const ProductoConDescuento& p)
{
    ProductoConDescuento res(p.codigo, p.descripcion, p.precio, p.stock + stock, p.descuento);

    return res;
}


ostream& operator<<(ostream& os, const ProductoConDescuento& p)
{
     os << "Codigo: " << p.codigo << "\nDescripcion: " << p.descripcion <<
    "\nPrecio: " << p.precio << "\nStock: " << p.stock << "\nDescuento: " << p.descuento <<
    "\nPrecio con descuento: " << p.precio - ((p.descuento * p.precio) / 100)  << endl;
    return os;
}
