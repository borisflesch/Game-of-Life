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
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ", ligne[i]);
		// if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g, int tempsEvolution, int comptageCyclique){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("\e[K");
	printf("Temps : %d | ", tempsEvolution);
	if (comptageCyclique) {
		printf("Comptage : Cyclique | ");
	} else {
		printf("Comptage : Non-cyclique | ");
	}
	printf("\n\n");
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

void debut_jeu(grille *g, grille *gc){
	int tempsEvolution = 1;

	int passerProchaineEvolution = 0;

	int vieillissement = 0;

	int comptageCyclique = 1;
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;

	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				if (passerProchaineEvolution) {
					passerProchaineEvolution = 0;
				} else {
					evolue(g,gc,&tempsEvolution,compte_voisins_vivants);
					efface_grille(*g);
					affiche_grille(*g, tempsEvolution, comptageCyclique);
				}
				break;
			}
			case 'n' :
			{ // touche 'n' pour charger dynamiquement une nouvelle grille
				char nGrille[255];
				// efface_grille(*g);
				printf("Merci d'indiquer le chemin vers la nouvelle grille à charger : ");
				scanf("%s", nGrille);

				tempsEvolution = 1; // Réinitialisation du temps
				init_grille_from_file(nGrille, g);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g, tempsEvolution, comptageCyclique);

				printf("\n\e[2A");
				printf("\n");

				// debut_jeu(g, gc, tempsEvolution);
				passerProchaineEvolution = 1;
				/* On empêche l'évolution au clic sur "Entrée"
				pour valider le nom de la nouvelle grille à charger */

				break;
			}
			case 'c' :
			{
				// voisinnage cyclique / non-cyclique
				if (comptageCyclique == 0) { // On repasse à un comptage cyclique
					comptageCyclique = 1;
					compte_voisins_vivants = &(compte_voisins_vivants_cyclique);
				} else { // On repasse à un comptage non-cyclique
					comptageCyclique = 0;
					compte_voisins_vivants = &(compte_voisins_vivants_non_cyclique);
				}

				efface_grille(*g);
				affiche_grille(*g, tempsEvolution, comptageCyclique);
				printf("\e[K");
				printf("\n");
				break;
			}
			case 'v' :
			{
				// activation / désactivation du vieillissement
				if (vieillissement == 1) {
					vieillissement = 0;
					printf("> Vieillissement désactivé\n");
				} else {
					vieillissement = 1;
					printf("> Vieillissement activé\n");
				}
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
