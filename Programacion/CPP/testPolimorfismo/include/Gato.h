#ifndef GATO_H
#define GATO_H

#include "Animal.h"
#include<iostream>

using namespace std;



class Gato : public Animal
{
private:
    char color[10];

public:
    Gato();
    Gato(char * color, char * nombre, int edad);

    virtual ~Gato();
    void correr() override;
    void saltar() override;
    void comer() override;
    void dormirSiesta() override;

    char * getNombre();
    char * getColor();
    int getEdad();

};

#endif // GATO_H
