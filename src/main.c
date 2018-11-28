#include <stdio.h>
#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"


Display *dpy;
Window rootwin;
Window win;
XEvent e;
int scr;
cairo_surface_t *sfc;


cairo_surface_t *cairo_create_x11_surface0(int x, int y)
{
    Display *dsp;
    Drawable da;
    int screen;
    cairo_surface_t *sfc;

    if ((dsp = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr, "ERROR: Could not open display\n");
        exit(1);
	}
    screen = DefaultScreen(dsp);
	rootwin = RootWindow(dsp, screen);
    /*da = XCreateSimpleWindow(dsp, DefaultRootWindow(dsp),
        0, 0, x, y, 0, 0, 0);*/

	unsigned long background = 0x0031343f;
	// da=XCreateSimpleWindow(dsp, rootwin, 1, 1, x, y, 0, 
	// 		WhitePixel(dsp, screen), WhitePixel(dsp, screen));
	da=XCreateSimpleWindow(dsp, rootwin, 1, 1, x, y, 0, 
			background, background);
    // XSelectInput(dsp, da, ButtonPressMask | KeyPressMask);
	// XSelectInput(dsp, da, ExposureMask|ButtonPressMask);
	XSelectInput(dsp, da, ExposureMask|ButtonPressMask|KeyPressMask);
    XMapWindow(dsp, da);


	// void XSetWMName(display, w, text_prop)
    //   Display *display;
    //   Window w;
    //   XTextProperty *text_prop;

	// typedef struct {
	// 	unsigned char *value;	/* property data */
	// 	Atom encoding;		/* type of property */
	// 	int format;		/* 8, 16, or 32 */
	// 	unsigned long nitems;	/* number of items in value */
	// } XTextProperty;

	// XTextProperty textProp;
	// textProp.value = "Name";
	// XSetWMName(dsp, da, textProp);

		//win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
				//BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dsp, da, "Jeu de la vie");

    sfc = cairo_xlib_surface_create(dsp, da,
        DefaultVisual(dsp, screen), x, y);
    cairo_xlib_surface_set_size(sfc, x, y);

    return sfc;
}

/*! Destroy cairo Xlib surface and close X connection.
 */
void cairo_close_x11_surface(cairo_surface_t *sfc)
{
   Display *dsp = cairo_xlib_surface_get_display(sfc);

   cairo_surface_destroy(sfc);
   XCloseDisplay(dsp);
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

	alloue_grille (g.nbl, g.nbc, &gc);

	if (useCairo) {


		printf("=== Programme en cours d'execution ===\n\n");

		sfc = cairo_create_x11_surface0(SIZEX, SIZEY);

		// run the event loop
		// while(1) {
			// XNextEvent(cairo_xlib_surface_get_display(sfc), &e);
			// if (e.type==Expose && e.xexpose.count<1) {
				// paint();
				// affiche_grille(g, 1, 1, 0, useCairo);
				
				debut_jeu(&g, &gc, useCairo);
			// } /* else if(e.type==ButtonPress) break; */

			// printf("Expose is %d\n", Expose);
			// printf("Got event: %d\n", e.type);

			// Par défaut : Temps initial => 1, Comptage cyclique => 1 (oui), Vieillissement => 0 (désactivé)
			// affiche_grille(g, 1, 1, 0, useCairo);

			// debut_jeu(&g, &gc, useCairo);
		// }

		cairo_close_x11_surface(sfc); // destroy cairo surface

	} else {

		printf("Commandes du programme :\n");
		printf("- n : Charger une nouvelle grille\n");
		printf("- c : Passer en mode cyclique/non-cyclique\n");
		printf("- v : Activer/desactiver le vieillissement\n");
		printf("- q : Quitter le programme\n");

		// Par défaut : Temps initial => 1, Comptage cyclique => 1 (oui), Vieillissement => 0 (désactivé)
		affiche_grille(g, 1, 1, 0, useCairo);

		debut_jeu(&g, &gc, useCairo);

	}

	libere_grille(&g);
	libere_grille(&gc);


	return 0;
}
