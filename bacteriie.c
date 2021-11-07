#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct position {
	
	double c;
	int x;
	int y;
};


double concentration(int i, int x0, int y0, double c0){
	
	int x = i % 100;
	int y = i / 100;
	
	double r = sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0));
	double c=c0/r;
	return c;
}


void gradc(double * tableau, struct position solute){
	
	
	 FILE * file = fopen("gradientC.csv", "w");
	int i = solute.y*100 + solute.x;
	for (int j=0; j<100*100; j++){
		if (j==i) tableau[i]=solute.c;
		else tableau[j]=concentration(j, solute.x, solute.y, solute.c);
		if (j%100==0) {
			printf("\n");
			fprintf(file, "\n");}
		printf("%0.2f, ", tableau[j]);
		fprintf(file, "%0.2f, ", tableau[j]);
		
}
}






int main(int argc, char * argv[]) {

	double * terrain = malloc(100*100*sizeof(double));
	
	struct position solute1 ={100,50,50};
	
	gradc(terrain, solute1);
	

	free(terrain);
	return 0;
}
