#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ESNUMERO(n)			((n) >= '0' && (n) <= '9')
#define ESMAYUS(A)			((A) >= 'A' && (A) <= 'Z')
#define ESMINUS(a)			((a) >= 'a' && (a) <= 'z')
#define ESLETRA(a)			(ESMAYUS(a) || ESMINUS(a))

#define AMAYUS(a)			(ESMINUS(a)? ((a) - 32) : (a))
#define AMINUS(A)			(ESMAYUS(A)? ((A) + 32) : (A))

int findPar(char *str);

int main()
{
	char str_1[] = "M++aee+rr+teo Es u2332n B.ss...obo", /* Cd a */
		 str_2[] = "+++__**+";       /*  */

	findPar(str_1);
	puts(str_1);

	findPar(str_2);
	puts(str_2);
	

	return 0;
}

int findPar(char *str)
{
	char new_str[56] = "";
	int i, j = 0;
	int dup = 0;

	for(i = 0; i < strlen(str); i++) {

		if( AMAYUS(*(str + i)) == AMAYUS(*(str + i + 1)) ) {
			i++;
			dup = 1;
		}
		else {
			*(new_str + j) = *(str + i);
			j++;
		}
	}

	if(dup) {
		*str = 0;
		i = 0;
		while(j--) {
			*(str+i) = *(new_str+i);
			i++;
		}
		*(str+i) = 0;

		return findPar(str);
	}


	return dup;
}