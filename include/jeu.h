/** @file
 *	@brief Fonctions propres au jeu
 */
#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * Modulo modifié pour traiter correctement le calcul des voisins avec bords cycliques
 * @param[in]  i Première opérande
 * @param[in]  m Seconde opérande
 * @return       Valeur du modulo modifié
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * Compte le nombre de voisins vivants de la cellule (i,j). Les bords sont cycliques.
 * @param[in]  i Ligne de la cellule
 * @param[in]  j Colonne de la cellule
 * @param[in]  g Grille dans laquelle se trouve cette cellule et ses voisins à compter
 * @return       Nombre de voisins vivants
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);

/**
 * Compte le nombre de voisins vivants de la cellule (i,j). Les bords sont non cycliques.
 * @param[in]  i Ligne de la cellule
 * @param[in]  j Colonne de la cellule
 * @param[in]  g Grille dans laquelle se trouve cette cellule et ses voisins à compter
 * @return       Nombre de voisins vivants
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

/**
 * Fait évoluer la grille g d'un pas de temps
 * @param[in]  g                      Pointeur sur la grille à faire évoluer
 * @param[out] gc                     Pointeur sur la grille évoluée
 * @param[in]  tempsEvolution         Entier représentant le temps (pas) d'évolution de la grille en cours
 * @param[in]  compte_voisins_vivants Pointeur sur une fonction de comptage des voisins vivants d'une cellule
 * @param[in]  vieillissement         Indique si le vieillissement est activé (1) ou non (0)
 */
void evolue (grille *g, grille *gc, int *tempsEvolution, int (*compte_voisins_vivants) (int, int, grille), int vieillissement);

#endif
