#include <iostream>

using namespace std;


int main()
{
    Racional r1, r2(2, 4), r3, r4;

	cout << "r2: Tiene que valer 1/2: " << r2 << endl

    r1 = r2; ///r1 = 1/2

    r3 = r1 + r2; ///r3 = 1/1

	cout << "r3: Tiene que valer 1/1: " << r3 << endl;

    r4 = 2 + r1;

	cout << "r4: Tiene que valer 5/2: " << r4 << endl;

	cout << "r4 real: (2,5): " << r4.real() << endl;

	cout << "r1: "<< r1 << ", r2: " << r2 << ", r3: " << r3 << ", r4: " << r4 << endl;

    return 0;
}
