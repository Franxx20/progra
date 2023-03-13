#ifndef CIRUCLO_H
#define CIRUCLO_H

#include "string.h"
#include "stdlib.h"
#include "iostream"

using namespace std;

class Circulo{

    private:
        float x;
        float y;
        unsigned diametro;
        char* color;

    public:

        Circulo();
        Circulo( const float x, const float y, const unsigned diametro, const char* color);

        virtual ~Circulo();

        Circulo operator --( int number );
        Circulo operator ++( int number );
        Circulo& operator =( const Circulo& circIgual );

        void CambiarColor( const char *newColor );
        friend ostream& operator <<( ostream& out, const Circulo& circulo );
};

#endif // CIRUCLO_H
