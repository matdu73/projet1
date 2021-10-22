#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




void grille( double h, double L, double l) {

double S= l*L;

double compost[h][S];












}





double fonctions(double pop1, double pop2)  {
//	bh= bh,ref×1.066Tint−Toptdeces−1.21Tint−Tmax avec bh,ref=0.005h−1
	double U_max=0.2;
	double Ua_max=0.003;
	double b_href =0.005;

	double Ks=1;  // a trouver grace a une fonction
	double Sr=1;  // a trouver grace a une fonction
	double Tint=25;
	double Tmax=82;
	double Topt=49;
	double ba= 0.0083;
	double flim=1;
	// on va l'avoir avec une autre fonction double Sr=

	
	//Etape 1 : calcul des cst de deces et de vie des bacteries
	double bh=b_href*pow(1.066,(Tint-Topt))-pow(1.21,((Tint-Tmax)));
	double U=U_max*Sr/(Sr+Ks);
	double Ua=Ua_max*flim;
	
	//etape 2 : on calcul la population de bactéries en fonctions du temps
for( int time=0; time<3600; time++){
	
	pop1=pop1*U-bh*pop1+pop1;
	
	pop2=pop2*Ua-pop2*ba+pop2;
	
	return pop1;
	
}
	

	

	
	
	
	
}
	
	
	
	
void afficher(double h) {

	printf( "Latitude: %f\n ,", h);
	
	}


int main(int argc, char * argv[]) {
	
	
	afficher(fonctions(100,100));
	
	
	
	
	
}
	
	

	
	
	
	
