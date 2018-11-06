#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

int main (int argc, char ** argv) {
	int tempsEvolution = 1; // Début du jeu <=> temps 1
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;

	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g, &tempsEvolution);
	
	debut_jeu(&g, &gc, &tempsEvolution);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
