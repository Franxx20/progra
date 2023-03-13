/* ----------------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
/* ----------------------------------------------------------------------------------- */
int assert(const char* expected, const char* result) {
	if (!expected || !result) {
		return ERR;
	}

	FILE *f_exp = fopen(expected, "rt");
	FILE *f_res = fopen(result, "rt");
	char *s_exp = calloc(STR_SIZE, sizeof(char));
	char *s_res = calloc(STR_SIZE, sizeof(char));

	if ((!f_exp || !f_res) || (!s_exp || !s_res)) {
		return ERR;
	}

	while (fgets(s_exp, STR_SIZE, f_exp) && fgets(s_res, STR_SIZE, f_res)) {
		if (strcmp(s_exp, s_res)) {
			return ERR;
		}
	}
	
	fclose(f_exp);
	fclose(f_res);
	free(s_exp);
	free(s_res);

	return OK;
}
/* ----------------------------------------------------------------------------------- */