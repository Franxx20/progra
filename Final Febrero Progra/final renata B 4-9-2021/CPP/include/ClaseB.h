#ifndef CLASEB_H
#define CLASEB_H

#include "ClaseBase.h"


class ClaseB : public ClaseBase
{
    public:
        ClaseB();
        ClaseB(int valor1):ClaseBase(valor1){}
        virtual ~ClaseB(){std::cout<<"Destructor de la ClaseB"<<endl;}

    protected:

    private:
};

#endif // CLASEB_H
