// MARCO_AGUSTIN_41572925
#ifndef CADENA_H
#define CADENA_H

#include <iostream>

class Cadena
{
    private:
        char *str;
        unsigned tam;
    public:
        Cadena(const char *cad);
        //Cadena(const Cadena& cad);
        ~Cadena();

        int primeraAparicion(const char c);
        Cadena operator ()(const int& li, const int& ls);
        Cadena aMayusculas();
        Cadena podarIzquierda();

        friend std::ostream& operator <<(std::ostream& out, const Cadena& cad);
};

#endif // CADENA_H
