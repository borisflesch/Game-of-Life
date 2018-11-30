#include <stdio.h>
#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

cairo_surface_t *sfc;


int main (int argc, char ** argv) {
	int initialisationErreur = 0;

	if (argc != 2 ) {
		printf("usage : main <numero de la grille>\n");
		return 1;
	}

	grille g, gc;

	char fichierGrille[100] = "grilles/grille";
	strcat(fichierGrille, argv[1]);
	strcat(fichierGrille, ".txt");
	initialisationErreur = init_grille_from_file(fichierGrille,&g);
	if (initialisationErreur) {
		printf("Erreur : Le fichier grille \"%s\" est introuvable\n", fichierGrille);
		return 1;
	}

	alloue_grille (g.nbl, g.nbc, &gc);

	#if MODECAIROGUI
		/*
		=====================
		=== CAIRO VERSION ===
		=====================
		*/

		printf("=== Programme en cours d'execution ===\n\n");
		sfc = cairo_create_x11_surface0(SIZEX, SIZEY);		
		debut_jeu(&g, &gc);
		cairo_close_x11_surface(sfc); // destroy cairo surface

	#else
		/*
		====================
		=== TEXT VERSION ===
		====================
		*/
		printf("Commandes du programme :\n");
		printf("- n : Charger une nouvelle grille\n");
		printf("- c : Passer en mode cyclique/non-cyclique\n");
		printf("- v : Activer/desactiver le vieillissement\n");
		printf("- q : Quitter le programme\n");

		// Par défaut : Temps initial => 1, Comptage cyclique => 1 (oui), Vieillissement => 0 (désactivé)
		affiche_grille(g, 1, 1, 0);

		debut_jeu(&g, &gc);

	#endif

	libere_grille(&g);
	libere_grille(&gc);


	return 0;
}
