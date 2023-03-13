#include "FiguraGeometrica.h"
#include<string.h>
FiguraGeometrica::FiguraGeometrica()
{
    this->nombre = new char [1];
    this->nombre[0]= '\0';
}

FiguraGeometrica::FiguraGeometrica(const char * nombre)
{
    int tamNombre = strlen(nombre)+1;

    this->nombre = new char [tamNombre];
    strcpy(this->nombre,nombre);


}

FiguraGeometrica::~FiguraGeometrica()
{
    delete[] this->nombre;
}

char * FiguraGeometrica::Getnombre()const
{
    return this->nombre;
}
