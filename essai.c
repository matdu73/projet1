#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct position {
	
	double c;
	int x;
	int y;
	int vect;
	

};


double concentration(int i, int x0, int y0, double c0){
	
	int x = i % 100;
	int y = i / 100;
	double r = sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0));
	double c=c0/(sqrt(r));
	return c;
}

void affichercapteur(struct position * libelule) {
    
    printf(" x =  %d  y : %d\n ",libelule->x,libelule->y  );

}

void gradc(double * tableau, struct position solute){
	
	
	 FILE * gradient = fopen("gradientC.csv", "w");
	int i = solute.y*100 + solute.x;
	for (int j=0; j<100*100; j++){

		tableau[j]=concentration(j, solute.x, solute.y, solute.c);
	//	printf("%0.2f ", tableau[j]);
	
		if (j==i) tableau[i]=solute.c;
		else tableau[j]=concentration(j, solute.x, solute.y, solute.c);
		
		if ((j%100==0) & (j!=0)) {
	 //		printf("\n");
			fprintf(gradient, "\n");}

	//	printf("%0.2f ", tableau[j]);
		fprintf(gradient, "%0.2f ", tableau[j]);
//		fprintf(file, ",");

	}
}

void initial(struct position robot ){

	srand(time(NULL));
    double randomDomaine = RAND_MAX + 1.0;
   	int pos_alea_x =1;
   	int pos_alea_y=3;


		pos_alea_x = (int) (rand() / randomDomaine * 100);
		pos_alea_y = (int) (rand() / randomDomaine * 100);
	
		robot.x=pos_alea_x;
		
		
		robot.y=pos_alea_y;
		printf(" x =  %d  y : %d\n ",robot.x,robot.y );
		
			
	
	
	
	
}






void deplacement(struct position robot, double * tableau, struct position solute){
	

	FILE * trace = fopen("trace.csv", "w");
	int i = robot.y*100 + robot.x;
	int i0= solute.y*100 + solute.x;
	srand(time(NULL));
    double randomDomaine = RAND_MAX + 1.0;
    

	int iy = (int) (rand() / randomDomaine * 3);
	int dirx=1;
	int diry=1;
    double	c_avant=tableau[i];
    
    

		
// si on sort du bord on prend la direction opposée

	if ((robot.x>99) || (robot.x<0)||(robot.y>99) || (robot.y<0)) {
		dirx=-dirx;
		diry=-diry;
	} 
	

	if (tableau[i]< c_avant){ 
		int tableau[]={-1,1,0};	
		int ix =(int) (rand() / randomDomaine * 3);
		if (ix==2) {
			iy =(int) (rand() / randomDomaine * 2);}
		else {
			iy =(int) (rand() / randomDomaine * 3);}
		dirx=tableau[ix];
		diry=tableau[iy];
		robot.vect= diry*100+dirx+robot.vect;
		}

	c_avant=tableau[i];
	fprintf(trace, "   %d,   %d\n ",robot.x,robot.y);
	affichercapteur(&robot);
	robot.x+=dirx;
	robot.y+=diry;
	robot.vect= diry+1*100+dirx+1+robot.vect;
	
	i = robot.y*100 + robot.x;
}


void rencontre(struct position * robot[2]) {
	int temps =0;
	int nombre_de-bact=2
	double * terrain = malloc(100*100*sizeof(double));

	struct position solute1 ={1000,40,56}; // on initialise la position du soluté

	initial(robot[0]); 	// on initialise la position initiale du premier robot
	
	gradc(terrain, solute1);   // gradient de concentration
	
	
	// on repete l'action de deplacement 1000 fois
	while (t<1000) {
		// on repete cette action de deplacement pour toute les bacteries
		
		for( int i=0 ; i<nombre_de-bact; i++){
			
			deplacement(intial(robot[i]), tableau, solute1)
			
			// je verifie que pour les deux premieres pour l'instant
			
			if (robot[0].x=robot[1].x && robot[0].y=robot[1].y) {
				
				
			
			
			
			}
			
			
			
			
			
			
			
			
			
			
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
}



int main(int argc, char * argv[]) {

	double * terrain = malloc(100*100*sizeof(double));

	struct position solute1 ={1000,40,56};
	struct position robot[100];
	
initial(robot[0]);


	

	gradc(terrain, solute1);
	deplacement(robot[0],terrain, solute1);
	
	



	free(terrain);
	
	
	
	return 0;
	
}
