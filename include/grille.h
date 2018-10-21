/** @file
 *	@brief Fonctions liées aux grilles
 */
#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * @struct grille :
 * nbl : nombre de lignes
 * nbc : nombre de colonnes
 * cellules : tableau de tableau de cellules
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/**
 * Alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 * @param l Nombre de lignes de la grille à allouer
 * @param c Nombre de colonnes de la grille à allouer
 * @param g Pointeur sur la grille allouée
 */
void alloue_grille (int l, int c, grille* g);

/**
 * Libère une grille
 * @param g Pointeur sur la grille à libérer
 */
void libere_grille (grille* g);

/**
 * Alloue et initalise la grille g à partir d'un fichier
 * @param filename Nom du fichier à partir du quel la grille doit être initialisée
 * @param g Grille à initialiser
 */
void init_grille_from_file (char * filename, grille* g);

/**
 * Rend vivante la cellule (i,j) de la grille g
 * @param i Ligne de la cellule
 * @param j Colonne de la cellule
 * @param g Grille
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 * Rend morte la cellule (i,j) de la grille g
 * @param i Ligne de la cellule
 * @param j Colonne de la cellule
 * @param g Grille
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * Teste si la cellule (i,j) de la grille g est vivante
 * @param i Abscisse de la cellule dans la grille
 * @param j Ordonnée de la cellule dans la grille
 * @param g Grille
 * @return  Booléen (0 ou 1) indiquant si la cellule est vivante ou non
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] == 1;}

/**
 * Recopie gs dans gd (sans allocation)
 * @param gs Grille à copier
 * @param gd Destination de la grille à copier
 */
void copie_grille (grille gs, grille gd);

#endif
