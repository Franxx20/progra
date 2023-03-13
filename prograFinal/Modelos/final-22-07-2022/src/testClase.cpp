#include "testClase.h"

testClase::testClase()
{
    //ctor
}

testClase::~testClase()
{
    //dtor
}

testClase::testClase(const testClase& other)
{
    //copy ctor
}

testClase& testClase::operator=(const testClase& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
