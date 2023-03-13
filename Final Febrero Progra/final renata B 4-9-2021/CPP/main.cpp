#include <iostream>
#include"../include/ClaseBase.h"
#include"../include/ClaseA.h"
#include"../include/ClaseB.h"
using namespace std;

int main()
{
    ClaseBase * a = new ClaseA(1);
    ClaseBase * b = new ClaseB(2);

    delete a;
    delete b;

    return 0;
}
