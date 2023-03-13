/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
***************************************************************************************/

#include <iostream>

using namespace std;


/** Figura **/

class Figura
{
public:
    virtual double area() const = 0;
    virtual double perimetro() const = 0;
};

/*
double Figura::area() const
{
	return 0;
}


virtual double Figura::perimetro()
{
	return 0;
}
*/

/** Circulo **/

#define PI 3.14159265358979323846

class Circulo : public Figura
{
private:
	double radio;

public:
	Circulo(double radio);

	double area() const override;
	double perimetro() const override;
};


Circulo::Circulo(double radio)
: radio(radio)
{}


double Circulo::area() const
{
	return PI * radio * radio;
}


double Circulo::perimetro() const
{
	return 2 * PI * radio;
}


/** Cuadrado **/

class Cuadrado : public Figura
{
private:
	double lado;

public:
	Cuadrado(double lado);

	double area() const override;
    double perimetro() const override;
};


Cuadrado::Cuadrado(double lado)
: lado(lado)
{}


double Cuadrado::area() const
{
	return lado * lado;
}


double Cuadrado::perimetro() const
{
	return 4 * lado;
}


/** Main **/

void imprimirFigura(const Figura& figura)
{
    cout << "Area: " << figura.area() << endl;
    cout << "Perimetro: " << figura.perimetro() << endl;
}

int main()
{
    //Figura fig; /** Corrija el codigo para que no se pueda crear un objeto de clase Figura. Luego comente la linea para que el programa compile. **/
    Circulo circulo(5);
    Cuadrado cuadrado(4);

    imprimirFigura(circulo);
    imprimirFigura(cuadrado);

    return 0;
}

/*
void imprimirFigura(Figura figura)
{
    cout << "Area: " << figura.area() << endl;
    cout << "Perimetro: " << figura.perimetro() << endl;
}
*/
