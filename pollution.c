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
//limite par l’humidité de la matière  flimhum


double flimhum(double tH2O) {
	//L'humidité est considérée comme étant de 70%, valeur pour laquelle l'humidité n'inhibe pas l'activité microbienne.
	double H1= 0.4
	double H2 =0.7
	
	if( tH2O<H1) {
		return 0;
	}
	
	if (tH2O<H2) {
		double b= (tH2O-H1)/(H2-H1);
		return b;
	}
	
	if (tH2O>H2) {
		
		return 1;
		
	}
	
	
	
	
	
}

// Croissance de la microflore

void fonctions(double x, double h)  {


	FILE * file = fopen("matdu72.csv", "w");



	//  if x> ....
	struct donnee donnee[3600];

	donnee[0].pop1=10;
	donnee[0].pop2=1000;
	donnee[0].mo_rap=1;
	donnee[0].mo_len=1;
	donnee[0].mo_subsol=10;



	double U_max=0.2;
	double Ua_max=0.003;
	double b_href =0.005;

	double Ks=0.166;  // a trouver grace a une fonction
	double Sr=0.5;  // a trouver grace a une fonction
	double Tini=25;
	double Tmax=82;
	double Tmin=0;
	double Topt=49;
	double Toptd=40;
	double ba= 0.0083;
	double flim=1;
	

	double k_href=0.009;
	double f_aero= 0.2;
	double K_hsref=0.03;



	//Etape 1 : calcul des cst neccessaire



	
	double U=U_max*Sr/(Sr+Ks);
	double Ua=Ua_max*flim;


	double Yh=0.66;
	double Tint=0;

	fprintf(file, " %s,%s, %s ,%s, %s, %s\n"," " ,"pop1","pop2","mo_rap","mo_len","mo_sol");

	//etape 2 : on rempli des tableau de croissance en fonction du temps
for( int t=0; t<3600; t++){
	
	
// Température à l'interieur du compost	

	if (t<20*24) {
	 Tint = Tini+0.083*t;
		}
	
	else { Tint= -t+85;}

//Calcule des constantes dépandates du temps
	double flimT = ((Tint-Tmax)*pow((Tint-Tmin),2))/((Topt-Tmin)*((Topt-Tmin)*(Tint-Topt)-(Topt-Tmax)*(Topt+Tmin-2*Tint)));

	
	double bh=b_href*pow(1.066,(Tint-Toptd))-pow(1.21,((Tint-Tmax)));
		if (bh<0.00001){
			
			break;
		}
		
	
//		fprintf(file, "%f",bh);
//		fprintf(file, ",");
		fprintf(file, "%d",t);
		fprintf(file, ",");
		
	double flimhydSB= (donnee[t].mo_len/donnee[t].pop1)/(0.5+donnee[t].mo_len/donnee[t].pop1);
	double K_hs=K_hsref*flimhydSB;
// haha
	double flimhydRB=1/(t+1);
	double K_h=k_href*flimhydRB;
	
	//pop1 -----> bacteries hetero ( noté Xh)
	

	donnee[t+1].pop1=floor(donnee[t].pop1*U_max*donnee[t].mo_subsol*flimT/(donnee[t].mo_subsol+Ks)-bh*donnee[t].pop1+donnee[t].pop1);
	

		fprintf(file, "%.05f",donnee[t+1].pop1 );
				fprintf(file, ",");

	//pop2  ----> bacteries auto

	donnee[t+1].pop2=floor(donnee[t].pop2*Ua*2-donnee[t].pop2*ba+donnee[t].pop2);

		fprintf(file, "%.05f",donnee[t+1].pop2 );
		fprintf(file, ",");
	// Dégradation de la matière organique rapidement biodégradable

	donnee[t+1].mo_rap=donnee[t].mo_rap-K_h*donnee[t].mo_rap+(1-f_aero)*bh*donnee[t].pop1;

		fprintf(file, "%.05f",donnee[t+1].mo_rap );
				fprintf(file, ",");


	//Dégradation de la matière lentement biodégradable


	donnee[t+1].mo_len=-K_hs*donnee[t].mo_len+donnee[t].mo_len;

		fprintf(file, "%.05f",donnee[t+1].mo_len );
				fprintf(file, ",");
		

	// Dégradation du substrat soluble


	donnee[t+1].mo_subsol=	donnee[t].mo_subsol+K_h*donnee[t].mo_rap+K_hs*donnee[t].mo_len-(U*donnee[t].pop1)/Yh;
		
		fprintf(file, "%.05f",donnee[t+1].mo_subsol );
		fprintf(file, ",");
	

fprintf(file, "\n");
}


	

}


// Dégradation de la matière organique






void afficher(double h) {

	printf( "Latitude: %f\n ,", h);

	}







int main(int argc, char * argv[]) {



	fonctions(1, 1) ;



}
