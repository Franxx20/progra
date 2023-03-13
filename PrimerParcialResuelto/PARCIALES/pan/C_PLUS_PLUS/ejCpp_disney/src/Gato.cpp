#include "Gato.h"
#include <string.h>


Gato::Gato(const char * n)
{
    this->nombre = new char[strlen(n)+1];

    strcpy(this->nombre,n);
}

void Gato::dormir() const
{
    cout << ("El gato duerme") << endl;
}

void Gato::comer () const
{
    cout << ("El gato esta comiendo") << endl;
}

void Gato::jugarConLaser() const
{
    cout << ("El gato esta jugando") << endl;
}
