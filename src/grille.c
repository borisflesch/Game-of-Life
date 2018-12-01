#include "grille.h"
#include "jeu.h"

void alloue_grille (int l, int c, grille* g){
	int i, j;
	g->nbl = l;
	g->nbc = c;
	g->cellules = (int**) malloc(l * sizeof(int*));

	for (i = 0; i < l; i++) {
		g->cellules[i] = (int*) malloc(c * sizeof(int));
		for (j = 0; j < c; j++) {
			set_morte(i, j, *g);
		}
	}
}

void libere_grille (grille* g){
	int i;
	for (i = 0; i < g->nbl; i++) {
		free(g->cellules[i]);
	}
	free(g->cellules);
}

int init_grille_from_file (char * filename, grille* g){
	int res = 0;

	FILE * pfile = NULL;
	pfile = fopen(filename, "r");

	if (pfile != NULL) {
		int i,j,n,l,c,vivantes=0,nonViables=0;

		fscanf(pfile, "%d", & l);
		fscanf(pfile, "%d", & c);

		alloue_grille(l,c,g);

		fscanf(pfile, "%d", & vivantes);
		for (n=0; n < vivantes; ++n){
			fscanf(pfile, "%d", & i);
			fscanf(pfile, "%d", & j);
			set_vivante(i,j,*g);
		}

		fscanf(pfile, "%d", &nonViables);
		for (n=0; n < nonViables; ++n){
			fscanf(pfile, "%d", & i);
			fscanf(pfile, "%d", & j);
			set_non_viable(i,j,*g);
		}

		fclose (pfile);
	} else {
		res = 1; // Erreur
	}
	return res;
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;
}

int grillesEgales(grille *g1, grille *g2) {
	int i, j;
	for (i = 0; i < g1->nbl; i++) {
		for (j = 0; j < g1->nbc; j++) {
			if (g1->cellules[i][j] != g2->cellules[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

int grilleVide(grille *g) {
	int i, j;
	for (i = 0; i < g->nbl; i++) {
		for (j = 0; j < g->nbc; j++) {
			if (g->cellules[i][j] > 0) {
				return 0;
			}
		}
	}
	return 1;
}

int grilleOscillante(grille *g, int (*compte_voisins_vivants) (int, int, grille), int vieillissement) {
	int tempsEvolutionOscillation = 0;
	grille copieInitiale, copieIteree, tmp;
	alloue_grille (g->nbl, g->nbc, &copieInitiale);
	copie_grille(*g, copieInitiale);

	alloue_grille (g->nbl, g->nbc, &copieIteree);
	copie_grille(*g, copieIteree);

	alloue_grille (g->nbl, g->nbc, &tmp);
	copie_grille(*g, tmp);

	int maxInterval = 1000; // On suppose qu'au-delà de 1000 évolutions, une grille ne peut pas être oscillante

	int maxDelais = 100; // On suppose qu'au-delà de 100 évolutions, il ne peut plus y avoir de comportement oscillatoire
	int i = 0;
	 do {
		while (tempsEvolutionOscillation < maxInterval) {
			evolue(&copieIteree,&tmp,&tempsEvolutionOscillation,compte_voisins_vivants,vieillissement); // Met à jour tempsEvolutionOscillation
			if (grilleVide(&copieInitiale)) {
				return 0;
			}
			if (grillesEgales(&copieInitiale, &copieIteree)) {
				return tempsEvolutionOscillation;
			}
		}

		evolue(&copieInitiale,&tmp,&tempsEvolutionOscillation,compte_voisins_vivants,vieillissement);
		copie_grille(copieInitiale, copieIteree);
		tempsEvolutionOscillation = 0; // Réinitialisation du temps d'une oscillation
		i++;
	} while (i < maxDelais);


	

	return 0;
}