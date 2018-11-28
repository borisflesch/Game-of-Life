#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#include "io.h"

#define MARGE_GAUCHE_GRILLE 20
#define MARGE_HAUTE_GRILLE 60
#define LARGEUR_GRILLE 450
#define HAUTEUR_GRILLE 400
#define CAIRO_LINE_WIDTH 2

extern cairo_surface_t *sfc;
extern XEvent e;

void affiche_trait (int c) {
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_trait_cairo (int c, int hauteur){
	// float tailleLigneGrille = (float) HAUTEUR_GRILLE / (float) hauteur;
	float tailleLigneGrille = 30.;
	cairo_t *cr;
	cr = cairo_create(sfc);
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_set_line_width(cr, CAIRO_LINE_WIDTH);
	
	cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));

	int i;
	for (i = 0; i < c; ++i) {
		// cairo_line_to(cr, i * 30.0 + 100.0, 20.0 + (hauteur * 30));
		// cairo_move_to(cr, i * 30.0 + 100.0, 20.0 + (hauteur * 30));
		cairo_line_to(cr, MARGE_GAUCHE_GRILLE + LARGEUR_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
		cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
	}
	cairo_stroke(cr);
	cairo_destroy(cr);
}

void affiche_ligne (int c, int* ligne, int vieillissement) {
	int i;
	if (vieillissement) {
		for (i=0; i<c; ++i) {
			if (ligne[i] == 0 ) printf ("|   ");
			else if (ligne[i] == -1) printf("| X "); // Non-viable
			else printf ("| %d ", ligne[i]);
		}
	} else {
		for (i=0; i<c; ++i) {
			if (ligne[i] == 0 ) printf ("|   ");
			else if (ligne[i] == -1) printf("| X "); // Non-viable
			else printf ("| 0 ");
		}
	}
	printf("|\n");
	return;
}

void affiche_ligne_cairo (int c, int* ligne, int vieillissement, int hauteur){
	int i;
	float tailleColonneGrille = (float) LARGEUR_GRILLE / (float) c;
	// float tailleLigneGrille = (float) HAUTEUR_GRILLE / (float) hauteur;
	float tailleLigneGrille = 30.;
	// printf("%f\n\n", tailleColonneGrille);
	if (vieillissement) {
		for (i=0; i<c; ++i) {
			if (ligne[i] == 0 ) printf ("|   ");
			else if (ligne[i] == -1) printf("| X "); // Non-viable
			else printf ("| %d ", ligne[i]);
		}
	} else {

		cairo_t *cr, *crcells;
		cr = cairo_create(sfc);
		crcells = cairo_create(sfc);
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		cairo_set_source_rgb(crcells, 0.0, 0.0, 0.0);
		cairo_set_line_width(cr, CAIRO_LINE_WIDTH);
		
		cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
	

		for (i=0; i<c; ++i) {

				// cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
				// cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));

			if (ligne[i] == 0) {
				cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
				cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
				cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
			} else if (ligne[i] == -1) {
				cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
				cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
				cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
				cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
				cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
				cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
				cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
			} else {
				cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
				cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i-1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
				// cairo_set_line_width(cr, 2CAIRO_LINE_WIDTH);
				// cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);
				// cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
				// cairo_set_line_width(cr, CAIRO_LINE_WIDTH);
				// cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille) + tailleLigneGrille);

				// cairo_rectangle(cr, 20, 20, 120, 80);
				cairo_rectangle(crcells, MARGE_GAUCHE_GRILLE + i * tailleColonneGrille, MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille),
				tailleColonneGrille, tailleLigneGrille);
				cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * tailleColonneGrille), MARGE_HAUTE_GRILLE + (hauteur * tailleLigneGrille));
			}
		}

		cairo_fill(crcells);
		cairo_stroke(cr);
		cairo_destroy(cr);
	}
	return;
}

void affiche_grille (grille g, int tempsEvolution, int comptageCyclique, int vieillissement, int useCairo){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("\e[K");
	printf("Temps : %d | ", tempsEvolution);
	printf("Comptage : ");
	comptageCyclique ? printf("Cyclique") : printf("Non-cyclique");
	printf(" | ");
	printf("Vieillissement : ");
	vieillissement ? printf("Active") : printf("Desactive");

	printf("\n\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i], vieillissement);
		affiche_trait(c);
	}
	printf("\n");
	// return;

	// int i, l=g.nbl, c=g.nbc;
	char strTemps[50];
	sprintf(strTemps, "- Temps : %d", tempsEvolution);

	cairo_t *cr;
	cr = cairo_create(sfc);

	// cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	// cairo_set_line_width(cr, CAIRO_LINE_WIDTH);
	// cairo_move_to(cr, 20.0, 550.0);
	// cairo_line_to(cr, 20.0, 370.0);
	
	// cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 

	cairo_select_font_face(cr, "Arial",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_font_size(cr, 26);
	cairo_move_to(cr, 20, 40);
	cairo_show_text(cr, "Conway's Game of Life");

	cairo_set_font_size(cr, 22);
	cairo_move_to(cr, 500, 80);
	cairo_show_text(cr, "Informations :");

	cairo_set_font_size(cr, 18);
	cairo_move_to(cr, 500, 120);
	cairo_show_text(cr, strTemps);  

	// // cairo_move_to(cr, 20, 530);
	// // cairo_show_text(cr, "very very interesting. I guess.");
	cairo_destroy(cr);


	int hauteur = 0;
	affiche_trait_cairo(c, hauteur);
	for (i=0; i<l; ++i) {
		affiche_ligne_cairo(c, g.cellules[i], vieillissement, hauteur);
		affiche_trait_cairo(c, ++hauteur);
		//break;
	}
	return;
}

float testInc = 1.0;

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 7);

	// Clear surface
	cairo_t *cr;
	cr = cairo_create(sfc);
	cairo_set_source_rgb (cr, 255.0, 255.0, 255.0);
	cairo_paint(cr);
	cairo_destroy(cr);
	// cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.0);
	// cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
	// cairo_rectangle(cr, 0.0, 0.0, 800., 800.);
	// cairo_paint_with_alpha(cr, 1.0);
	// cairo_destroy(cr);
}

