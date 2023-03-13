#include "laberinto.h"

int main()
{
	int laberinto[MAX_FILAS][MAX_COLUM] = {
	  /* 0  1  2  3  4  5  6 */
        {1, 1, 0, 1, 0, 1, 1}, /*0*/
        {0, 1, 0, 1, 0, 0, 1}, /*1*/
        {0, 1, 0, 1, 1, 1, 1}, /*2*/
        {1, 1, 1, 1, 1, 0, 0}, /*3*/
        {0, 0, 1, 0, 1, 1, 2}  /*4*/
	};


	if(findPath(*laberinto, MAX_FILAS, MAX_COLUM) != 0) {
    puts("[ERROR] - Out of Memory.");
  }


    return 0;
}
