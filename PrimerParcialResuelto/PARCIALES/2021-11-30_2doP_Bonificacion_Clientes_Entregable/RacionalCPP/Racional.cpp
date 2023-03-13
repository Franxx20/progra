#include "Racional.h"

Racional::Racional(){
    this->numerador = 0;
    this->denominador = 1; //Minimo valor posible debe ser 1 porque no existe division por 0 (valor negativos pueden expresarse en el numerador)
}

Racional::Racional(int numerador, int denominador){

    this->racionalIrreducible( &numerador, &denominador);

    this->denominador = denominador;
    this->numerador = numerador;
}

Racional operator +( const int entero, const Racional& racional ){
    Racional auxSumador ( entero , 1);
    int numSuma = ( (racional.numerador * auxSumador.denominador) + (auxSumador.numerador * racional.denominador) );
    int denSuma = racional.denominador * auxSumador.denominador;

    Racional tempSuma( numSuma, denSuma );

    return( tempSuma );
}

Racional Racional::operator *( Racional racProducto ){
    /** a/b*c/d = a*c / b*c  **/
    /*  A * C  =  A * C       */
    /*  B   D     B * D       */
    int numProd = ( this->numerador * racProducto.numerador );
    int demProd = ( this->denominador * racProducto.denominador );

    Racional tempProd( numProd, demProd );

    return( tempProd );
}

Racional Racional::operator +( Racional racSumador ){
    /** a/b + c/d = (a*d+c*b)/(b*d)  **/
    /*  A + C  =  (A * D)+(C * B)     */
    /*  B   D          B * D          */
    int numSuma = ( (this->numerador * racSumador.denominador) + (racSumador.numerador * this->denominador) );
    int denSuma = this->denominador * racSumador.denominador;

    Racional tempSuma( numSuma, denSuma );

    return( tempSuma );
}

Racional& Racional::operator =( Racional racOrigen ){
    this->denominador = racOrigen.denominador;
    this->numerador = racOrigen.numerador;

    return( *this );
}

void Racional::racionalIrreducible( int *numerador, int *denominador ){
    int divisor = 2; //Inicia en 2 porque todos los numeros son divisibles por 1 (y al hacerlo dan )
    int num = *numerador, den = *denominador;
    while( num>=divisor || den>=divisor ){
        int rtoNum = num%divisor;
        int rtoDiv = den%divisor;

        if( rtoNum==0 && rtoDiv==0 ){
            num /= divisor;
            den /= divisor;
        } else {
            divisor++;
        }
    }

    *numerador = num;
    *denominador = den;
}

float Racional::real(){
    return (this->numerador / (float)this->denominador);
}

ostream& operator <<( ostream& out, const Racional& racional ){
    return out << racional.numerador << "/" << racional.denominador;
}
