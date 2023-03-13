#include "Recta.h"

Recta::Recta(){
    Punto ini(0,0);
    Punto fin(0,0);

    this->iniRec = ini;
    this->finRec = fin;
}

Recta::Recta( const Punto& iniRec, const Punto& finRec ){
    this->iniRec = iniRec; /** (x1,y1) **/
    this->finRec = finRec; /** (x2,y2)  **/
}

/*
*       Recta A           Recta B
*   Point A, Point B, Point C, Point D
*/
Punto Recta::operator &&( const Recta& recta ){
    // RECTA A representada como a1x + b1y = c1
    //
    // PUNTO A == recta.iniRec --> (first, second)
    // PUNTO B == recta.finRec --> (first, second)
    //
    // SE GENERA EL VECTOR DIRECTOR DE LA RECTA COMO :: AB = B - A = ( x2-x1; y2-y1) = (vx ; vy)
    //
    double termY_st = this->finRec.getY() - this->iniRec.getY();
    double termX_st = this->iniRec.getX() - this->finRec.getX();
    // TERMINO INDEPENDIENTE SE GENERA, a partir del vector director :: C = vx*py - vy*py
    double termC_st = termX_st*( this->iniRec.getY() ) - termY_st*( this->iniRec.getX() ) ;

    // RECTA B representada como a2x + b2y = c2
    //
    // PUNTO C == recta.iniRec --> (first, second)
    // PUNTO D == recta.finRec --> (first, second)
    //
    double termY_nd = recta.finRec.getY() - recta.iniRec.getY() ;    // Genero las coordenadas del vector director de la recta
    double termX_nd = recta.finRec.getX() - recta.iniRec.getX() ;    // haciendo AB = B - A = (x2-x1 ; y2-y1)
    // Termino independiente C
    double termC_nd = termX_nd*( recta.iniRec.getY() ) - termY_nd*( recta.iniRec.getX() );

    // Determinante como: multiplicacionDiagPpal - multiplicacionResto
    double determinante = termY_nd*termX_st - termY_st*termX_nd ;

    if (determinante == 0){ //En caso de PARALELAS
        /// FLT_MAX pertenece a la bibloteca float.h y coloca el maximo representable por un puntero float
        Punto puntoInt( FLT_MAX,FLT_MAX );
        return puntoInt;
    } else {
        double x = (termX_nd*termC_st - termX_st*termC_nd) / determinante;
        double y = (termY_st*termC_nd - termY_nd*termC_st) / determinante;

        Punto puntoInt( x,y );
        return puntoInt;
    }
}

double Recta::operator -( const Punto& punto ){
    double vectY = this->finRec.getY() - this->iniRec.getY() ;    // Genero las coordenadas del vector director de la recta
    double vectX = this->finRec.getX() - this->iniRec.getX() ;    // haciendo AB = B - A = (x2-x1 ; y2-y1)
    double termC = vectX*( this->iniRec.getY()) - vectY*( this->iniRec.getX() ); //C = Vx*Py - Vy*Px

    double distancia = abs( vectY * punto.getX() + vectX * punto.getY() + termC ) / sqrt( vectY*vectY + vectX*vectX );
    return distancia;
}

/**
*   Una recta lleva la forma de y = mx + b
*   1. Se consigue la pendiente a partir de dos puntos haciendo
*       m = (y2-y1) / (x2-x1)
*       b = y - mx siendo (x,y) alguno de los puntos que pertenezcan a la recta
**/

double Recta::obtPendiente( ){
    /**  m = (y2-y1) / (x2-x1) **/
    double pendiente = ( this->finRec.getY() - this->iniRec.getY() ) / (double)( this->finRec.getX() - this->iniRec.getX() );
    return pendiente;
}

float Recta::obtIndependiente(){
    float termInd = this->iniRec.getY() - ( this->obtPendiente() * this->iniRec.getX() );
    return termInd;
}

ostream& operator <<( ostream& out, const Recta& recta ){
    return out << "{" << recta.iniRec << "," << recta.finRec << "}";
}
