#ifndef MY_STRINGS_H
#define MY_STRINGS_H

int str_len(const char *str);
/*
 *						[str_ntok]
 * strtok Pero puede tomar mas de un separador de cade,
 * [Nota Importante]: Liberar el puntero asignado antes de su repetido uso.
 */
char *str_ntok(char *str, const char *sep);
int str_ncmp(const char *s1, const char *s2, size_t n);
char *str_str(const char *pajar, const char *aguja);
size_t str_cspn(const char *str, const char *reject);
void *mem_move(void *dest, const void* src, size_t n);


#endif
