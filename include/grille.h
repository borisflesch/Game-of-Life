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
 * @brief Grille du jeu
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;

/**
 * Alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 * @param[in]  l Nombre de lignes de la grille à allouer
 * @param[in]  c Nombre de colonnes de la grille à allouer
 * @param[out] g Pointeur sur la grille à allouer
 */
void alloue_grille (int l, int c, grille* g);

/**
 * Libère une grille
 * @param[in] g Pointeur sur la grille à libérer
 */
void libere_grille (grille* g);

/**
 * Alloue et initalise la grille g à partir d'un fichier
 * @param[in]  filename Nom du fichier à partir du quel la grille doit être initialisée
 * @param[out] g        Grille à initialiser
 * @return              0 si aucune erreur lors de la lecture du fichier, 1 sinon
 */
int init_grille_from_file (char * filename, grille* g);

/**
 * Rend vivante la cellule (i,j) de la grille g
 * @param[in]  i Ligne de la cellule
 * @param[in]  j Colonne de la cellule
 * @param[out] g Grille
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 * Rend morte la cellule (i,j) de la grille g
 * @param[in]  i Ligne de la cellule
 * @param[in]  j Colonne de la cellule
 * @param[out] g Grille
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 * Rend non-viable la cellule (i,j) de la grille g
 * @param[in]  i Ligne de la cellule
 * @param[in]  j Colonne de la cellule
 * @param[out] g Grille
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

/**
 * Teste si la cellule (i,j) de la grille g est vivante
 * @param[in] i Abscisse de la cellule dans la grille
 * @param[in] j Ordonnée de la cellule dans la grille
 * @param[in] g Grille
 * @return      Booléen (0 ou 1) indiquant si la cellule est vivante ou non
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}

/**
 * Teste si la cellule (i,j) de la grille g est non-viable
 * @param[in] i Abscisse de la cellule dans la grille
 * @param[in] j Ordonnée de la cellule dans la grille
 * @param[in] g Grille
 * @return      Booléen (0 ou 1) indiquant si la cellule est non-viable ou non
 */
static inline int est_non_viable(int i, int j, grille g){return g.cellules[i][j] == -1;}

/**
 * Recopie gs dans gd (sans allocation)
 * @param[in]  gs Grille à copier
 * @param[out] gd Destination de la grille à copier
 */
void copie_grille (grille gs, grille gd);

#endif
