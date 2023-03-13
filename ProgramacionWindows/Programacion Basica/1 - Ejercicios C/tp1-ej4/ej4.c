			/*    ej.4    */
/*	Variables definidas por usuario */
/*			TOL, X y R0 			*/
/*	funcion: 1/2(Ri-1 + (X/Ri-1))	*/

#include <stdio.h>

float abs_f(float n1, float n2)
{
	float n3 = n1 - n2;
	return (n3 < 0.0) ? (n3 * -1.0) : n3;
}


float calcularRaiz(float X, float R0, float TOL)
{
	float 	term = R0,
			prev_term;
	
	do
	{
		prev_term = term;
		term = (float)1/2 * (prev_term + (X / prev_term));

		//printf("prev: %.9f\nR: %.9f\n", prev_term, term);

	} while(abs_f(term, prev_term) > TOL);

	return term;
}


int main()
{
	float 	X = 13,
			R0 = 1,
			TOL = 0.007;

	float f = calcularRaiz(X, R0, TOL);
	printf("Raiz de %.2f es: %.9f\n", X, f);
	
	return 0;
}



/*    ejercicio con argumentos a main    */

/*#include <stdlib.h>

int main(int argc, char *argv[])
{
	float 	X = atof(argv[1]),
			R0 = atof(argv[2]),
			TOL = atof(argv[3]);

	float f = calcularRaiz(X, R0, TOL);
	printf("Raiz de %.2f es: %.9f\n", X, f);
	
	return 0;
}*/