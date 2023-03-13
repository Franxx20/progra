#include <iostream>
#include "include/VectorBool.h"

using namespace std;

int main()
{
	VectorBool v1(3), v2(5), v3(3);

	v1[0] = true; v1[1] = true; v1[2] = false;
	v3[0] = false; v3[1] = true; v3[2] = false;

	try {
		v2 = v1 & v2;
	} catch(length_error& ex) {
		cout << "Error al intentar aplicar v1 & v2... " << ex.what() << endl;
	} catch(exception& ex) {
		cout << "Ha ocurrido un error desconocido: " << ex.what() << endl;
	}

	v2 = v3;

	v3[2] = true;
	cout << "v2 = " << v2 << ", v3 = " << v3 << endl;

	v2 = v1 & v2;
	cout << "v2 = " << v2 << endl;

	return 0;
}
