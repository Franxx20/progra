#include <stdio.h>
#include "../src/assert.h"

int main() {
	printf("%d\n", assert("expected.txt", "file.txt"));
	printf("%d\n", assert("expected.txt", "file2.txt"));
	return 0;
}