void debut_jeu(grille *g, grille *gc, int useCairo){
	int tempsEvolution = 1;

	int passerProchaineEvolution = 0;

	int vieillissement = 0;

	int comptageCyclique = 1;
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;

	if (useCairo) {
		while(1) {
			affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, useCairo);
			XNextEvent(cairo_xlib_surface_get_display(sfc), &e);
			// printf("ev %d\n", e.type);
			// if (e.type==Expose && e.xexpose.count<1) {
			if (e.type == KeyPress) { // Touche pressée
				// printf("keykey%d\n", e.xkey.keycode);
				// return;
				if (e.xkey.keycode == 36) { // Touche entrée
					if (passerProchaineEvolution) {
						passerProchaineEvolution = 0;
					} else {
						evolue(g,gc,&tempsEvolution,compte_voisins_vivants,vieillissement);
						efface_grille(*g);
						affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, useCairo);
					}
				} else if (e.xkey.keycode == 57) { // Touche n

					int erreurInitialisation = 0;

					libere_grille(g);
					libere_grille(gc);
					do {
						char numeroGrille[10];
						char fichierGrille[100] = "grilles/grille";
						printf("Numero de la nouvelle grille a charger : ");
						scanf("%s", numeroGrille);
						strcat(fichierGrille, numeroGrille);
						strcat(fichierGrille, ".txt");
						erreurInitialisation = init_grille_from_file(fichierGrille, g);
						if (erreurInitialisation) {
							printf("Erreur : Le fichier grille \"%s\" est introuvable\n", fichierGrille);
						}
					} while (erreurInitialisation);

					tempsEvolution = 1; // Réinitialisation du temps
					alloue_grille (g->nbl, g->nbc, gc);
					efface_grille(*g);
					affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, useCairo);

					printf("\n\e[2A");
					printf("\n");

					/* On empêche l'évolution au clic sur "Entrée"
					lors du chargement de la nouvelle grille */
					passerProchaineEvolution = 1;
				}
			}
		}
		return;
	}

	char c = getchar();
	// char c;
	// scanf("%c", &c);
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				if (passerProchaineEvolution) {
					passerProchaineEvolution = 0;
				} else {
					evolue(g,gc,&tempsEvolution,compte_voisins_vivants,vieillissement);
					efface_grille(*g);
					affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, useCairo);
				}
				break;
			}
			case 'n' :
			{ // touche 'n' pour charger dynamiquement une nouvelle grille
				int erreurInitialisation = 0;

				libere_grille(g);
				libere_grille(gc);
				do {
					char numeroGrille[10];
					char fichierGrille[100] = "grilles/grille";
					printf("Numero de la nouvelle grille a charger : ");
					scanf("%s", numeroGrille);
					strcat(fichierGrille, numeroGrille);
					strcat(fichierGrille, ".txt");
					erreurInitialisation = init_grille_from_file(fichierGrille, g);
					if (erreurInitialisation) {
						printf("Erreur : Le fichier grille \"%s\" est introuvable\n", fichierGrille);
					}
				} while (erreurInitialisation);

				tempsEvolution = 1; // Réinitialisation du temps
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, useCairo);

				printf("\n\e[2A");
				printf("\n");

				/* On empêche l'évolution au clic sur "Entrée"
				lors du chargement de la nouvelle grille */
				passerProchaineEvolution = 1;

				break;
			}
			case 'c' :
			{
				// voisinnage cyclique / non-cyclique
				if (comptageCyclique) { // On repasse à un comptage non-cyclique
					comptageCyclique = 0;
					compte_voisins_vivants = &(compte_voisins_vivants_non_cyclique);
				} else { // On repasse à un comptage cyclique
					comptageCyclique = 1;
					compte_voisins_vivants = &(compte_voisins_vivants_cyclique);
				}

				printf("\e[A");
				printf("\e[K");
				printf("\n");
				break;
			}
			case 'v' :
			{
				// activation / désactivation du vieillissement
				vieillissement = !vieillissement;

				printf("\e[A");
				printf("\e[K");
				printf("\n");
				break;
			}
			default :
			{ // touche non traitée
				printf("\e[A");
				printf("\e[K");
				printf("\n");
				break;
			}
		}
		// c = getchar();
		scanf("%c", &c);
	}
	printf("A bientot !\n");
	return;
}
