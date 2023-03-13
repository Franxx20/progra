#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ESESPACIO(X)		((X) == ' ')
#define ESNUMERO(X)		((X) >= '0' && (X) <= '9')
#define ESMAYUS(X)		((X) >= 'A' && (X) <= 'Z')
#define ESMINUS(X)		((X) >= 'a' && (X) <= 'z')
#define ESLETRA(X)		(ESMAYUS(X) || ESMINUS(X))
#define AMINUS(X)			(ESMAYUS(X)? (X) + 32 : (X))
#define AMAYUS(X)			(ESMINUS(X)? (X) - 32 : (X))
#define ESCARACTER(X)	(ESLETRA(X) || ESNUMERO(X) || ESESPACIO(X))

void normalize(char *str);

int main()
{
	char str[1024];
	FILE *fp = fopen("archivo.txt", "rt");
	FILE *temp = fopen("temp.txt", "wt");

	if(!fp || !temp) {
		if(fp) {
			fclose(fp);
		}
		else if(temp) {
			fclose(temp);
		}
		return 0;
	}

	while(fgets(str, sizeof(str), fp)) {
		normalize(str);
		fprintf(temp, "%s\n", str);
	}

	fclose(fp);
	fclose(temp);

	remove("archivo.txt");
	rename("temp.txt", "archivo.txt");

	return 0;
}


int esEspecial(const char c)
{
	char *especiales = ".,;¿?¡!";
	int es = 0;

	for(;*especiales; especiales++) {
		if(c == *especiales) {
			es = 1;
		}
	}
	return es;
}


void normalize(char *str)
{
	do {
		unsigned firstLetter = 0;
		for(;*str && *(str) != '.'; str++) {

			if(ESLETRA(*str) && !firstLetter) {
				*str = AMAYUS(*str);
				firstLetter = 1;
			}
			else if(ESLETRA(*str)) {
				*str = AMINUS(*str);
			}
			else if(!(ESCARACTER(*str) || esEspecial(*str))) {
				int len = strlen(str+1);
				memmove(str, str+1, len);
				*(str+len) = '\0';
				str--;
			}

			if(ESESPACIO(*str)) {
				unsigned i;
				char *aux = str;

				for(i = 0; ESESPACIO(*(aux+i)); i++) {}

				if(i) {
					int len = strlen(aux+i);
					memmove(aux+1, aux+i, len);
					*(aux + len + 1) = '\0';
				}
			}
		}
		str++;
	} while(*str);
}
