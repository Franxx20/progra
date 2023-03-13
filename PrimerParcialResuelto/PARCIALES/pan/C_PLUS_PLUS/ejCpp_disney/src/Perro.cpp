#include "Perro.h"
#include <string.h>


Perro::Perro(const char * n)
{
    this->nombre = new char[strlen(n)+1];

    strcpy(this->nombre,n);
}

void Perro::dormir() const
{
    cout << ("El perro duerme") << endl;
}

void Perro::comer () const
{
    cout << ("El perro esta comiendo") << endl;
}

void Perro::moverCola() const
{
    cout << ("El perro esta moviendo la cola") << endl;
}

ostream& operator <<(ostream& sal, const Perro& perro)
{
	return sal << perro.nombre;///muestra en pantalla la cadena
}




