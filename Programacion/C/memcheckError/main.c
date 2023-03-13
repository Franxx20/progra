#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *x = malloc(10 * sizeof(int));
  x[10] = 0;
  // Problem 1: heap block overrrun
  // Problem 2: memery leak -- x not freed

  return 0;
}
