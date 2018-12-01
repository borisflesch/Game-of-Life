/** @file
 *	@brief Fonctions d'input/output (entrées/sorties) du programme
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#if MODECAIROGUI

    #define SIZEX 900
    #define SIZEY 500

    /** 
     * Création d'une surface Xlib Cairo
     * @param[in] x Largeur de la surface (en pixels)
     * @param[in] y Hauteur de la surface (en pixels)
     */
    cairo_surface_t *cairo_create_x11_surface0(int x, int y);

    /**
     * Destruction d'une surface Xlib Cairo et fermeture de la connexion à X
     */
    void cairo_close_x11_surface();

    /**
     * Affichage d'un trait horizontal (en mode GUI Cairo)
     * @param[in] c           Nombre de cellules du trait
     * @param[in] hauteur     Numéro de la hauteur du trait à tracer (en partant du haut de la grille)
     * @param[in] tailleLigne Hauteur de la ligne (en pixels)
     */
    void affiche_trait (int c, int hauteur, float tailleLigne);

    /**
     * Affichage d'une ligne de la grille (en mode GUI Cairo)
     * @param[in] c              Nombre de cellules de la ligne
     * @param[in] ligne          Tableau indiquant pour chaque cellule si elle est vivante ou morte
     * @param[in] vieillissement Indique si le vieillissement est activé (1) ou désactivé (0)
     * @param[in] hauteur        Numéro de la hauteur du trait à tracer (en partant du haut de la grille)
     * @param[in] tailleLigne    Hauteur de la ligne (en pixels)
     */
    void affiche_ligne (int c, int* ligne, int vieillissement, int hauteur, float tailleLigne);

    /**
     * Effacement de la grille sur l'interface graphique (en mode GUI Cairo)
     */
    void efface_grille ();

    /**
     * Affiche une entrée de texte au bas de l'écran
     * @param[in] input  Entrée à afficher (saisie au clavier)
     * @param[in] erreur Erreur à afficher entre parenthèses si nécessaire
     */
    void drawTextInput(char *input, char *erreur);

#else

    /**
     * Affichage d'un trait horizontal (en mode Texte)
     * @param[in] c Nombre de cellules du trait
     */
    void affiche_trait (int c);

    /**
     * Affichage d'une ligne de la grille (en mode Texte)
     * @param[in] c              Nombre de cellules de la ligne
     * @param[in] ligne          Tableau indiquant pour chaque cellule si elle est vivante ou morte
     * @param[in] vieillissement Indique si le vieillissement est activé (1) ou désactivé (0)
     */
    void affiche_ligne (int c, int* ligne, int vieillissement);

    /**
     * Effacement d'une grille (en mode Texte)
     * @param[in] g Grille à effacer
     */
    void efface_grille (grille g);

#endif

/**
 * Débute le jeu
 * @param[in,out] g  Pointeur sur la grille (principale)
 * @param[in,out] gc Pointeur sur la seconde grille allouée aux mêmes nombres de lignes et colonnes que la première et qui permettra plus tard l'évolution de la grille de g vers gc
 */
void debut_jeu(grille *g, grille *gc);


/**
 * Affichage d'une grille
 * @param[in] g                  Grille à afficher
 * @param[in] tempsEvolution     Entier représentant le temps (pas) d'évolution de la grille en cours
 * @param[in] comptageCyclique   Indique si le comptage est en mode cyclique (1) ou non-cyclique (0)
 * @param[in] vieillissement     Indique si le vieillissement est activé (1) ou désactivé (0)
 * @param[in] tempsOscillation   Indique le temps d'oscillation d'une grille (ou -1 si non testé ou 0 si non oscillante)
 */
void affiche_grille (grille g, int tempsEvolution, int comptageCyclique, int vieillissement, int tempsOscillation);

#endif