<<<<<<< HEAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reponse{
  
  char phrase[100];

};

void input( char * question, struct reponse * a ) {

   printf("%s",question);
   gets(a->phrase);

}


struct position {
 
  double c;
  int x;
  int y;
  int vect[2];
  int dirx;
  int diry;
  int rencontre;
  int couleur;
  int add;


};

int arround( double o) {

  return (int) floor(o+0.5);
 
}

double concentration(int i, int x0, int y0, double c0){
  
  int x = i % 100;
  int y = i / 100;
  double r = sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0));
  double c=(c0/r);
  return c;
}


void gradc(double * tableau, struct  position solute){
  
  
  FILE * gradient = fopen("gradientC.csv", "w");
  int i = solute.y*100 + solute.x;
  for (int j=0; j<100*100; j++){

    tableau[j]=concentration(j, solute.x, solute.y, solute.c);
  //printf("%0.2f ", tableau[j]);
  
    if (j==i) tableau[i]=solute.c;
    else tableau[j]=concentration(j, solute.x, solute.y, solute.c);
    
    if ((j%100==0) & (j!=0)) {
    //printf("\n");
    fprintf(gradient, "\n");}

  //printf("%0.2f ", tableau[j]);
    fprintf(gradient, "%0.2f ", tableau[j]);
  //fprintf(file, ",");

  }
}

void initial(struct position * robot){

	



  double randomDomaine = RAND_MAX + 1.0;
  

  //int pos_alea_x = (int) (rand() / randomDomaine * 100);
  int pos_alea_y = (int) (rand() / randomDomaine * 100);
 if (robot->couleur==0){
  robot->dirx=1;
  robot->c=0; 
  robot->diry=1;
  robot->x=0;
  robot->y=pos_alea_y;
  robot->vect[0]=1;
  robot->vect[1]=1;
  robot->rencontre=0;
  robot->add=0;
  
  
  }
  
   if (robot->couleur==1){
  robot->dirx=1;
  robot->c=0; 
  robot->diry=1;
  robot->x=99;
  robot->y=pos_alea_y;
  robot->vect[0]=1;
  robot->vect[1]=1;
  robot->rencontre=0;
    robot->add=0;
  }
  
  
  
  
  //printf("(%d, %d) \n", robot->x, robot->y);

}

int deplacement1(struct position * robot, double * tableau){
  
  
  int i = robot->y*100 + robot->x;
  //printf("\n concentration : %f \n", tableau[i]);
  
    double randomDomaine = RAND_MAX + 1.0;
  int iy = (int) (rand() / randomDomaine * 3);      
// la bacterie tape un bord => elle rebondie
  if ((robot->x>99) || (robot->x<0)||(robot->y>99) || (robot->y<0)) {
    robot->dirx=-robot->dirx;
    robot->diry=-robot->diry;
  } 
  
 
  else {
    if (tableau[i]< robot->c){ 
      // on s'assure que la bacterie avance 
      int direction[]={-1,1,0};  
      int ix =(int) (rand() / randomDomaine * 3);
      //  printf("randommmmm %f", rand() / randomDomaine * 3);
      if (ix==2) {
        iy =(int) (rand() / randomDomaine * 2);}
      else {
        iy =(int) (rand() / randomDomaine * 3);}
      robot->dirx=direction[ix];
      robot->diry=direction[iy];
      // printf("dirx deplacentfgf %d\n\n", robot->dirx);
    }}
    
  // printf("dirx deplacentfgf %d\n\n", robot->dirx);
  robot->c=tableau[i];

  
  // on ne fait pas avancer les bacteries qui ont d??j?? avanc?? avec la fonction rencontre
  
   	if (robot->rencontre==1) {
		robot->rencontre=0;
		return 1;}

  robot->x+=robot->dirx;
  robot->y+=robot->diry;
  //printf("(x???deplacemnt=%d,y???deplacemnt=%d)\n", robot->x, robot->y);
  robot->vect[0]+=robot->dirx;
  robot->vect[1]+=robot->diry;
  //printf("(x???deplacemnt=%d,y???deplacemnt=%d)\n",   robot->vect[1], robot->vect[0]);
  // printf("(vectx=%d,vecty=%d)\n",   robot->vect[0], robot->vect[1]);
	return 1;
}

