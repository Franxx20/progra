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

    Hora& correcionValores();
public:
    Hora();
    Hora(Hora & otro);
    Hora (int segundos);

    virtual ~Hora();

    //Hora operator+(const Hora & otro);
    Hora& operator=(const Hora & otro);
    Hora operator++(int); // postIncremento HORA++
    Hora& operator++(); // preIncremento ++HORA
    Hora operator+(const Hora & otro);


    friend ostream& operator<<(ostream & out, const Hora & hora);
};


#endif // HORA_H
