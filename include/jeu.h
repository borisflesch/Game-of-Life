/** @file
 *	@brief Fonctions propres au jeu
 */
#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * Modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * @param  i Première opérande
 * @param  m Seconde opérande
 * @return   Valeur du modulo modifié
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * Compte le nombre de voisins vivants de la cellule (i,j). Les bords sont cycliques.
 * @param  i Ligne de la cellule
 * @param  j Colonne de la cellule
 * @param  g Grille dans laquelle se trouve cette cellule et ses voisins à compter
 * @return   Nombre de voisins vivants
 */
int compte_voisins_vivants (int i, int j, grille g);

/**
 * Fait évoluer la grille g d'un pas de temps
 * @param g  Pointeur sur la grille à faire évoluer
 * @param gc Pointeur sur la grille évoluée
 * @param tempsEvolution Entier représentant le temps (pas) d'évolution de la grille en cours
 */
void evolue (grille *g, grille *gc, int *tempsEvolution);

#endif
