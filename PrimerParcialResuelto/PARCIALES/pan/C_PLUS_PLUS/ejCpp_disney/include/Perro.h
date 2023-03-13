#ifndef PERRO_H
#define PERRO_H

#include "Animal.h"


class Perro : public Animal
{
    private:
        char * nombre;

    public:
        Perro(const char *);

        void comer () const;
        void dormir() const;
        void moverCola() const;

        friend ostream& operator <<(ostream& sal, const Perro& perro);
};

#endif // PERRO_H
