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
 * @param c              Nombre de cellules de la ligne
 * @param ligne          Tableau indiquant pour chaque cellule si elle est vivante ou morte
 * @param vieillissement Indique si le vieillissement est activé (1) ou désactivé (0)
 */
void affiche_ligne (int c, int* ligne, int vieillissement);

/**
 * Affichage d'une grille
 * @param g                Grille à afficher
 * @param tempsEvolution   Entier représentant le temps (pas) d'évolution de la grille en cours
 * @param comptageCyclique Indique si le comptage est en mode cyclique (1) ou non-cyclique (0)
 * @param vieillissement   Indique si le vieillissement est activé (1) ou désactivé (0)
 */
void affiche_grille (grille g, int tempsEvolution, int comptageCyclique, int vieillissement);

/**
 * Effacement d'une grille
 * @param g Grille à effacer
 */
void efface_grille (grille g);

/**
 * Débute le jeu
 * @param g  Pointeur sur la grille (principale)
 * @param gc Pointeur sur la seconde grille allouée aux mêmes nombres de lignes et colonnes que la première et qui permettra plus tard l'évolution de la grille de g vers gc
 */
void debut_jeu(grille *g, grille *gc);

#endif
