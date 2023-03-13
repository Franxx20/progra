#ifndef MY_STRINGS_H
#define MY_STRINGS_H


#define ESMAYUS(A)			(A >= 'A' && A <= 'Z')
#define ESMINUS(a)			(a >= 'a' && a <= 'z')
#define ESLETRA(a)			(ESMAYUS(a) || ESMINUS(a))

#define AMAYUS(a)			(ESMINUS(a)? ((a) - 32) : (a))
#define AMINUS(A)			(ESMAYUS(A)? ((A) + 32) : (A))


size_t str_len(const char *str);
int str_ncmp(const char *s1, const char *s2, size_t n);
int str_ncmpi(const char *s1, const char *s2, size_t n);
char *str_str(const char *pajar, const char *aguja);
size_t str_cspn(const char *str, const char *reject);
size_t str_spn(const char *str, const char *accept);
char *str_chr(const char *str, char c);
char *str_ncat(char *dest, const char *src, size_t n);
char *str_ncpy(char *dest, const char *src, size_t n);
char *str_pbrk(const char *s1, const char *s2);
void *mem_move(void *dest, const void* src, size_t n);


/*						[str_ntok]
 * strtok Pero puede tomar mas de un separador de cade,
 * [Nota Importante]: Liberar el puntero asignado antes de su repetido uso.
 */
char *str_ntok(char *str, const char *sep);
char *proxPalabra(char **str);

#endif
