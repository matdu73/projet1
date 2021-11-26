
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reponse{
	
	char phrase[100];

};

void input( char * question, struct reponse * a ) {

   printf(question);
   gets(a->phrase);

}



int main(){
	
	struct reponse a ;
	input("nombre de bacteries souhaite : ",&a);
	printf(" il y aura %s bacteries\n", a.phrase );
	int n = strtol(a.phrase, NULL, 10);
	printf(" il y aura %d bacteries\n", n );
	
	return 0;
	
}
