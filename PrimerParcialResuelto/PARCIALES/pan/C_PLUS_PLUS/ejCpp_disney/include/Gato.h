#ifndef GATO_H
#define GATO_H

#include "Animal.h"

class Gato : public Animal
{
    private:
        char * nombre;

    public:
        Gato(const char *);

        void comer () const;
        void dormir() const;
        void jugarConLaser() const;
};

#endif // GATO_H
