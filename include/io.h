/** @file
 *	@brief Fonctions d'input/output (entrées/sorties) du programme
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 * Affichage d'un trait horizontal
 * @param c Nombre de cellules du trait
 */
void affiche_trait (int c);

/**
 * Affichage d'une ligne de la grille
 * @param c     Nombre de cellules de la ligne
 * @param ligne Tableau indiquant pour chaque cellule si elle est vivante ou morte
 */
void affiche_ligne (int c, int* ligne);

/**
 * Affichage d'une grille
 * @param g Grille à afficher
 */
void affiche_grille (grille g);

/**
 * Effacement d'une grille
 * @param g Grille à effacer
 */
void efface_grille (grille g);

// debute le jeu
/**
 * Débute le jeu
 * @param g  Pointeur sur la grille (principale)
 * @param gc Pointeur sur la seconde grille allouée aux mêmes nombres de lignes et colonnes que la première et qui permettra plus tard l'évolution de la grille de g vers gc
 */
void debut_jeu(grille *g, grille *gc);

#endif