void deplacement2(struct position * robot, double * tableau) {
	

	double randomDomaine = RAND_MAX + 1.0;
	
	if ((robot->x>99) || (robot->x<0)||(robot->y>99) || (robot->y<0)) {
		robot->dirx=-robot->dirx;
		robot->diry=-robot->diry;
  }

  
    else {
		
		if (robot->add%10==0){

	int iy = (int) (rand() / randomDomaine * 3);
	
		
	  int direction[]={-1,1,0};  
      int ix =(int) (rand() / randomDomaine * 3);

      if (ix==2) {
        iy =(int) (rand() / randomDomaine * 2);}
      else {
        iy =(int) (rand() / randomDomaine * 3);}
      robot->dirx=direction[ix];
      robot->diry=direction[iy];
		
}}

  robot->x+=robot->dirx;
  robot->y+=robot->diry;
  robot->add+=1;



}

int rencontre( struct position * robot, int n, double * tableau, struct position solute ){
  
   for ( int i=0 ; i<n-1; i++){
   
    for ( int j=i+1 ; j<n; j++){
    
    

if ((robot[i].x==robot[j].x) && (robot[i].y==robot[j].y) && (robot[i].x<99) && (robot[i].x>0) && (robot[i].y<99) && (robot[i].y>0)){ 
  
  if (robot[i].couleur != robot[j].couleur){
    robot[i].couleur=1;
    robot[j].couleur=1;
    return 0;}
  
  else {
    if (robot[i].couleur==1) return 0;}
    
  
  
if ((robot[i].vect[0]!=0 || robot[i].vect[1] !=0) && (robot[j].vect[0]!=0 || robot[j].vect[1] !=0))  {
if (robot[i].rencontre==0 && robot[j].rencontre==0)  {    
        
        robot[i].rencontre=1;
        robot[j].rencontre=1;
        
        
        printf(" le robot %d avec le robot numero %d , x= %d" ,i,j,robot[i].x);
        
        printf(" y= %d\n\n" ,robot[i].y);
        
  //  printf(" vectx ini: %d, vecty ini= %d" ,robot[i].vect[0],robot[i].vect[1]);
    
    
    
        robot[i].vect[0]=arround(robot[i].vect[0]/(sqrt(robot[i].vect[0]*robot[i].vect[0]+robot[i].vect[1]*robot[i].vect[1])));
        robot[i].vect[1]=arround(robot[i].vect[1]/(sqrt(robot[i].vect[0]*robot[i].vect[0]+robot[i].vect[1]*robot[i].vect[1])));
  
        robot[j].vect[0]=arround(robot[j].vect[0]/(sqrt(robot[j].vect[0]*robot[j].vect[0]+robot[j].vect[1]*robot[j].vect[1])));
        robot[j].vect[1]=arround(robot[j].vect[1]/(sqrt(robot[j].vect[0]*robot[j].vect[0]+robot[j].vect[1]*robot[j].vect[1])));
             
        //on compare la position de certaines bact??ries/libellules(robots) 
        //elles se partagent les infos --> am??lioration de la tendance g??n??rale (direction g??n??rale)
        
        robot[i].vect[0]=robot[j].vect[0]+robot[i].vect[0];
        robot[i].vect[1]=robot[j].vect[1]+robot[i].vect[1];
        

        
        //on normalise la tendance g??n??rale pour faire avancer les robots(bact??ries-libbellules) d'un vecteur unitaire dans la direction id??ale 
        
  
  
        
        //printf(" x= %d" ,robot[i].vect[0]);
        //printf("y= %d\n" ,robot[i].vect[1]);
        
        //cas ou les vecteurs de tendance g??n??ral s'annulent:
      
        if (robot[i].vect[0]==0 && robot[i].vect[1]==0){
          
          robot[i].vect[0]=-robot[j].vect[1];
          robot[i].vect[1]=robot[j].vect[0];
          
     
          
        }
        robot[i].vect[0]=robot[i].vect[0]/sqrt(robot[i].vect[0]*robot[i].vect[0]+robot[i].vect[1]*robot[i].vect[1]);
        robot[i].vect[1]=robot[i].vect[1]/sqrt(robot[i].vect[0]*robot[i].vect[0]+robot[i].vect[1]*robot[i].vect[1]);
          
        robot[j].vect[0]=robot[i].vect[0];
        robot[j].vect[1]=robot[i].vect[1];
        // printf("i= %d,j= %d dirx= %d \n", i,j ,robot[i].dirx);
        
        robot[i].dirx=arround(robot[i].vect[0]);
        robot[i].diry=arround(robot[i].vect[1]);
        
        robot[j].dirx=robot[i].dirx;
        robot[j].diry=robot[i].diry;
        
       // printf("i= %d, dirx= %d, diry=%d, vect=(%d,%d) x= %d y =%d\n", i, robot[i].dirx, robot[i].diry, robot[i].vect[0], robot[i].vect[1],robot[i].x,robot[i].y);
        //printf("j= %d, dirx= %d, diry=%d, vect=(%d,%d) x= %d y =%d\n\n", j, robot[j].dirx, robot[j].diry, robot[j].vect[0], robot[j].vect[1],robot[j].x,robot[j].y);
       
        
        //on oublie pas d'update les concentrations !
        
        int position_c = robot[i].y*100+robot[i].x;
        robot[i].c=tableau[position_c];
        robot[j].c=tableau[position_c];

  
        robot[i].x+=robot[i].dirx;
        robot[i].y+=robot[i].diry;
        
        robot[j].x+=robot[j].dirx;
        robot[j].y+=robot[j].diry;
   
    int jr=robot[i].y*100+robot[i].x;
    int js=solute.y*100+solute.x;
        if (jr==js){
          printf("bravo ! ");
          return 1;}
      }}
    }}
  }
  return 0;
 }


