#include <iostream>

using namespace std;

class ClaseA
{
protected:
    int valor1;
public:
    ClaseA(int valor1 = 0);
    virtual ~ClaseA();
    virtual void imprimir()const;
};


class ClaseB : public ClaseA
{

public:
    ClaseB(int valor1 = 0);
    virtual ~ClaseB();


};

class ClaseC : public ClaseA
{

public:
    ClaseC(int valor1 = 0);
    virtual ~ClaseC();
};

void ClaseA:
imprimir()const
{
    cout <<"PRINTEO DE LA CLASE A" << endl;
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
