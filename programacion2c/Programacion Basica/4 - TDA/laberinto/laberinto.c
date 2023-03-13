#include "laberinto.h"

/* private functions */
int _checkNext(int *side, int offset, int max, int *check);
int _lastPosition(Position *cur, Position *prev);


int findPath(int *path, int filas, int colum)
{
	enum dir came_from = SELF,
			 return_from = SELF;
    Position pos,
			 prev_pos;

    tPila savedPath;
    crearPila(&savedPath);

    /*init*/
	pos.x = 0;
	pos.y = 0;

    while(*MOVE(path, pos.y, pos.x) != GOAL) {

		if(!pilaVacia(&savedPath)) {
			verTope(&savedPath, &prev_pos, sizeof(Position));
			came_from = _lastPosition(&pos, &prev_pos);
		}

		if(!ponerEnPila(&savedPath, &pos, sizeof(Position)))
			return -1;

		if(came_from != UP && return_from != UP) {
			if(_checkNext(&pos.y, -1, filas, MOVE(path, pos.y-1, pos.x)))
				goto moved;
		}
		if(came_from != RIGHT && return_from != RIGHT) {
			if(_checkNext(&pos.x,  1, colum, MOVE(path, pos.y, pos.x+1)))
				goto moved;
		}
		if(came_from != DOWN && return_from != DOWN) {
			if(_checkNext(&pos.y,  1, filas, MOVE(path, pos.y+1, pos.x)))
				goto moved;
		}
		if(came_from != LEFT && return_from != LEFT) {
			if(_checkNext(&pos.x, -1, colum, MOVE(path, pos.y, pos.x-1)))
				goto moved;
		}
		if(!pilaVacia(&savedPath)) {
			sacarDePila(&savedPath, &prev_pos, sizeof(Position));
			sacarDePila(&savedPath, &pos, sizeof(Position));
			return_from = _lastPosition(&pos, &prev_pos);
		}

		continue;
	moved:
		return_from = SELF;
    }

    /* goal position */
	if(!ponerEnPila(&savedPath, &pos, sizeof(Position)))
		return -1;

	puts("{y;x}");
	puts("-----");
    while(!pilaVacia(&savedPath)) {
    	sacarDePila(&savedPath, &pos, sizeof(Position));
    	printf("{%d;%d}\n", pos.y, pos.x);
    }

    vaciarPila(&savedPath);
    return 0;
}


int _checkNext(int *side, int offset, int max, int *check)
{
    if(*side + offset < max && *side + offset >= 0 && *(check) != WALL) {
		*side += offset;
		return 1;
    }

    return 0;
}


int _lastPosition(Position *cur, Position *prev)
{
	enum dir lastPos;

	if(cur->x - prev->x > 0) { /* return_from from left */
		lastPos = LEFT;
	}
	else if(cur->y - prev->y > 0) { /* return_from from upside*/
		lastPos = UP;
	}
	else if(cur->x - prev->x < 0) { /* return_from from right */
		lastPos = RIGHT;
	}
	else if(cur->y - prev->y < 0) { /* return_from from downside*/
		lastPos = DOWN;
	}
	else lastPos = SELF;

	return lastPos;
}
