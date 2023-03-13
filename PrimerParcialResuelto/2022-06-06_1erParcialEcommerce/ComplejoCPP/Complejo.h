#ifndef COMPLEJO_H
#define COMPLEJO_H

#include <iostream>

using namespace std;

class Complejo
{
	private:
	    int real;
	    int imaginario;

    public:
        Complejo();
        Complejo(int r, int i);

        Complejo operator+(const Complejo& otro);
        friend Complejo operator*(int escalar,const Complejo & otro);
        Complejo operator*(const Complejo& otro);

        friend ostream& operator <<(ostream& os, const Complejo& otro);
        friend istream& operator >>(istream& is, Complejo& otro);
};



#endif // COMPLEJO_H
