#include <stdio.h>
#include "pilaDinamica/pila.h"

#define MAX_FILAS	5
#define MAX_COLUM	7
#define WALL 0
#define GOAL 2
#define MOVE(X,Y,Z) ((X) + (Y) * MAX_COLUM + (Z))

typedef struct pos
{
	int y, x;

} Position;

enum dir{UP, RIGHT, DOWN, LEFT, SELF};


int findPath(int *path, int filas, int colum);
