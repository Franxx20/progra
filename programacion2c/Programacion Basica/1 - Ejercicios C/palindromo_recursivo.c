#include <stdio.h>
#include <string.h>
#include <ctype.h>

int _esPalindromo(char *ini, char *fin)
{
	if(!isalpha(*ini)) {
		return _esPalindromo(ini + 1, fin);
	}
	
	if(!isalpha(*fin)) {
		return _esPalindromo(ini, fin-1);
	}

	if(*ini != *fin) {
		return 0;
	}

	if(ini == fin) {
		return 1;
	}

	return _esPalindromo(ini + 1, fin - 1);
}

int esPalindromo(char *str)
{
	int fin = strlen(str) - 1;
	return _esPalindromo(str, str + fin);
}

int main() 
{
	char *str = "arriba  la    birra";
	int rc = esPalindromo(str);
	printf("rc: %d\n", rc);
	return 0;
}