int main(int argc, char * argv[]) {
  
  struct reponse a ;
  input("nombre de bacteries blanches souhai??es : ",&a);
    int n1 = strtol(a.phrase, NULL, 10);
  input("nombre de bacteries rouges souhai??es : ",&a);

  int n2 = strtol(a.phrase, NULL, 10);
  
  input("coordonn??e x du solute : x=",&a);
  int x0 = strtol(a.phrase, NULL, 10);
  
  input("coordonn??e y du solute : y=",&a);
  int y0 = strtol(a.phrase, NULL, 10);

	int n=n1+n2;
  
  
  
 if (x0>=100 || y0>=100 || x0<=0 || y0<=0 || n<=0 || n>=1000) { return printf( "les coordonn??es du solute doivent ??tre des entiers compris entre [0:100[ , le nb de bat??ries doit ??tre un entier compris entre [0;100] ") ;}
  
  FILE * trace1 = fopen("trace1.csv", "w");
  FILE * trace2 = fopen("trace2.csv", "w");


srand(time(NULL));
  
  double * terrain = malloc(100*100*sizeof(double));
  struct position solute1={100,x0,y0};
  struct position robot[10000];
  gradc(terrain, solute1);
  fprintf(trace1, "%d, \n ",n);
  
  for (int i=0; i<n; i++){
	  
	  for( int j=0; j<n1;j++){robot[j].couleur=0;}
	 
	  for( int b=n1; b<n2;b++){ robot[b].couleur=1;}
	   
    initial(&robot[i]); //on initialise tous nos robots (position de mani??re al??atoire, etc.)
  }

  //boucle pour faire avancer nos petites bact??ries t fois
  for (int t=0; t<60000; t++){
  //  printf("temps de rencontre %d \n", t);
  
    if (rencontre(robot,n, terrain,solute1)==1) {
    printf(" gfghset Au bout de %d",t);
          return 0;}
    //printf("\n\n");
    for (int i=0; i<n; i++){
    if (robot[i].couleur==1){
      deplacement2(&robot[i],terrain);
      fprintf(trace2, "  %d,  %d \n ",robot[i].x, robot[i].y);
      fprintf(trace1, "  %d,  %d \n ",0, 0);
      
      }
      
    else{
    deplacement1(&robot[i],terrain);
    
      fprintf(trace1, "  %d,  %d \n ",robot[i].x, robot[i].y);
      fprintf(trace2, "  %d,  %d \n ",0, 0);
      int jr=robot[i].y*100+robot[i].x;
      int js=solute1.y*100+solute1.x;
        if (jr==js){
          printf("bravo ! Au bout de %d",t);
          return 0;
        }}
    }    
  

      

 
 
}
 free(terrain);

  return 0;
}
=======

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reponse{
  
  char phrase[100];

};

