#include <stdio.h>
#include <stdlib.h>
int getInput(int i)
{
	int aux = 0;
	printf("#%d - (-1 to exit): >>> ", i);
	scanf("%d", &aux);
	return aux;
}


int cargarVector(int *vec, int size, int curr_pos)
{
	if(size == curr_pos) return -1;
	int i = curr_pos,
		condition;
	vec += curr_pos;
	
	condition = getInput(i);
	while (i < size - 1 && condition != -1)
	{
		*vec = condition;
		vec++; i++;
		condition = getInput(i);
	}
	
	return i;
}


void mostrarVector(int *vec, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		printf("#%d - %d\n", i, vec[i]);
	}
}


int main()
{
	int size = 7,
		curr_pos = 0;
	int *vec = calloc(size, sizeof(int));

	int t = cargarVector(vec, size, curr_pos);
	printf("--- %d valores cargados ---\n", t);
	mostrarVector(vec, size);

	return 0;
}


/* 		printf("#%d - (-1 to exit): >>> ", i);
		scanf("%d", vec);
		if(*vec == -1)
		{
			*vec = 0;
			break;
		} */