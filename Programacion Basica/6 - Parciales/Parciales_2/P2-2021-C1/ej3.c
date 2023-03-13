#include <stdio.h>
#include <string.h>

char *istrcat(char *str_1, const char *str_2)
{
	char *temp;
	const char *temp_s;
	int	s_1 = strlen(str_1),
		s_2 = strlen(str_2),
		i;

	temp = (str_1 + s_2) + s_1;
	temp_s = str_1 + s_1;

	for(i = s_1; i >= 0; i--) {
		*(--temp) = *(--temp_s);
	}

	for(i = 0; i < s_2; i++) {
		*(str_1 + i) = *(str_2 + i);
	}

	*(str_1 + s_1 + s_2) = '\0';

	return str_1;
}


int main()
{
	char str_1[40] = "mundo!";
	char str_2[] = "Hola ";
	istrcat(str_1, str_2);
	puts(str_1);
	return 0;
}