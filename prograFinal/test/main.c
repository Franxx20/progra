#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"../my_strings/my_strings.h"
int main()
{
//    char a[7] = "abcdefg";
//    char *ptr;
//    int i;
//    memmove( ptr, a, 5 );
//    for( i=0; i<7; i++ )
//        printf( "a[%d]=%c \n", i, a[i] );
//    printf( "\n" );
//    for( i=0; i<5; i++ )
//        printf( "ptr[%d]=%c \n", i, ptr[i] );
//    printf( "\n" );
//
//
//    char c[12] = "Hola";
//    char d[12] = "Mundo";

//    memmove(c,d,4);
//
//    for( i=0; i<12; i++ )
//        printf( "a[%d]=%c  \n", i, c[i] );
//    printf( "\n sizeof c %d strlen %d\n ",(int)sizeof(c), (int)myStrlen(c));
//    for( i=0; i<12; i++ )
//        printf( "ptr[%d]=%c \n", i, d[i] );


//    char s2[8] = "abcdefg";
//    char s1[8];
//    myStrncpy( s1, s2 ,5);
//    printf( "s2=%s\n", s2 );
//    printf( "s1=%s\n", s1 );

//    char s1[14] = "Hola ";
//    char s2[] = "amigos";
//    printf( "s1=%s\t", s1 );
//    printf( "s2=%s\n", s2 );
//    myStrcat( s1, s2 );
//    printf( "s1=%s\n", s1 );

char s[] = "Hola amigos";
 char c = 'a';
 printf( "s=%s\t", s );
 printf( "c=%c\n", c );
 printf( "strrchr=%s num=%d\n ", myStrchr( s, c ),*(char*)myStrchr( s, c ) );
    return 0;

}
