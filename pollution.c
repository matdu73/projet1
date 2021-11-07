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
	
	double H1= 0.2;
	double H2 =0.7;
	
	if( tH2O<H1) {
		return 0;
	}
	
	if (tH2O<H2) {
		double b= (tH2O-H1)/(H2-H1);
		return b;
	}
	
	else  {
		
		return 1;
		
	}
	
	
}

// Croissance de la microflore

void fonctions(double x, double h)  {


	FILE * file = fopen("matdu72.csv", "w");




	struct donnee donnee[3600];

	donnee[0].pop1=10;
	donnee[0].pop2=1000;
	donnee[0].mo_rap=1;
	donnee[0].mo_len=1;
	donnee[0].mo_subsol=10000;
	
//cste------------------------------------------------------------------

	double K02h=0.05;
	double K02a=0.1;
	double Kxrb=0.5;
	double Kxsb=0.5;
	double Knh=1.5;
	double Ks=0.166;
	
	double tNxi=0.08;
	double tNxh=0.08;
	
	double Yh=0.66;
	double YC02h=1.375;
	double YH20h=0.2;
	double Yn03=33;	
	

	
	double Uh_max=0.2;
	double Ua_max=0.03;
	
	double b_href =0.005;
	double ba= 0.0083;
	double kHRref=0.009;
	double f_Iaero= 0.2;
	double kHSref=0.003;



	
//températures------------------------------	

	double Tini=25;
	double Tmax=82;
	double Tmin=0;
	double Topt=49;
	double Toptd=40;

	



	double Tintnit=Tini; //en réalité =Text
	double Tmaxnit = 40;
	double Tminnit=0;
	double Toptnit=32;
	

	//Etape 1 : calcul des cst neccessaire

	double flimT=0;
	double Tint=0;
	double bh=0.7;
	double Uh=1;
	double Ua=0;

	double flimHum = 2;
	double flim02h=0;
	double flimNav =0;
	double flimHydXRB=0;
	double flimHydXSB=0;
	double r02biofilm=0;
	double rC02=0;
	double H20h=0;
	double NXa=1;
	double NXh=1;
	double NXsb=1;
	double NXrb=0;
	double flimTnit=0;
	double flim02a=0;
	double Nav=1;
	double kHS = 0;
	double kHR = 0;
	double tH2O=1;
	double p02biofilm=1;
	double p02int=1;
	

	fprintf(file, "%s, %s ,%s, %s, %s\n","" ," t" ,"pop1","mo_len","mo_sol");

	//etape 2 : on rempli des tableau de croissance en fonction du temps
	
for( int t=0; t<3600; t++){
	
// Température à l'interieur du compost	

	if (t<20*24) {
	 Tint = Tini+0.083*t;
		}
	else { Tint= -t+85;}
	
	

//Calcule des constantes dépandates du temps
	 flimT = ((Tint-Tmax)*pow((Tint-Tmin),2))/((Topt-Tmin)*((Topt-Tmin)*(Tint-Topt)-(Topt-Tmax)*(Topt+Tmin-2*Tint)));


//Calcule des constantes dépendantes du temps


	bh=b_href*pow(1.066,(Tint-Toptd))-pow(1.21,((Tint-Tmax)));
	
	Uh=Uh_max*donnee[t].mo_subsol/(donnee[t].mo_subsol+Ks);
	//*flimT*flim02h*flimHum*flimNav;
	Ua=Ua_max*flimTnit*flim02a*flimHum*flimNav;


		if (bh<0.00001){
			
			break;
	}

		
	
//		fprintf(file, "%f",bh);
//		fprintf(file, ",");
		fprintf(file, "%d",t);
		fprintf(file, ",");
		

//---------------------calcul des flim a la con-------------------------------------------------

//flimT et flimTnit
if (Tintnit>Tmaxnit || Tintnit< Tminnit) flimTnit = 0;
else flimTnit = ((Tintnit-Tmaxnit)*pow((Tintnit-Tminnit),2))/((Toptnit-Tminnit)*((Toptnit-Tminnit)*(Tintnit-Toptnit)-(Toptnit-Tmaxnit)*(Toptnit+Tminnit-2*Tintnit)));

flimT = ((Tint-Tmax)*pow((Tint-Tmin),2))/((Topt-Tmin)*((Topt-Tmin)*(Tint-Topt)-(Topt-Tmax)*(Topt+Tmin-2*Tint)));

//flimHum --> il manque tH20, lien avec dH20?

flimhum(tH2O);
	
//	flim02h --> il manque p02biofilm, doit avoir un rapport avec r02 non ?
flim02h= p02biofilm/(p02biofilm+K02h);
 
//	flim02a --> il manque p02int....
flim02a= p02int/(p02int+K02a);

// flimNav 
flimNav = Nav/(Nav+Knh);

//flimHydXRB 

double dNXidt= bh*donnee[t].pop1*tNxi*f_Iaero*(1+(-ba*NXa)/(-bh*donnee[t].pop1*tNxh));
NXa+=(Ua-ba)*NXa;  //il manque XNa initial
NXh+=tNxh*donnee[t].pop1;
NXrb+=-kHR*NXrb-(-bh*donnee[t].pop1*tNxh-ba*NXa+dNXidt);

flimHydXRB=(NXrb/NXh)/(Kxrb+(NXrb/NXh));

//flimHydXSB

flimHydXSB=(donnee[t].mo_len/donnee[t].pop1)/(Kxsb+(donnee[t].mo_len/donnee[t].pop1));

//Nav
NXsb+= -kHS*NXsb; //pas de valeur initiale...
Nav+=(kHR*NXrb+kHS*NXsb)-(Uh*donnee[t].pop1*tNxh+(Ua*NXa)*(1+Yn03));



//calcul des conso et prod des microorganismes -------------------------------------------

//02
r02biofilm= -((1-Yh)/Yh)*Uh*donnee[t].pop1;

//co2
rC02=(YC02h/Yh)*Uh*donnee[t].pop1;

//H20h
H20h+=(YH20h/Yh)*Uh*donnee[t].pop1;


//calcul K

kHS = kHSref*flimHum*flimHydXSB;
kHR= kHRref*flimHum*flimHydXRB;

//---------------------------------------------------------


		fprintf(file, "%d",t);
		fprintf(file, ",");
		

//pop1 -----> bacteries hetero ( noté Xh)


	donnee[t+1].pop1=donnee[t].pop1*Uh-bh*donnee[t].pop1+donnee[t].pop1;



		fprintf(file, "%.05f",donnee[t+1].pop1 );
				fprintf(file, ",");

//pop2  ----> bacteries auto ( noté Xa)

//	donnee[t+1].pop2=floor(donnee[t].pop2*Ua*2-donnee[t].pop2*ba+donnee[t].pop2);

//		fprintf(file, "%.05f",donnee[t+1].pop2 );
//		fprintf(file, ",");
		
// Dégradation de la matière organique rapidement biodégradable (noté Xrb)

//	donnee[t+1].mo_rap=donnee[t].mo_rap-kHR*donnee[t].mo_rap+(1-f_Iaero)*bh*donnee[t].pop1;

	//	fprintf(file, "%.05f",donnee[t+1].mo_rap );
		//		fprintf(file, ",");


//Dégradation de la matière lentement biodégradable (noté Xsb)


	donnee[t+1].mo_len=-kHS*donnee[t].mo_len+donnee[t].mo_len;

		fprintf(file, "%.05f",donnee[t+1].mo_len );
				fprintf(file, ",");
		

// Dégradation du substrat soluble (noté Sr)


	donnee[t+1].mo_subsol=	donnee[t].mo_subsol+kHR*donnee[t].mo_rap+kHS*donnee[t].mo_len-(Uh*donnee[t].pop1)/Yh;
		
		fprintf(file, "%.05f",donnee[t+1].mo_subsol );
		fprintf(file, ",");
	

fprintf(file, "\n");
//-------------------------------------------------------------------
}


	

}


// Dégradation de la matière organique






void afficher(double h) {

	printf( "Latitude: %f\n ,", h);

	}







int main(int argc, char * argv[]) {


	fonctions(1, 1) ;


}
