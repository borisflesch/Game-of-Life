#include <stdio.h>
#include <string.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

int main (int argc, char ** argv) {
	int initialisationErreur = 0;

	if (argc != 2 ) {
		printf("usage : main <numero de la grille>");
		return 1;
	}

	grille g, gc;

	char fichierGrille[100];
	strcat(fichierGrille, "grilles/grille");
	strcat(fichierGrille, argv[1]);
	strcat(fichierGrille, ".txt");
	initialisationErreur = init_grille_from_file(fichierGrille,&g);
	if (initialisationErreur) {
		printf("Erreur : Le fichier grille \"%s\" est introuvable\n", fichierGrille);
		return 1;
	}

	alloue_grille (g.nbl, g.nbc, &gc);

	// Par défaut : Temps initial => 1, Comptage cyclique => 1 (oui), Vieillissement => 0 (désactivé)
	affiche_grille(g, 1, 1, 0);

	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
