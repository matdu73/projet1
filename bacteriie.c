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
	double c=c0/(sqrt(r));
	return c;
}


void gradc(double * tableau, struct position solute){
	
	
	 FILE * file = fopen("gradientC.csv", "w");
	int i = solute.y*100 + solute.x;
	for (int j=0; j<100*100; j++){

		tableau[j]=concentration(j, solute.x, solute.y, solute.c);
		printf("%0.2f ", tableau[j]);

		if (j==i) tableau[i]=solute.c;
		else tableau[j]=concentration(j, solute.x, solute.y, solute.c);
		if (j%100==0 & j!=0) {
	//		printf("\n");
			fprintf(file, "\n");}
<<<<<<< HEAD
			
		printf("%0.2f ", tableau[j]);
		fprintf(file, "%0.2f ", tableau[j]);
//		fprintf(file, ",");


}
        
}




=======
		printf("%0.2f, ", tableau[j]);
		fprintf(file, "%0.2f, ", tableau[j]);
		
	}
}
>>>>>>> 625946f47b9267fb9f124289082dcc703e02c699

void deplacement(struct position robot, double * tableau, struct position solute){
	
	int i = robot.y*100 + robot.x;
	int i0= solute.y*100 + solute.x;
	double randomDomaine = RAND_MAX + 1.0;
    int init = (rand() / randomDomaine * 3);
	int dirx=1;
	int diry=1;
    
    while (i!= i0){
		
		if (diminution de concentration){
			dirx =(rand() / randomDomaine * 3)-1;
			diry =(rand() / randomDomaine * 3)-1;
		}
		
		robot.x+=dirx;
		robot.y+=diry;
		i = robot.y*100 + robot.x;
	
	
	
	
	
}}

int main(int argc, char * argv[]) {

	double * terrain = malloc(100*100*sizeof(double));
	
	struct position solute1 ={100,50,50};
	struct position robot1={0,10,10};
	
	//gradc(terrain, solute1);

	free(terrain);
	return 0;
}