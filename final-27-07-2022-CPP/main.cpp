#include <iostream>
#include"VectorEnteros.h"
using namespace std;

int main()
{
    int ve1[] = {1,2,3,4,5,6,7,8};
    int ve2[] = {9,10,11,12,13};
    VectorEnteros v1;
    VectorEnteros v2(ve2,5);
    VectorEnteros v3;
//
    cout << v2.agregar(ve1,sizeof(ve1)/sizeof(ve1[0])) << endl;
    v1=v2;
    v3 = v1 + v2;
    v3 = v3 + 14;
    cout << v3 << endl;
    return 0;
}
