# EcoSysteme 

Simulation simple d'un écosysteme, dont le but est de mieux maitriser le langage c et ses concepts. 

## Fonctionnement
Dans une matrice de taille `SIZE_X ` X `SIZE_Y ` définit dans ecosys.h nous faisons cohabité des `proies`, des `prédateurs` et `l'herbe`, à chaque `tick` un événement se produit les proies et les prédateurs bougent dans la matrice d'une case dans une `direction aléatoire`.
Si une `proie` est sur une case avec de l'herbe il le `consomme` et augmente sa barre de satiété. Si sa barre de `satiété` est pleine et qu'il croise une autre proie il se `reproduit`, si sa barre est vide il `meurt`.
Les `prédateurs` fonctionne de la même manière sauf qu'il `consomme les proies`.
Les` herbes` qui ont été consommé `se regénérent à un ticks aléatoire`.


## Evolution du nombre des proies et des prédateurs en fonction du temps  
![](/Data.png)
