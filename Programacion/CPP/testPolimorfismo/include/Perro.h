#ifndef PERRO_H
#define PERRO_H

#include "Animal.h"


class Perro : public Animal
{
    public:
        Perro();
        virtual ~Perro();

    private:
            void correr()=0;
     void saltar()=0;
     void comer()=0;
     void dormirSiesta()=0;



};

#endif // PERRO_H
