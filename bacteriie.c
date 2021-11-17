
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



struct position {

	double c;
	int x;
	int y;
	int vect[2];
	int dirx;
	int diry;

};


int arround( double o) {

 return (int) floor(o+0.5);

}

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

		printf("%0.2f ", tableau[j]);
		fprintf(file, "%0.2f ", tableau[j]);
//		fprintf(file, ",");


}

}

void initial(struct position robot ){

	srand(time(NULL));
    double randomDomaine = RAND_MAX + 1.0;

	int pos_alea_x = (int) (rand() / randomDomaine * 100);
	int pos_alea_y = (int) (rand() / randomDomaine * 100);

	robot.x=pos_alea_x;
	robot.y=pos_alea_y;
	robot.c=0;
	robot.dirx=1;
	robot.diry=1;
	robot.vect[0]=1;
	robot.vect[1]=1;
	printf("(%d, %d) \n", robot.x, robot.y);

}

void deplacement(struct position robot, double * tableau){


	int i = robot.y*100 + robot.x;
	printf("\n i = (%d)", i);
	printf("%f", tableau[i]);
	srand(time(NULL));
    double randomDomaine = RAND_MAX + 1.0;
	int iy = (int) (rand() / randomDomaine * 3);

	if ((robot.x>99) || (robot.x<0)||(robot.y>99) || (robot.y<0)) {
		robot.dirx=-robot.dirx;
		robot.diry=-robot.diry;
	}

	else {
		if (tableau[i]< robot.c){
			int direction[]={-1,1,0};
			int ix =(int) (rand() / randomDomaine * 3);
			if (ix==2) {
				iy =(int) (rand() / randomDomaine * 2);}
		else {
			iy =(int) (rand() / randomDomaine * 3);}
		robot.dirx=direction[ix];
		robot.diry=direction[iy];
		}}

	robot.c=tableau[i];
	printf("ca marche ?");

	affichercapteur(robot);
	printf("ca marche ?");
	robot.x+=robot.dirx;
	printf("ca marche ?");
	robot.y+=robot.diry;
	printf("ca marche ?");
	robot.vect[0]+=robot.dirx;
	printf("ca marche ?");
	robot.vect[1]+=robot.diry;
	printf("ca marche ?");


}


void rencontre(struct position robot[3], int n, double * tableau ) {

	for ( int i=0 ; i<n-1; i++){
		for ( int j=i ; j<n; j++){
			if (robot[i].x==robot[j].x && robot[i].y==robot[j].y) {

				//on compare la position de certaines bactéries/libellules(robots)
				//elles se partagent les infos --> amélioration de la tendance générale (direction générale)

				robot[i].vect[0]=robot[j].vect[0]+robot[i].vect[0];
				robot[i].vect[1]=robot[j].vect[1]+robot[i].vect[1];

				robot[j].vect[0]=robot[i].vect[0];
				robot[j].vect[1]=robot[i].vect[1];

				//on normalise la tendance générale pour faire avancer les robots(bactéries-libbellules) d'un vecteur unitaire dans la direction idéale

				robot[i].dirx=arround(robot[i].vect[0]/sqrt(robot[i].vect[0]+robot[i].vect[1]));
				robot[i].diry=arround(robot[i].vect[1]/sqrt(robot[i].vect[0]+robot[i].vect[1]));

				robot[j].dirx=robot[i].dirx;
				robot[j].diry=robot[i].diry;

				robot[i].x+=robot[i].dirx;
				robot[i].y+=robot[i].diry;

				robot[j].x+=robot[j].dirx;
				robot[j].y+=robot[j].diry;

				//on oublie pas d'update les concentrations !

				int position_c = robot[i].y*100+robot[i].x;
				robot[i].c=tableau[position_c];
				robot[j].c=tableau[position_c];
			}
		}
	}
 }


int main(int argc, char * argv[]) {

	FILE * trace1 = fopen("trace1.csv", "w");

	double * terrain = malloc(100*100*sizeof(double));
	struct position solute1={100,56,13};
	struct position robot[100];
	gradc(terrain, solute1);

	for (int i=0; i<3; i++){
		printf("robot[%d] :  ",i);
		initial(robot[i]); //on initialise tous nos robots (position de manière aléatoire, etc.)
	}

	//boucle pour faire avancer nos petites bactéries 600 fois
	for (int t=0; t<600; t++){

		for (int i=0; i<3; i++){
			printf("%d",i);
			deplacement(robot[i],terrain);
			printf("H2%d",i);
			fprintf(trace1, "  %d,  %d \n ",robot[i].x, robot[i].y);
			int jr= robot[i].y*100+robot[i].x;
			int js= solute1.y*100+solute1.x;
			if (jr==js) break;
		}
		rencontre(robot,3, terrain);

	}



	free(terrain);

	return 0;

}
