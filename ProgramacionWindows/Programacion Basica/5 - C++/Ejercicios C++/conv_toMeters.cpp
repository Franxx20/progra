#include <iostream>
#include <iomanip>

using namespace std;

int main ()
{
	float   fMedidaUsuario,
			fConvMetros,
			fConvCentim;

	cout  << "Longitud a convertir: ";
	cin   >>  fMedidaUsuario;

	while (fMedidaUsuario > 0)
	{
		fConvMetros  =  fMedidaUsuario * 12 * 2.54;
		fConvCentim  =  fConvMetros/100;

		cout  	<<  "Medida inglesa: "
				<<  setw(9) //Sets width
				<<  setprecision(2)
				<<  setiosflags(ios::fixed)
				<<  fMedidaUsuario
				<<  "\n";
		cout  	<<  "Medida en metros: "
				<<  setw(9)
				<<  setprecision(2)
				<<  fConvMetros
				<<  "\n";
		cout  	<<  "Medida en centimetros: "
				<<  setw(9)
				<<  setprecision(2)
				<<  fConvCentim
				<<  "\n";

		cout  	<<  "\nIntroduzca otro valor a \n";
		cout  	<< "convertir (0 termina el programa): ";
		cin    	>>  fMedidaUsuario;
	}
	cout  <<  "\nTerminación del programa\n";
	return 0;
}