void input( char * question, struct reponse * a ) {

   printf("%s",question);
   gets(a->phrase);

}


struct position {
 
  double c;
  int x;
  int y;
  int vect[2];
  int dirx;
  int diry;
  int rencontre;


};

int arround( double o) {

  return (int) floor(o+0.5);
 
}

double concentration(int i, int x0, int y0, double c0){
  
  int x = i % 100;
  int y = i / 100;
  double r = sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0));
  double c=(c0/r);
  return c;
}


void gradc(double * tableau, struct  position solute){
  
  
  FILE * gradient = fopen("gradientC.csv", "w");
  int i = solute.y*100 + solute.x;
  for (int j=0; j<100*100; j++){

    tableau[j]=concentration(j, solute.x, solute.y, solute.c);
  //printf("%0.2f ", tableau[j]);
  
    if (j==i) tableau[i]=solute.c;
    else tableau[j]=concentration(j, solute.x, solute.y, solute.c);
    
    if ((j%100==0) & (j!=0)) {
    //printf("\n");
    fprintf(gradient, "\n");}

  //printf("%0.2f ", tableau[j]);
    fprintf(gradient, "%0.2f ", tableau[j]);
  //fprintf(file, ",");

  }
}

void initial(struct position * robot ){


  double randomDomaine = RAND_MAX + 1.0;

  //int pos_alea_x = (int) (rand() / randomDomaine * 100);
  int pos_alea_y = (int) (rand() / randomDomaine * 100);
 
  robot->dirx=1;
  robot->c=0; 
  robot->diry=1;
  robot->x=0;
  robot->y=pos_alea_y;
  robot->vect[0]=1;
  robot->vect[1]=1;
  robot->rencontre=0;
  
  //printf("(%d, %d) \n", robot->x, robot->y);

}

int deplacement(struct position * robot, double * tableau){
  
  
  int i = robot->y*100 + robot->x;
  //printf("\n concentration : %f \n", tableau[i]);
  
    double randomDomaine = RAND_MAX + 1.0;
  int iy = (int) (rand() / randomDomaine * 3);      

  if ((robot->x>99) || (robot->x<0)||(robot->y>99) || (robot->y<0)) {
    robot->dirx=-robot->dirx;
    robot->diry=-robot->diry;
  } 
  
 
  else {
    if (tableau[i]< robot->c){ 
      
      int direction[]={-1,1,0};  
      int ix =(int) (rand() / randomDomaine * 3);
      //  printf("randommmmm %f", rand() / randomDomaine * 3);
      if (ix==2) {
        iy =(int) (rand() / randomDomaine * 2);}
      else {
        iy =(int) (rand() / randomDomaine * 3);}
      robot->dirx=direction[ix];
      robot->diry=direction[iy];
      // printf("dirx deplacentfgf %d\n\n", robot->dirx);
    }}
    
  // printf("dirx deplacentfgf %d\n\n", robot->dirx);
  robot->c=tableau[i];
  //affichercapteur(robot);
   	if (robot->rencontre==1) {
		robot->rencontre=0;
		return 1;}

  robot->x+=robot->dirx;
  robot->y+=robot->diry;
  //printf("(x???deplacemnt=%d,y???deplacemnt=%d)\n", robot->x, robot->y);
  robot->vect[0]+=robot->dirx;
  robot->vect[1]+=robot->diry;
  //printf("(x???deplacemnt=%d,y???deplacemnt=%d)\n",   robot->vect[1], robot->vect[0]);
  // printf("(vectx=%d,vecty=%d)\n",   robot->vect[0], robot->vect[1]);
	return 1;
}



