#include <stdio.h>
#include <stdlib.h>
#include "../macros/macros.h"
#include "vec.h"

int disjuntos(int *v1, int *v2, int s1, int s2)
{
	int i, j;
	for(i = 0; i < s1; i++)
	{
		for(j = 0; j < s2; j++)
		{
			if(*(v1 + i) == *(v2 + j)) return 0;
		}
	}

	return 1;
}


int simetria(int *v1, int s1)
{
	int centro = REDONDEO((s1 - 1) / 2.0),
		*p, *d;

	if(DEBUG) printf("Centro: vec[%d] = %d\n", centro, *(v1+centro));

	p = v1;
	d = v1 + (s1 - 1);

	while(centro-- > 0)
	{
		if(DEBUG) printf("%d == %d ??\n", *p, *d);
		if (*(p++) != *(d--)) return 0;
	}

	return 1;
}

int simetria_2(int *v1, int s1)
{
	int *pEnd = v1 + (s1 - 1);

	while(v1 < pEnd)
	{
		if(DEBUG) printf("%d == %d ??\n", *v1, *pEnd);
		if (*(v1++) != *(pEnd--)) return 0;
	}

	return 1;
}