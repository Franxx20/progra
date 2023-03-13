#include <string.h>
#include <queue>
#include <iostream>
#include "Cadena.h"

using namespace std;


Cadena::Cadena()
{
    this->cadenaC = new char[1];
    cadenaC[0] = '\0';
}


Cadena::Cadena(const char* cadenaC)
{
    this->cadenaC = new char[strlen(cadenaC) + 1];
    strcpy(this->cadenaC, cadenaC);
}


Cadena::Cadena(char c)
{
    this->cadenaC = new char[2];
    cadenaC[0] = c;
    cadenaC[1] = '\0';
}


Cadena::Cadena(int numero)
{
    this->cadenaC = new char[cantDigitos(numero) + (numero < 0 ? 1 : 0) + 1];
    sprintf(this->cadenaC, "%d", numero);
}


Cadena::Cadena(const Cadena& otra)
{
    this->cadenaC = new char[strlen(otra.cadenaC) + 1];
    strcpy(this->cadenaC, otra.cadenaC);
}


Cadena::~Cadena()
{
//    cout << "Ejecutando Destructor ..." << endl;
    delete [] cadenaC;
}

int Cadena::getLongitud() const
{
    char* i = this->cadenaC;
    int longitud = 0;

    while(*i)
    {
        longitud++;
        i++;
    }

    return longitud;
}

const char* Cadena::getCadenaC() const
{
    return this->cadenaC;
}

Cadena& Cadena::operator +=(const Cadena& cadena)
{
    Cadena cadAux;

    strcpy(cadAux.cadenaC,this->cadenaC);

    delete [] this->cadenaC;

    this->cadenaC = new char[strlen(cadena.cadenaC) + strlen(cadAux.cadenaC) + 1];

    strcpy(this->cadenaC,cadAux.cadenaC);
    strcat(this->cadenaC, cadena.cadenaC);

    return *this;
}

bool Cadena::operator ==(const Cadena& cadena) const
{
    char* i = this->cadenaC;
    char* j = cadena.cadenaC;

    while(*i && *j)
    {
        if(*i != *j)
            return false;
        i++;
        j++;
    }

    return true;
}

bool Cadena::operator !=(const Cadena& cadena) const
{
    char* i = this->cadenaC;
    char* j = cadena.cadenaC;
    while(*i && *j)
    {
        if(*i != *j)
            return true;
        i++;
        j++;
    }

    return false;
}

bool Cadena::operator <(const Cadena& cadena) const
{
    char* i = this->cadenaC;
    char* j = cadena.cadenaC;

    while(*i && *j)
    {
        if(*i < *j)
            return true;
        i++;
        j++;
    }

    return false;
}

bool Cadena::operator <=(const Cadena& cadena) const
{

    char *i = this->cadenaC;
    char *j = cadena.cadenaC;

    while(*j && *i)
    {
        if(*i != *j)
        {
            if(*i > *j)
                return false;
        }
        i++;
        j++;
    }
    return true;
}

bool Cadena::operator >(const Cadena& cadena) const
{


    char *i = this->cadenaC;
    char *j = cadena.cadenaC;

    while(*i && *j)
    {
        if(*j != *i)
        {
            if(*j > *i)
                return false;
            if(*j < *i)
                return true;
        }

        i++;
        j++;
    }

    return false;
}

bool Cadena::operator >=(const Cadena& cadena) const
{
    char* i = this->cadenaC;
    char* j = cadena.cadenaC;

    while(*i && *j)
    {
        if(*i < *j)
            return false;
        i++;
        j++;
    }

    return true;
}

Cadena& Cadena::operator =(const Cadena& otra)
{
    if (this == &otra)
        return *this;

    if(strlen(this->cadenaC) != strlen(otra.cadenaC))
    {
        delete [] this->cadenaC;
        this->cadenaC = new char[strlen(otra.cadenaC) + 1];
    }

    strcpy(this->cadenaC, otra.cadenaC);

    return *this;
}

char& Cadena::operator [](int subindice)
{
    Cadena errorCad;

    if((int)strlen(this->cadenaC) < subindice)
        return errorCad.cadenaC[0];
    return this->cadenaC[subindice];
}

const char& Cadena::operator [](int subindice) const
{
    Cadena errorCad;

    if((int)strlen(this->cadenaC) < subindice)
        return errorCad.cadenaC[0];
    return this->cadenaC[subindice];
}

Cadena operator +(const Cadena& cad1, const Cadena& cad2)
{
    Cadena concat;
    delete [] concat.cadenaC; //TODO: Implementar constructor privado que no copia la cadena.
    concat.cadenaC = new char[strlen(cad1.cadenaC) + strlen(cad2.cadenaC) + 1];
    strcpy(concat.cadenaC, cad1.cadenaC);
    strcat(concat.cadenaC, cad2.cadenaC);
    return concat;
}


ostream& operator <<(ostream& os, const Cadena& cadena)
{
    os << cadena.cadenaC;
    return os;
}


istream& operator >>(istream& is, Cadena& cadena)
{
    queue<char> colaChars;
    char c;

    while((c = is.get()) != '\n' && c != EOF)
        colaChars.push(c);

    if(strlen(cadena.cadenaC) != colaChars.size())
    {
        delete [] cadena.cadenaC;
        cadena.cadenaC = new char[colaChars.size() + 1];
    }

   	int i = 0;
    while(!colaChars.empty())
    {
        cadena.cadenaC[i++] = colaChars.front();
        colaChars.pop();
    }

    cadena.cadenaC[i] = '\0';

    return is;
}


int Cadena::cantDigitos(int numero)
{
    int cant = 1;

    while((numero /= 10) != 0)
        cant++;

    return cant;
}


bool Cadena::esFinDeLinea(char c)
{
    return c == '\r' || c == '\n';
}
