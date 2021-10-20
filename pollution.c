#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>



struct objet {
		float x;
		float y;
		int c;
	};
	

void comptage(float x, float y, float r, struct objet * capteur ){
	
	
	for (int i=0;i<6;i++) {
		if (sqrt((capteur[i].x-x)*(capteur[i].x-x)+(capteur[i].y-y)*(capteur[i].y-y))<=r){
			capteur[i].c+= 1;
			
		}}		
}			

	
void nuage(float x, float y, float r, struct objet * capteur){ //en km, km et m
	float rayon=r;
	float xf=x;
	float yf=y;
	srand(time(NULL));
    double randomDomaine = RAND_MAX + 1.0;
    double init = rand() / randomDomaine * 0.03;
	while ((xf<8 && xf>0) && (yf>0 && yf<5)) {
		rayon=rayon+20/rayon;
		double ax = (rand() / randomDomaine * 0.03)-0.015;
		//printf("%f\n",ax);
		double ay = (rand() / randomDomaine * 0.03)-0.015;
		yf+=-0.001*(xf-2)+ay;
		xf+=0.01+ax;
		//comptage(xf,yf,rayon,capteur);
		//printf("%f,%f,%f\n",xf,yf,rayon);
		for (int i=0;i<6;i++){
			//printf("%f\n",capteur[i].x);
		if (sqrt((capteur[i].x-xf)*(capteur[i].x-xf)+(capteur[i].y-yf)*(capteur[i].y-yf))<=(rayon/1000)){
			capteur[i].c= capteur[i].c+1;}
}}

printf("Le paquet quitte la zone d'interet a x =%0.2f km et y=%0.2f km avec un rayon de r =%0.2f. \n voici le comptage :\n", xf, yf, rayon);

}


void paquets(float x, float y, float r, struct objet * capteur ){ 
	
	for ( int i=0; i<100; i++) {
		nuage(x,y,r,capteur);
	}}


int main(int argc, char * argv[]) {
	
struct objet capteur[6];	
capteur[0].x = 7.340;
capteur[0].y = 4.020;
capteur[0].c= 0;
capteur[1].x = 7.500;
capteur[1].y = 2.880;
capteur[1].c= 0;
capteur[2].x = 7.420;
capteur[2].y = 1.910;
capteur[2].c= 0;
capteur[3].x = 7.250;
capteur[3].y = 1.340;
capteur[3].c= 0;
capteur[4].x = 7.380;
capteur[4].y = 0.720;
capteur[4].c= 0;
capteur[5].x = 6.200;
capteur[5].y = 0.280;
capteur[5].c= 0;


for ( int i=0; i<100; i++) {
		nuage(2.5,3.1,10,capteur);
	}
//paquets(2.5,3.1,10,capteur);

printf("voici le decompte : \n capteur 1: %d; \n capteur 2: %d; \n capteur 3: %d; \ncapteur 4: %d; \ncapteur 5: %d; \ncapteur 6: %d;  \n" ,  capteur[0].c/100 , capteur[1].c/100 , capteur[2].c/100 , capteur[3].c/100, capteur[4].c/100, capteur[5].c/100);

}


