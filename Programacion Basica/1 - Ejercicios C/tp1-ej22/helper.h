#include <stdio.h>
#include <stdlib.h>

#define OK		1
#define NOT_OK	0
#define SIZE(x)	sizeof(x)/sizeof(x[0])

int insert_i(int what, int where, int *in, int size);
void printArray(int *vec, int size);