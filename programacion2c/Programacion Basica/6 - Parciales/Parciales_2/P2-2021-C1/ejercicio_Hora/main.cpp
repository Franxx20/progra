#include <iostream>
#include "Hora.h"

using namespace std;

int main()
{
	Hora h1(86399);
	Hora h2(3601);
	Hora h3;
	//Hora h4();

	cout << "h1 debe decir 23:59:59 - dice: <" << h1 << ">" << endl;
	cout << "h2 debe decir 01:00:01 - dice: <" << h2 << ">" << endl;
	cout << "h3 debe decir 01:00:00 - dice: <" << (h3 = h1 + h2) << ">" << endl;

	Hora h5(172799);
	cout << "h5 debe decir 00:00:00 - dice: <" << ++h5 << ">" << endl;

	Hora h6(285799);
	cout << "h6 debe decir 07:23:19 - dice: <" << h6 << ">" << endl;


	return 0;
}
