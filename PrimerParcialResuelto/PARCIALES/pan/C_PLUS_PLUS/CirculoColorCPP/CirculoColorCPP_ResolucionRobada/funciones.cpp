#include <string.h>
#include <iostream>
#include "funciones.h"

using namespace std;

Circulo :: Circulo()
{
    x = y = 0;
    diam = 0;
    color = NULL;
}

char* duplicarCadena( const char* cad )
{
    if(cad && *cad)
    {
        try
        {
            char* aux = new char[strlen(cad) + 1];
            strcpy(aux, cad);
            return aux;
        }
        catch( bad_alloc& er)
        {
            cerr << "ERROR" << er.what() << endl;
        }
    }
    return NULL;
}

Circulo :: Circulo( float x, float y, unsigned diam, const char* color)
{
    this->x = x;
    this->y = y;
    this->diam = diam;
    this->color = duplicarCadena( color );
    if( this->color == NULL && color && *color )
    {
        cerr<< "SIN MEMORIA EN CONSTRUCTOR PARAMETRIZADO"<<endl;
    }
}

Circulo :: Circulo( const Circulo& obj )
{
    this->x = obj.x;
    this->y = obj.y;
    this->diam = obj.diam;
    this->color = duplicarCadena( obj.color );
    if( this->color == NULL && obj.color && *obj.color )
    {
        cerr<< "SIN MEMORIA EN CONSTRUCTOR POR COPIA"<<endl;
    }
}

Circulo :: ~Circulo()
{
    delete[]color;
}

Circulo& Circulo :: operator = (const Circulo& obj)
{
    this->x = obj.x;
    this->y = obj.y;
    this->diam = obj.diam;
    delete[]color;
    this->color = duplicarCadena(obj.color);
    if(this->color == NULL && obj.color && *obj.color)
    {
        cerr<< "SIN MEMORIA EN CONSTRUCTOR POR COPIA"<<endl;
    }
    return (*this);
}

Circulo Circulo :: operator ++ (int)
{
    Circulo aux(*this);
    this->diam++;
    return aux;
}

Circulo Circulo :: operator -- (int)
{
    Circulo aux(*this);
    this->diam--;
    return aux;
}

void Circulo :: CambiarColor(const char* colorNuevo)
{
    delete[]color;
    this->color = duplicarCadena(colorNuevo);
    if(this->color == NULL && colorNuevo && colorNuevo)
    {
        cerr<< "SIN MEMORIA EN CONSTRUCTOR POR COPIA"<<endl;
    }
}

ostream& operator << (ostream& salida, const Circulo& obj)
{
    salida<< "Coordenada x: "<<obj.x<<endl;
    salida<< "Coordenada y: "<<obj.y<<endl;
    salida<< "Diametro: "<< obj.diam <<endl;
    salida<< "Color: "<< (obj.color? obj.color : "NN")<<endl;
    return salida;
}
