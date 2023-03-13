#ifndef CLASEBASE_H
#define CLASEBASE_H
#include<iostream>
using namespace std;
class ClaseBase
{
protected:
    int valor1;


public:
    ClaseBase():valor1(0) {}
    ClaseBase(int valor):valor1(valor) {}
    virtual ~ClaseBase()
    {
        cout << "Destructor de la claseBase"<<endl;
    }

};

#endif // CLASEBASE_H
