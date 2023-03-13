#include "Circulo.h"

Circulo::Circulo()
{
    this->x = 0;
    this->y = 0;
    this->diametro = 0;

	this->color = new char[1];
	this->color[0] = '\0';
}

Circulo::Circulo( const float x, const float y, const unsigned diametro, const char* color){
    this->x = x;
    this->y = y;
    this->diametro = diametro;

    this->color = new char[ strlen(color)+1 ];
    strcpy( this->color, color );
}

Circulo Circulo::operator --( int number ){
    //Constructor ( const float x, const float y, const unsigned diametro, const char* color)
    Circulo tempCirc( this->x,
                      this->y,
                      this->diametro,
                      this->color );
    if( this->diametro > 0 ){
        this->diametro--;
    }
    return tempCirc;
}

Circulo Circulo::operator ++( int number ){
    Circulo tempCirc( this->x,
                      this->y,
                      this->diametro,
                      this->color );
    this->diametro++;
    return tempCirc;
}

Circulo& Circulo::operator =( const Circulo& circIgual ){
    this->x = circIgual.x;
    this->y = circIgual.y;
    this->diametro = circIgual.diametro;

    if(strlen(this->color) != strlen(circIgual.color)){
		delete [] this->color;
		this->color = new char[ strlen(circIgual.color) + 1];
	}
    strcpy( this->color, circIgual.color );

    return *this;
}

Circulo::~Circulo(){
}

void Circulo::CambiarColor( const char *newColor ){
    if(strlen(this->color) != strlen(newColor)){
		delete [] this->color;
		this->color = new char[ strlen(newColor) + 1 ];
	}
	strcpy( this->color, newColor );
}

ostream& operator <<( ostream& out, const Circulo& circulo ){
    out << "Diametro:" << circulo.diametro << endl;
    if( circulo.diametro != 0 ){
        out << "Coordenada y:" << circulo.y << ", "
            << "Coordenada x:" << circulo.x << endl;
    }
    return out << "Color:" <<circulo.color << endl << endl;
}
