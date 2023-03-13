#include "Producto.h"

Producto::Producto():precio(0),stock(0)
{
    this->codigo = new char[1];
    this->codigo[0] = '\0';
    this->descripcion = new char [1];
    this->descripcion[0] = '\0';


}
Producto::Producto(const char *codigo, const char * descripcion, float precio, int stock):precio(precio),stock(stock){
this->codigo = new char[strlen(codigo)+1];
strcpy(this->codigo,codigo);
this->descripcion = new char[strlen(descripcion)+1];
strcpy(this->descripcion,descripcion);


}

Producto::~Producto()
{
    delete[]this->codigo;
    delete[]this->descripcion;
    cout << "llamando al destructor de Producto" << endl;
    //dtor
}
Producto & Producto::operator+=(int stock){
this->stock +=stock;

return *this;
}
ostream & operator<<(ostream & out,const Producto & otro)
{
        out << "Codigo: " << otro.codigo << endl << "Descripcion: " << otro.descripcion<< endl << "Precio: " <<  otro.precio << endl << "Stock: " << otro.stock<< endl;

    return out;
}
