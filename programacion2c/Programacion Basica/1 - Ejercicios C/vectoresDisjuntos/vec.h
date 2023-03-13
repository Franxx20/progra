#ifndef VEC_H
#define VEC_H

#define OK		0
#define NOT_OK	1
#define SIZE(x)	sizeof(x)/sizeof(x[0])
#define DEBUG 1


int disjuntos(int *v1, int *v2, int s1, int s2);
int simetria(int *v1, int s1);
int simetria_2(int *v1, int s1);

#endif