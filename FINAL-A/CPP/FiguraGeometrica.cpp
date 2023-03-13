#include "FiguraGeometrica.h"
#include<string.h>
FiguraGeometrica::FiguraGeometrica()
{
    this->nombre = new char [0];
    this->nombre[0] = '\0';

}

FiguraGeometrica::FiguraGeometrica(const char * nombre)
{
    this->nombre = new char[strlen(nombre)+1];

    strcpy(this->nombre,nombre);


}

FiguraGeometrica::~FiguraGeometrica()
{
    delete[]this->nombre;
}
