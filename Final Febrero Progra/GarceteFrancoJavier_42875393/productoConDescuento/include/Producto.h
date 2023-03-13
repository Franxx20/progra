#ifndef PRODUCTO_H
#define PRODUCTO_H
#include<iostream>
#include<string.h>
using namespace std;

class Producto
{
    protected:
        char * codigo;
        char * descripcion;
        float precio;
        int stock;


    public:
        Producto();
        Producto(const char *codigo, const char * descripcion, float precio, int stock);

        ~Producto();
        Producto & operator+=(int stock);



        friend ostream &operator<<(ostream & out, const Producto & otro);




};

#endif // PRODUCTO_H
