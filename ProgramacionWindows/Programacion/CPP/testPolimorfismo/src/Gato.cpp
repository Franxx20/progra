#include "Gato.h"
#include<string.h>
#include<iostream>

using namespace std;
Gato::Gato()
{
    //ctor
}
char *Gato::getNombre()
{
    return this->nombre;
}

char * Gato::getColor()
{
    return this->color;
}

int Gato::getEdad()
{
    return this->edad;
}

Gato::Gato(char * color, char * nombre, int edad)
{
    strcpy(this->color,color);
    strcpy(this->nombre, nombre);
    this->edad = edad;
}

void Gato::correr()
{
    cout << "EL GATO "<< this->getNombre() << " ESTA DURMIENDO UNA SIESTA" << endl;;
}
void Gato::saltar()
{
    cout << "EL GATO " << this->getNombre()<< " ESTA CORRIENDO" << endl;
}
void Gato::comer()
{
    cout << "EL GATO " << this->getNombre() << " ESTA COMIENDO" << endl;
}
void Gato::dormirSiesta()
{
    cout << "EL GATO " << this->getNombre() << " ESTA DURMIENDO UNA SIESTA" << endl;
}



Gato::~Gato()
{
    //dtor
}

