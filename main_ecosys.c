#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include <unistd.h>
#include "ecosys.h"




#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000




int main(void) {
 srand(time(NULL));
  /* A completer. Part 2:*/
  //exercice 4, questions 2 
  Animal *Lion = creer_animal(1,1,100),*Mouton = creer_animal(8,9,100);
  afficher_ecosys(Mouton, Lion);
  Mouton->dir[0]=1;
  Mouton->dir[1]=1;
  Lion->dir[0]=0;
  Lion->dir[1]=-1;
  printf("\n");
  bouger_animaux(Lion);bouger_animaux(Mouton);
  afficher_ecosys(Mouton, Lion);
  free(Lion);
  free(Mouton);
//exercice 4, questions 4 
Animal* Test = creer_animal(6,5, 50);


reproduce(&Test,1);
printf("TEST: %d\n", compte_animal_rec(Test));
liberer_liste_animaux(Test);



//Exercice 5 question 1
int monde[SIZE_X][SIZE_Y];
   for(int i=0;i<SIZE_X;i++){
		for(int j = 0; j < SIZE_Y; j++){
			monde[i][j]=0;
		}
	}



   /* exercice 6, question 2 et exercice 7, question 3* exercice 8, question 1*/

   //on cree une liste de proies
   Animal *proies=creer_animal(8,5,50);
	    for (int i = 1; i < 20; i++){
			ajouter_animal(rand() % (SIZE_X-2) + 1, rand() % (SIZE_Y-2) + 1, 50, &proies);
		}

  Animal *predateurs=creer_animal(8,4,100);
	    for (int i = 1; i <50; i++){
			ajouter_animal(rand() % (SIZE_X-2) + 1, rand() % (SIZE_Y-2) + 1, 100, &predateurs);
			}
	
	int nb_bouble;
	printf("Veuillez rentrer un nombre maximal d'iteration ?\n");
	scanf("%d",&nb_bouble);
	
	printf("Nombre de proies au depart (*): %d\n", compte_animal_rec(proies));
	printf("Nombre de predateurs au depart (O): %d\n\n", compte_animal_it(predateurs));
	
	FILE *fichier = fopen("Evol_Pop.txt","w");
	fclose(fichier);

int generation=0;
  for(int i=0;((proies && predateurs) && (i < nb_bouble));i++){
	
	  	rafraichir_proies(&proies, monde);
		rafraichir_predateurs(&predateurs, &proies);
		rafraichir_monde(monde);
		afficher_ecosys(proies,predateurs);
		printf("Nombre de proies a l arriver (*): %d\n", compte_animal_rec(proies));
		printf("Nombre de predateurs a l arriver (O): %d\n", compte_animal_rec(predateurs));
		usleep(300000);
		//On enregistre le nombre de proies et de predateurs
		FILE *fichier=fopen("Evol_Pop.txt","a");
		fprintf(fichier,"%d %d %d\n",generation++,compte_animal_rec(proies),compte_animal_rec(predateurs));
		fclose(fichier);
		//Fin de l'enregistrement
	}
  

  
	liberer_liste_animaux(proies);
	liberer_liste_animaux(predateurs);
   
   
  return 0;
}

