#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.7;
float p_reproduce_predateur=0.9;
int temps_repousse_herbe=-1;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}


/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {

  //création de l'animal avec ses coordonées et son energie
  Animal *Nouvelle_animal=creer_animal(x,y,energie); 

  //On met notre nouvelle aniamal au début de notre list_animal et 
	Nouvelle_animal->suivant=*liste_animal;
	*liste_animal=Nouvelle_animal;

  //on test si l'animal est bien dans l'ecosysteme 
  assert(x>0);
  assert(y>0);
  
	assert(x<SIZE_X-1);
	assert(y<SIZE_Y-1);
}

void enlever_animal(Animal **liste_animal, Animal *animal){

  Animal *reservoir=*liste_animal , *poubelle=NULL;

      	while(reservoir!=animal){ // On cherche l'animal est on supprime si on trouve l'element
		        poubelle=reservoir;
	          reservoir=reservoir->suivant;
        	}

	if(poubelle){ poubelle->suivant=reservoir->suivant;}

	else{*liste_animal=(reservoir->suivant);}

	free(animal);
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {

Animal *variable_temporaire;

/*on parcourir la liste puis on récupére l'adresse du maillon courant, on passe au
suivant et on désallouer l'adresse précédente récupérée. */

      while(liste){

        variable_temporaire=liste;
        liste=liste->suivant;
      
        free(variable_temporaire);
      }

 return NULL;

}


/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}

/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  char ecosys[SIZE_X][SIZE_Y];
 
  /* on initialise le tableau */
  
    for(int i=0;i<SIZE_X;i++){
			for(int j=0;j<SIZE_Y;j++){

			    if ((i==0 || (i==(SIZE_X-1))) & (j==0 || j==(SIZE_Y-1))){ecosys[i][j]='+';}

          else if((i==0 && j>=1) || (i==SIZE_X-1 && j>=1)){ecosys[i][j]='-';}

          else if((j==0 && i>=1) || (j==SIZE_Y-1 && i>=1)){ecosys[i][j]='|';}

           else {ecosys[i][j]=' ';
          } 
        }
      }

 

  /* on ajoute les proies */
    Animal *proies=liste_proie;
	while(proies){
    int x=proies->x;
    int y=proies->y;
     /*on met dans l'ecosysteme les proies*/
		ecosys[x][y]='*';
		proies=proies->suivant;
	}


  /* on ajoute les predateurs */
  Animal *predateurs=liste_predateur;
	while(predateurs){

      int x=predateurs->x;
      int y=predateurs->y;

    /* Si on rencontre dans le tableau une proie alors on met @*/
		if(ecosys[x][y]=='*'){
			ecosys[x][y]='@';
		}
    /* Sinon on est dans une case vide on met 0*/
		else{
			ecosys[x][y]='O';
		}
		predateurs=predateurs->suivant;
	}


  /* on affiche le tableau */
  for(int i=0;i<SIZE_X;i++){
			for(int j=0;j<SIZE_Y;j++){
        printf("%c",ecosys[i][j]);
      }
      printf("\n");
          }
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}


/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
   Animal *deplacement=la;
   while(deplacement){

    /*déplacement dans l'axe x*/
     deplacement->x=deplacement->x+deplacement->dir[0];
      if (deplacement->x==SIZE_X-1){deplacement->x=1;}
     else if (deplacement->x==0){deplacement->x=SIZE_X-2;} 

     /*déplacement dans l'axe y*/
     deplacement->y=deplacement->y+deplacement->dir[1];
      if (deplacement->y==SIZE_Y-1){deplacement->y=1;}
     else if (deplacement->y==0){deplacement->y=SIZE_Y-2;}

     deplacement=deplacement->suivant;
   }
}
/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   Animal *animal=*liste_animal;
	while(animal){
		  if( (rand()%101) < (p_reproduce*100)) {
        int x=animal->x;
        int y=animal->y;
        float energie=(float)(animal->energie/2);
      
        /*creation du petite animal*/
        animal->energie=energie;
			  ajouter_animal(x,y,energie,liste_animal);
			
		  }
		animal=animal->suivant;
	}
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(*liste_proie);
  Animal *animal=*liste_proie;

  while(animal){
   animal->energie-=1;
   //l'animal mange de l'herbe si il y'en a
   if (monde[animal->x][animal->y]>0){
     animal->energie+=monde[animal->x][animal->y];
     monde[animal->x][animal->y] =temps_repousse_herbe;
     }
   else if (animal->energie<0){ 
     Animal *liste_transition=animal;
    animal= animal->suivant;
      enlever_animal(liste_proie, liste_transition);
   }
    else animal=animal->suivant; 

	}
  	reproduce(liste_proie,p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
	Animal *xy = l;
	while (xy){
		if ((xy->x == x) && (xy->y == y)){return xy;}
		else{xy = xy->suivant;}
	}
  return NULL;
} 


/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur);
  Animal *predateur=*liste_predateur;
  
  while(predateur){
   predateur->energie-=1;
   Animal *proies=animal_en_XY(*liste_proie,predateur->x,predateur->y);
		  if (proies){
			  predateur->energie += proies->energie;
			  enlever_animal(liste_proie, proies);
	  	}
		  if (predateur->energie<0){
			Animal *liste_transition=predateur;
			predateur= predateur->suivant;
			enlever_animal(liste_predateur,liste_transition);
		  }
		else{
			predateur = predateur->suivant;
		  }
	}
  	reproduce(liste_predateur,p_reproduce_predateur);
}


/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
   for(int i=0;i<SIZE_X;i++){
		for(int j=0;j<SIZE_Y; j++){
			monde[i][j]+=1;
		}
	}
}




