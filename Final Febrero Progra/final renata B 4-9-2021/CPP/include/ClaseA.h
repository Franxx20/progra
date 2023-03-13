#ifndef CLASEA_H
#define CLASEA_H

#include "ClaseBase.h"


class ClaseA : public ClaseBase
{
public:
    ClaseA():ClaseBase(){};
    ClaseA(int valor1):ClaseBase(valor1){};
    virtual ~ClaseA()
    {
        std::cout<<"Destructor de la ClaseA"<<endl;
    }



};

#endif // CLASEA_H
