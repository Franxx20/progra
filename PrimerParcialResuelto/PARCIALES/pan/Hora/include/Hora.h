#ifndef HORA_H
#define HORA_H

#include <iostream>

using namespace std;

class Hora
{
    private:
        int horas;
        int minutos;
        int segundos;

    public:
        Hora(int);
        Hora();

        Hora& operator = (const Hora&);
        Hora operator + (Hora&) const;
        Hora operator ++ ();

        friend ostream& operator << (ostream&, const Hora&);
};

#endif // HORA_H
