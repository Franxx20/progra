#ifndef MY_STRINGS_H_INCLUDED
#define MY_STRINGS_H_INCLUDED
#include<stddef.h>
void  myMemcpy(void * destino, const void * origen, size_t num);
void myMemMove(void * destino, void * origen, size_t n);
size_t myStrlen(const char * s);
char *  myStrcpy(char * s1, const char * s2);
char * myStrncpy(char * d, const char * o, size_t n);

char *myStrcat(char *s1, const char *s2);


char * myStrrchr(char * s, int n);
char * myStrchr(char * s, int n);

int myStrcmp(const char * s1, const char * s2);
#endif // MY_STRINGS_H_INCLUDED
