#include "ProductoConDescuento.h"

ProductoConDescuento::ProductoConDescuento():Producto(),descuento(0)
{

}


ProductoConDescuento::ProductoConDescuento(const char *codigo, const char * descripcion, float precio, int stock,float descuento):Producto(codigo,descripcion,precio,stock),descuento(descuento)
{

}


ostream& operator<<(ostream& out, const ProductoConDescuento & otro)
{
    out << "Codigo: " << otro.codigo << endl << "Descripcion: " << otro.descripcion<< endl << "Precio: " <<  otro.precio << endl << "Stock: " << otro.stock<< endl << "Descuento: "<< otro.descuento<< endl<< "Precio con descuento: "<< otro.precio - (otro.precio*otro.descuento)/100<< endl;;

    return out;
}
ProductoConDescuento operator+(int stock, const ProductoConDescuento & otro){
ProductoConDescuento nue(otro.codigo,otro.descripcion,otro.precio,otro.stock+stock,otro.descuento);

return  nue;
}
