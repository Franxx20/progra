#ifndef PRODUCTOCONDESCUENTO_H
#define PRODUCTOCONDESCUENTO_H

#include "Producto.h"


class ProductoConDescuento : public Producto
{
private:
    float descuento;

public:
    ProductoConDescuento();
    ProductoConDescuento(const char *codigo, const char * descripcion, float precio, int stock,float descuento);

    friend ostream &operator<<(ostream & out, const ProductoConDescuento & otro);
    friend ProductoConDescuento operator+(int stock, const ProductoConDescuento & otro);
};

#endif // PRODUCTOCONDESCUENTO_H
