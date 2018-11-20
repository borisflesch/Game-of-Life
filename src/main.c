#include <stdio.h>
#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

#define SIZEX 800
#define SIZEY 800


void paint(cairo_surface_t *surface)
{
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
	cairo_paint(cr);
	
	// line
	cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
	cairo_move_to (cr, 10.0, 50.0);
	cairo_line_to(cr, 100.0,50.0);
	cairo_set_line_width (cr, 1);
	cairo_stroke (cr);

	// filled rectangle
	cairo_rectangle(cr,30,30,50,50);
	cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
	cairo_fill(cr);	

	cairo_destroy(cr); // destroy cairo mask
}

int main (int argc, char ** argv) {
	int initialisationErreur = 0;
	int useCairo = 1;

	if (argc != 2 ) {
		printf("usage : main <numero de la grille>\n");
		return 1;
	}

	grille g, gc;

	char fichierGrille[100] = "grilles/grille";
	// strcat(fichierGrille, "grilles/grille");
	strcat(fichierGrille, argv[1]);
	strcat(fichierGrille, ".txt");
	initialisationErreur = init_grille_from_file(fichierGrille,&g);
	if (initialisationErreur) {
		printf("Erreur : Le fichier grille \"%s\" est introuvable\n", fichierGrille);
		return 1;
	}

	if (useCairo) {
		Display *dpy;
		Window rootwin;
		Window win;
		XEvent e;
		int scr;
		
		// init the display
		if(!(dpy=XOpenDisplay(NULL))) {
			fprintf(stderr, "ERROR: Could not open display\n");
			exit(1);
		}

		scr=DefaultScreen(dpy);
		rootwin=RootWindow(dpy, scr);

		win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
				BlackPixel(dpy, scr), BlackPixel(dpy, scr));

		XStoreName(dpy, win, "jeu de la vie");
		XSelectInput(dpy, win, ExposureMask|ButtonPressMask);
		XMapWindow(dpy, win);
		
		// create cairo surface
		cairo_surface_t *cs; 
		cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

		// run the event loop
		while(1) {
			XNextEvent(dpy, &e);
			if(e.type==Expose && e.xexpose.count<1) {
				paint(cs);
			} else if(e.type==ButtonPress) break;
		}

		cairo_surface_destroy(cs); // destroy cairo surface
		XCloseDisplay(dpy); // close the display

	} else {

		printf("Commandes du programme :\n");
		printf("- n : Charger une nouvelle grille\n");
		printf("- c : Passer en mode cyclique/non-cyclique\n");
		printf("- v : Activer/desactiver le vieillissement\n");
		printf("- q : Quitter le programme\n");

	}

	alloue_grille (g.nbl, g.nbc, &gc);

	// Par défaut : Temps initial => 1, Comptage cyclique => 1 (oui), Vieillissement => 0 (désactivé)
	affiche_grille(g, 1, 1, 0, useCairo);

	debut_jeu(&g, &gc, useCairo);

	libere_grille(&g);
	libere_grille(&gc);


	return 0;
}
