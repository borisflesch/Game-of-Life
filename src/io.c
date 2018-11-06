#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g, int *tempsEvolution){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("Temps : %d\n\n", *tempsEvolution);
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n");
	return;
}

void efface_grille (grille g){
	// printf("\n\e[%dA",g.nbl*2 + 5); 
	printf("\n\e[%dA",g.nbl*2 + 7); 
}

void debut_jeu(grille *g, grille *gc, int *tempsEvolution){
	int comptageNonCyclique = 0;
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;

	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc,tempsEvolution,compte_voisins_vivants);
				efface_grille(*g);
				affiche_grille(*g, tempsEvolution);
				break;
			}
			case 'n' :
			{ // touche 'n' pour charger dynamiquement une nouvelle grille
				char nGrille[255];
				// efface_grille(*g);
				printf("Merci d'indiquer le chemin vers la nouvelle grille à charger : ");
				scanf("%s", nGrille);
				// efface_grille(*g);
				// printf("\n\n");

				(*tempsEvolution) = 0; // Réinitialisation du temps
				init_grille_from_file(nGrille, g);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g, tempsEvolution);
				printf("\n");
				
				debut_jeu(g, gc, tempsEvolution);
				break;
			}
			case 'c' :
			{
				// voisinnage cyclique / non-cyclique
				if (comptageNonCyclique == 1) { // On repasse à un comptage cyclique
					comptageNonCyclique = 0;
					compte_voisins_vivants = &(compte_voisins_vivants_cyclique);
					printf("> Comptage été passé en mode Cyclique\n");
				} else { // On repasse à un comptage non-cyclique
					comptageNonCyclique = 1;
					compte_voisins_vivants = &(compte_voisins_vivants_non_cyclique);
					printf("> Comptage passé en mode Non-cyclique\n");
				}
				// printf("\n\e[1A");
				printf("\n");

				affiche_grille(*g, tempsEvolution);
				printf("\n");
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
