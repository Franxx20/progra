#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void intercambio(void *dest, void* src, size_t n)
{
	int i;
	char *aux_1 = malloc(n);
	char *aux_2 = malloc(n);

	for(i = 0; i < n; i ++)
	{
		aux_1[i] = *((char *)src + i);
		aux_2[i] = *((char *)dest + i);
	}
	for(i = 0; i < n; i ++)
	{
		*((char *)src + i)  = aux_2[i];
		*((char *)dest + i) = aux_1[i];
	}
}


int main()
{
	char str_1[] = "hola mundo",
		 str_2[] = "chau mundo";

	int vec1[4] = {16,  7, 3,  4},
		vec2[7] = {12, 34, 9, 45},
		i;

	intercambio(str_2, str_1, sizeof(str_1));
	printf("str_1: %s\n", str_1);
	printf("str_2: %s\n", str_2);

	intercambio(vec2, vec1, 2 * sizeof(int));
	printf("vec1:\n");
	for(i = 0; i < 4; i++)
		printf("%d ", vec1[i]);
	
	printf("\nvec2:\n");
	for(i = 0; i < 4; i++)
		printf("%d ", vec2[i]);
	
	printf("\n");
	return 0;
}