
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


int input( char* question ) {

   char str[100];

   printf( question);
   gets( str );

   printf( "\nYou entered: %s", str);


   return 0;
}
