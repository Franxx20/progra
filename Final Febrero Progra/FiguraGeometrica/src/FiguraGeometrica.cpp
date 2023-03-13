#include "FiguraGeometrica.h"

FiguraGeometrica::FiguraGeometrica()
{
    this->nombre = new char[1];
    this->nombre[0] = '\0';
}
FiguraGeometrica::FiguraGeometrica(const char * nombre){
this->nombre = new char[strlen(nombre)+1];
strcpy(this->nombre,nombre);

}
FiguraGeometrica::~FiguraGeometrica()
{
    //dtor
    delete[]this->nombre;
    std::cout << "Llamando al constructor base"<<std::endl;
}
