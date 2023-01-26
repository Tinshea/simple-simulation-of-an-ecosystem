#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20
#define ENERGIE 100


/* on crée les listes pour les prédateurs et pour les proies*/
void creerleslistes(Animal **liste_animal , int nb_animaux){
    
  *liste_animal=creer_animal( 1+rand()%(SIZE_X-2) ,1+rand()%(SIZE_Y-2) ,ENERGIE);

          for(int i=1;i<nb_animaux;i++){
                *liste_animal=ajouter_en_tete_animal(*liste_animal,creer_animal( 1+rand()%(SIZE_X-2) ,1+rand()%(SIZE_Y-2) ,ENERGIE ));
            }
            
  }

int main() {

  /* Part 1, exercice 5, question 3 */

  
  /* on crée 2 liste un pour les prédateurs et une pour les proies*/
Animal *liste_proies;
Animal *liste_predateurs;

Animal **les_proies = &liste_proies;
Animal **les_predateurs = &liste_predateurs;

creerleslistes(les_proies, NB_PROIES);
creerleslistes(les_predateurs, NB_PREDATEURS);


//affichage de l'ecosystéme
printf("le nombre de proies est de %d \n",compte_animal_rec(liste_proies));
printf("le nombre de predateur est de %d \n \n",compte_animal_rec(liste_predateurs));
 
afficher_ecosys(liste_proies,liste_predateurs);

//libére la mémoire allouée pour les listes liste_proies et liste_predateurs.
free(liste_proies);
free(liste_predateurs);




  return 0;
}
