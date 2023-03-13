#ifndef ANIMAL_H
#define ANIMAL_H
#include<iostream>

using namespace std;


class Animal
{

protected:
    char nombre[20];
    int edad;


public:
    Animal();
    //virtual ~Animal();
    virtual void correr()=0;
    virtual void saltar()=0;
    virtual void comer()=0;
    virtual void dormirSiesta()=0;

    friend ostream& operator<<(ostream & out, Animal & a);

};

#endif // ANIMAL_H
