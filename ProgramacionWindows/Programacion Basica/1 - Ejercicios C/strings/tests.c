#include <stdio.h>
#include <string.h>
#include "my_strings.h"

#define good	"\033[0;34m"
#define bad		"\033[0;35m"
#define reset	"\033[0m"

int main()
{
	char str_1[] = "Looks like it's GOING to be a hot night",
		 str_2[] = "Looks like it's going to be a cold night";
	
	puts("Beginning str_len Test...");
	{
		if(str_len(str_1) == 39 && str_len(str_2) == 40) {
			printf("str_len Test: %sPassed!%s\n", good, reset);
		}
		else {
			printf("str_len Test: %sFailed!%s\n", bad, reset);
		}
		puts("");
	}

	puts("Beginning str_ncmpi Test...");
	{
		if(str_ncmpi(str_1, str_2, 50) == 'h' - 'c') {
			printf("str_ncmpi Test: %sPassed!%s\n", good, reset);
		}
		else {
			printf("str_ncmpi Test: %sFailed!%s\n", bad, reset);
		}
		puts("");
	}

	puts("Beginning str_str Test...");
	{
		char *aux = str_str(str_1, "be");
		char *result = "be a hot night";
		if(str_ncmp(aux, result, str_len(result)) == 0) {
			printf("str_str Test: %sPassed!%s\n", good, reset);
		}
		else {
			printf("str_str Test: %sFailed!%s\n", bad, reset);
		}
		puts("");
	}

	puts("Beginning str_cspn Test...");
	{
		if(str_cspn(str_1, "be") == strcspn(str_1, "be")) {
			printf("str_cspn Test: %sPassed!%s\n", good, reset);
		}
		else {
			printf("str_cspn Test: %sFailed!%s\n", bad, reset);
		}
		puts("");
	}

	puts("Beginning str_chr Test...");
	{
		char *aux = str_str(str_2, "c");
		char *result = "cold night";
		if(str_ncmp(aux, result, 10) == strncmp(aux, result, 10)) {
			printf("str_chr Test: %sPassed!%s\n", good, reset);
		}
		else {
			printf("str_chr Test: %sFailed!%s\n", bad, reset);
		}
		puts("");
	}

	puts("Beginning str_ncat Test...");
	{
		str_ncat(str_2, "...", 3);
		if(str_len(str_2) == 43) {
			printf("str_ncat Test: %sPassed!%s\nResult: ", good, reset);
			puts(str_2);
		}
		else {
			printf("str_ncat Test: %sFailed!%s\n", bad, reset);
		}
		puts("");
	}

	puts("Beginning str_ncpy Test...");
	{
		char aux[50] = "";
		str_ncpy(aux, str_1, 15);

		if(str_len(aux) == 15) {
			printf("str_ncpy Test: %sPassed!%s\nResult: ", good, reset);
			puts(aux);
		}
		else {
			printf("str_ncpy Test: %sFailed!%s\n", bad, reset);
		}
		puts("");
	}

	puts("Beginning str_pbrk Test...");
	{
		char *aux = str_pbrk(str_2, "ok");

		if(str_ncmp(aux, "ooks like it's going to be a cold night...", 
			str_len(aux)) == 0) {
			printf("str_pbrk Test: %sPassed!%s\n", good, reset);
			printf("Result: %s\n", aux);
		}
		else {
			printf("str_pbrk Test: %sFailed!%s\n", bad, reset);
			printf("Result: %s\n", aux);
		}
		puts("");
	}

	return 0;
}