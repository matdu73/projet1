#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct donnee {
	double pop1;
	double pop2;
	double mo_rap;
	double mo_len;
	double mo_subsol;
	double x;
	double y;
};




/*
void grille( double h, double L, double l) {

double S= l*L;

double compost[h][S];





}
*/


// Croissance de la microflore

void fonctions(double x, double y, double h)  {


	FILE * file = fopen("lol.csv", "w");



	//  if x> ....
	struct donnee donnee[3600];

	donnee[0].pop1=10;
	donnee[0].pop2=10;
	donnee[0].mo_rap=1;
	donnee[0].mo_len=1;
	donnee[0].mo_subsol=10;



	double U_max=0.2;
	double Ua_max=0.003;
	double b_href =0.005;

	double Ks=0.166;  // a trouver grace a une fonction
	double Sr=0.5;  // a trouver grace a une fonction
	double Tint=25;
	double Tmax=82;
	double Topt=49;
	double ba= 0.0083;
	double flim=1;

	double k_href=0.009;
	double f_aero= 0.2;
	double K_hsref=0.03;



	//Etape 1 : calcul des cst neccessaire

	double bh=b_href*pow(1.066,(Tint-Topt))-pow(1.21,((Tint-Tmax)));
	double U=U_max*Sr/(Sr+Ks);
	double Ua=Ua_max*flim;
	double K_h=k_href*flim;
	double K_hs=K_hsref*flim;
	double Yh=0.66;

		fprintf(file, " %s,%s,%s, %s ,%s, %s, %s\n"," "," " ,"pop1","pop2","mo_rap","mo_len","mo_sol");

	//etape 2 : on rempli des tableau de croissance en fonction du temps
for( int t=0; t<3600; t++){

	
		fprintf(file, ",");
		fprintf(file, "%d",t);
	//pop1 -----> bacteries hetero ( noté Xh)

	donnee[t+1].pop1=donnee[t].pop1*U_max*Sr/(Sr+Ks);-bh*donnee[t].pop1+donnee[t].pop1;
	
		fprintf(file, ",");
		fprintf(file, "%.05f",donnee[t+1].pop1 );

	//pop2  ----> bacteries auto

	donnee[t+1].pop2=donnee[t].pop2*Ua-donnee[t].pop2*ba+donnee[t].pop2;
		fprintf(file, ",");
		fprintf(file, "%.05f",donnee[t+1].pop2 );

	// Dégradation de la matière organique rapidement biodégradable

	donnee[t+1].mo_rap=donnee[t].mo_rap-K_h*donnee[t].mo_rap+(1-f_aero)*bh*donnee[t].pop1;
			fprintf(file, ",");
		fprintf(file, "%.05f",donnee[t+1].mo_rap );


	//Dégradation de la matière lentement biodégradable


	donnee[t+1].mo_len=-K_hs*donnee[t].mo_len+donnee[t].mo_len;
				fprintf(file, ",");
		fprintf(file, "%.05f",donnee[t+1].mo_len );
		

	// Dégradation du substrat soluble


	donnee[t+1].mo_subsol=	donnee[t].mo_subsol+K_h*donnee[t].mo_rap+K_hs*donnee[t].mo_len-(U*donnee[t].pop1)/Yh;
		fprintf(file, ",");
		fprintf(file, "%.05f",donnee[t+1].mo_subsol );
	

fprintf(file, "\n");
}
	








}


// Dégradation de la matière organique






void afficher(double h) {

	printf( "Latitude: %f\n ,", h);

	}







int main(int argc, char * argv[]) {



	fonctions(1, 1, 12) ;



}
