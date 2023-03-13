#ifndef ANIMAL_H
#define ANIMAL_H


#include <iostream>
using namespace std;

class Animal
{
    private:


    public:
        //virtual ~Animal() {};

        virtual void dormir() const  = 0;
        virtual void comer() const  = 0;
};

#endif // ANIMAL_H
