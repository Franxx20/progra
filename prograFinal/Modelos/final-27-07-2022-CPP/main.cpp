#include <iostream>
#include"VectorEnteros.h"
using namespace std;

int main()
{
    int ve1[] = {1,2,3,4,5,6,7,8};
    int ve2[] = {9,10,11,12,13};
    VectorEnteros v1;
    VectorEnteros v2(ve2,sizeof(ve2)/sizeof(ve2[0]));
    VectorEnteros v3;

    cout << v1.agregar(ve1,sizeof(ve1)/sizeof(ve1[0])) << endl;
    v3 = v1 + v2;
    v3 = v3 + 16;
    cout << v3 << endl;
    return 0;
}
