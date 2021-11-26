
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
  //printf("(x–deplacemnt=%d,y–deplacemnt=%d)\n", robot->x, robot->y);
  robot->vect[0]+=robot->dirx;
  robot->vect[1]+=robot->diry;
  //printf("(x–deplacemnt=%d,y–deplacemnt=%d)\n",   robot->vect[1], robot->vect[0]);
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
             
        //on compare la position de certaines bactéries/libellules(robots) 
        //elles se partagent les infos --> amélioration de la tendance générale (direction générale)
        
        robot[i].vect[0]=robot[j].vect[0]+robot[i].vect[0];
        robot[i].vect[1]=robot[j].vect[1]+robot[i].vect[1];
        

        
        //on normalise la tendance générale pour faire avancer les robots(bactéries-libbellules) d'un vecteur unitaire dans la direction idéale 
        
  
  
        
        //printf(" x= %d" ,robot[i].vect[0]);
        //printf("y= %d\n" ,robot[i].vect[1]);
        
        //cas ou les vecteurs de tendance général s'annulent:
      
        if (robot[i].vect[0]==0 && robot[i].vect[1]==0){
          
          robot[i].vect[0]=-robot[j].vect[1];
          robot[i].vect[1]=robot[j].vect[0];
          
         /*
          //a partir de là je suis pas convaincue de l'utilité ...
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
  
  input("coordonnée x du solute : x=",&a);
  int x0 = strtol(a.phrase, NULL, 10);
  
  input("coordonnée y du solute : y=",&a);
  int y0 = strtol(a.phrase, NULL, 10);


  
  
  
 if (x0>=100 || y0>=100 || x0<=0 || y0<=0 || n<=0 || n>=1000) { return printf( "les coordonnées du solute doivent être des entiers compris entre [0:100[ , le nb de batéries doit être un entier compris entre [0;100] ") ;}
  
  FILE * trace1 = fopen("trace1.csv", "w");

srand(time(NULL));
  
  double * terrain = malloc(100*100*sizeof(double));
  struct position solute1={100,x0,y0};
  struct position robot[10000];
  gradc(terrain, solute1);
  fprintf(trace1, "%d, \n ",n);
  
  for (int i=0; i<n; i++){
    initial(&robot[i]); //on initialise tous nos robots (position de manière aléatoire, etc.)
  }

  //boucle pour faire avancer nos petites bactéries 600 fois
  for (int t=0; t<6000; t++){
	  printf("temps de rencontre %d \n", t);
    if (rencontre(robot,n, terrain,solute1)==1) {
		printf(" gfghset Au bout de %d",t);
          return 0;}
    //printf("\n\n");
    for (int i=0; i<n; i++){
	
		deplacement(&robot[i],terrain);
	
       //printf("robot[%d] : (%d,%d)   ",i,robot[i].dirx, robot[i].diry);
      fprintf(trace1, "  %d,  %d \n ",robot[i].x, robot[i].y);
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
