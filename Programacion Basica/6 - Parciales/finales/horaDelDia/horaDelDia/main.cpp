#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "include/HoraDelDia.h"

using namespace std;

int main()
{
	HoraDelDia inicio, fin(0,0,20);
	cout << "ingrese el horario de inicio: ";
	cin >> inicio;

	cout << endl << "Ingrese el horario de fin: ";
	cin >> fin;

	if(inicio >= fin) {
		cout << endl << "Error! El horario de inicio debe ser menor al de fin.";
		return 0;
	}

	while(inicio < fin) {
		system("clear");
		cout << "Actual: " << inicio++ << endl << "Fin: " << fin << endl;
		sleep(1);
	}

	cout << "FIN" << endl;

	HoraDelDia h1(22,54,21), h2(1,20,55), h3;

	h3 = h1+h2;
	cout << h3 << endl;

	h3 += 2;
	cout << h3 << endl;

	h3 = 3 + h3;
	cout << h3 << endl;

	h3 = h3.getHoraMaxima();
	cout << h3 << endl;
}