int rencontre(struct position * robot, int n, double * tableau, struct position solute ) {
  
  
  
  for ( int i=0 ; i<n-1; i++){
   
    for ( int j=i+1 ; j<n; j++){
		
		

if (robot[i].x==robot[j].x && robot[i].y==robot[j].y && ((robot[i].x<99) && (robot[i].x>0) && (robot[i].y<99) && (robot[i].y>0)) && (robot[i].vect[0]!=0 || robot[i].vect[1] !=0) && (robot[j].vect[0]!=0 || robot[j].vect[1] !=0) ) {
if (robot[i].rencontre==0 && robot[j].rencontre==0)  {    
        
        robot[i].rencontre=1;
        robot[j].rencontre=1;
        
        
        printf(" le robot %d avec le robot numero %d , x= %d" ,i,j,robot[i].x);
        
        printf(" y= %d\n\n" ,robot[i].y);
        
	//	printf(" vectx ini: %d, vecty ini= %d" ,robot[i].vect[0],robot[i].vect[1]);
		
		
		
        robot[i].vect[0]=arround(robot[i].vect[0]/(sqrt(robot[i].vect[0]*robot[i].vect[0]+robot[i].vect[1]*robot[i].vect[1])));
        robot[i].vect[1]=arround(robot[i].vect[1]/(sqrt(robot[i].vect[0]*robot[i].vect[0]+robot[i].vect[1]*robot[i].vect[1])));
  
        robot[j].vect[0]=arround(robot[j].vect[0]/(sqrt(robot[j].vect[0]*robot[j].vect[0]+robot[j].vect[1]*robot[j].vect[1])));
        robot[j].vect[1]=arround(robot[j].vect[1]/(sqrt(robot[j].vect[0]*robot[j].vect[0]+robot[j].vect[1]*robot[j].vect[1])));
             
        //on compare la position de certaines bact??ries/libellules(robots) 
        //elles se partagent les infos --> am??lioration de la tendance g??n??rale (direction g??n??rale)
        
        robot[i].vect[0]=robot[j].vect[0]+robot[i].vect[0];
        robot[i].vect[1]=robot[j].vect[1]+robot[i].vect[1];
        

        
        //on normalise la tendance g??n??rale pour faire avancer les robots(bact??ries-libbellules) d'un vecteur unitaire dans la direction id??ale 
        
  
  
        
        //printf(" x= %d" ,robot[i].vect[0]);
        //printf("y= %d\n" ,robot[i].vect[1]);
        
        //cas ou les vecteurs de tendance g??n??ral s'annulent:
      
        if (robot[i].vect[0]==0 && robot[i].vect[1]==0){
          
          robot[i].vect[0]=-robot[j].vect[1];
          robot[i].vect[1]=robot[j].vect[0];
          
         /*
          //a partir de l?? je suis pas convaincue de l'utilit?? ...
          robot[i].dirx=arround(robot[i].vect[0]);
          robot[i].diry=arround(robot[i].vect[1]);
          
          int init = robot[i].y*100+robot[i].x;
          robot[i].x+=robot[i].dirx;
          robot[i].y+=robot[i].diry;
          int essai = robot[i].y*100+robot[i].x;
          
          if (tableau[essai]<tableau[init]){
            robot[i].vect[0]=-robot[i].vect[0];
            robot[i].vect[1]=-robot[i].vect[1];
          }*/
          
        }
        robot[i].vect[0]=robot[i].vect[0]/sqrt(robot[i].vect[0]*robot[i].vect[0]+robot[i].vect[1]*robot[i].vect[1]);
        robot[i].vect[1]=robot[i].vect[1]/sqrt(robot[i].vect[0]*robot[i].vect[0]+robot[i].vect[1]*robot[i].vect[1]);
          
        robot[j].vect[0]=robot[i].vect[0];
        robot[j].vect[1]=robot[i].vect[1];
        // printf("i= %d,j= %d dirx= %d \n", i,j ,robot[i].dirx);
        
        robot[i].dirx=arround(robot[i].vect[0]);
        robot[i].diry=arround(robot[i].vect[1]);
        
        robot[j].dirx=robot[i].dirx;
        robot[j].diry=robot[i].diry;
        
       // printf("i= %d, dirx= %d, diry=%d, vect=(%d,%d) x= %d y =%d\n", i, robot[i].dirx, robot[i].diry, robot[i].vect[0], robot[i].vect[1],robot[i].x,robot[i].y);
        //printf("j= %d, dirx= %d, diry=%d, vect=(%d,%d) x= %d y =%d\n\n", j, robot[j].dirx, robot[j].diry, robot[j].vect[0], robot[j].vect[1],robot[j].x,robot[j].y);
       
        
        //on oublie pas d'update les concentrations !
        
        int position_c = robot[i].y*100+robot[i].x;
        robot[i].c=tableau[position_c];
        robot[j].c=tableau[position_c];

  
        robot[i].x+=robot[i].dirx;
        robot[i].y+=robot[i].diry;
        
        robot[j].x+=robot[j].dirx;
        robot[j].y+=robot[j].diry;
   
		int jr=robot[i].y*100+robot[i].x;
		int js=solute.y*100+solute.x;
        if (jr==js){
          printf("bravo ! ");
          return 1;}
      }}
    }
  }
  return 0;
 }


