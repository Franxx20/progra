#include <stdio.h>
#include "vec.h"

void vec_dis_test()
{
	int vec1[3] = {4, 2, 3},
		vec2[14] = {1, 8, 9, 45, 32, 12, 54, 77, 88, 88, 90, 12,
					32, 76};
	
	if (disjuntos(vec1, vec2, SIZE(vec1), SIZE(vec2)))
		printf("Los vectores son disjuntos.\n");
	else
		printf("Los vectores NO son disjuntos.\n");
}

int main()
{	
	int vec_impar[13] = {0, 1, 2, 3, 4, 5, 58, 6, 4, 3, 2, 1, 0};
	int vec_par[12] = {0, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 0};


	printf("--- Vector Impar ---\n");
	if (simetria_2(vec_impar, SIZE(vec_impar)))
	{
		printf("Simetricos!\n");
	}
	else printf("No...\n");


	printf("--- Vector Par ---\n");
	if (simetria_2(vec_par, SIZE(vec_par)))
	{
		printf("Simetricos!\n");
	}
	else printf("No...\n");


	return 0;
}
