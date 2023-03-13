/*	Desarrollar una función que inserte un elemento en un arreglo
de enteros, dada la posición de inserción.	*/
#include "helper.h"

int main()
{
	int vec[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	if(!insert_i(42, 5, vec, SIZE(vec)))
		printf("[ERROR] - Couldn't instert into array\n");
	else
		printArray(vec, SIZE(vec));

	return 0;
}


int insert_i(int what, int where, int *in, int size)
{
	int  i = size - 1,
		*a = in + size - 1,
		*b = a;

	if(where > size || where <= 0)
		return NOT_OK;

	while(i-- >= where)
	{
		*(a--) = *(--b);
	}

	*a = what;

	return OK;
}


void printArray(int *vec, int size)
{
	int i;
	printf("--- Print Array ---\n");
	for(i = 0; i < size; i++)
	{
		printf("#%d --- %d\n", i+1, vec[i]);
	}
	printf("-------------------\n");
}