int main(int argc, char * argv[]) {
  
  struct reponse a ;
  input("nombre de bacteries souhaite : ",&a);
  //printf(" il y aura %s bacteries\n", a.phrase );
  int n = strtol(a.phrase, NULL, 10);
  
  input("coordonn??e x du solute : x=",&a);
  int x0 = strtol(a.phrase, NULL, 10);
  
  input("coordonn??e y du solute : y=",&a);
  int y0 = strtol(a.phrase, NULL, 10);


  
  
  
 if (x0>=100 || y0>=100 || x0<=0 || y0<=0 || n<=0 || n>=1000) { return printf( "les coordonn??es du solute doivent ??tre des entiers compris entre [0:100[ , le nb de bat??ries doit ??tre un entier compris entre [0;100] ") ;}
  
  FILE * trace1 = fopen("trace1.csv", "w");
  FILE * trace2 = fopen("trace2.csv", "w");


srand(time(NULL));
  
  double * terrain = malloc(100*100*sizeof(double));
  struct position solute1={100,x0,y0};
  struct position robot[10000];
  gradc(terrain, solute1);
  fprintf(trace1, "%d, \n ",n);
  
  for (int i=0; i<n; i++){
    initial(&robot[i]); //on initialise tous nos robots (position de mani??re al??atoire, etc.)
  }

  //boucle pour faire avancer nos petites bact??ries 600 fois
  for (int t=0; t<6000; t++){
	  printf("temps de rencontre %d \n", t);
    if (rencontre(robot,n, terrain,solute1)==1) {
		printf(" gfghset Au bout de %d",t);
          return 0;}
    //printf("\n\n");
    for (int i=0; i<n; i++){
		if (robot[i].couleur==1){
			deplacement2(&robot[i],terrain)
			fprintf(trace2, "  %d,  %d \n ",robot[i].x, robot[i].y);
			fprintf(trace1, "  %d,  %d \n ",0, 0);
			
			}
			
		else{
		deplacement1(&robot[i],terrain);
	
       //printf("robot[%d] : (%d,%d)   ",i,robot[i].dirx, robot[i].diry);
      fprintf(trace1, "  %d,  %d \n ",robot[i].x, robot[i].y);
      fprintf(trace2, "  %d,  %d \n ",0, 0);
      int jr=robot[i].y*100+robot[i].x;
      int js=solute1.y*100+solute1.x;
        if (jr==js){
          printf("bravo ! Au bout de %d",t);
          return 0;
        }}
    }    
  

      

  free(terrain);

  return 0;
 
}
>>>>>>> 07a8ac262408f47f200a1beb32b8d4bafdb0df0e
