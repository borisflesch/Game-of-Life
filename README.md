# Projet : Game of Life

![Build Status](https://semaphoreapp.com/api/v1/projects/d4cca506-99be-44d2-b19e-176f36ec8cf1/128505/shields_badge.svg)
![GitHub version](https://d25lcipzij17d.cloudfront.net/badge.svg?id=gh&type=6&v=0.5&x2=0)

Ce [dépôt](https://git.unistra.fr/bflesch/Projet-Game-of-Life) contient l'intégralité du projet du cours de Techniques de Développement intitulé « Game of Life ».


![](https://fboris.com/documents/project-game-of-life-techdev/preview-gui.gif)


Structure des fichiers
----------------------

- / racine
	- src/ contient toutes les sources (*.c)
	- lib/ contient les librairies (*.a)
	- include/ contient toutes les en-têtes de fonctions et structures du programme (*.h)
	- grilles/ contient l'ensemble des grilles disponibles

Commandes importantes
---------------------

### Compiler le programme

~~~{.sh}
make
~~~
Le fichier exécutable se trouve au chemin suivant : /bin/main
Par défaut, le programme est compilé en mode graphique (Cairo et X requis).

Pour compiler en mode texte :
~~~{.sh}
make MODE=TEXT
~~~

**ATTENTION :** Il est impératif de nettoyer les artefacts de compilation en passant du mode textuel au mode graphique et vice versa.

### Exécuter le programme

~~~{.sh}
./bin/make <chemin vers une grille>
~~~

Exemple :
~~~{.sh}
./bin/make "grilles/grille3.txt"
~~~

### Générer la documentation (Doxygen)

~~~{.sh}
doxygen
~~~
Il suffit ensuite d'ouvrir le fichier /doc/html/index.html pour accéder à l'intégralité de la documentation

### Générer une archive du programme

~~~{.sh}
make dist
~~~
L'archive sera créée dans le répertoire /dist

### Nettoyer les artefacts de compilation

~~~{.sh}
make clean
~~~

Ajouter des grilles
---------------------------
Si vous souhaitez ajouter vos propres conditions initiales pour le jeu, vous pouvez ajouter des grilles dans le répertoire /grilles/. Le fichier devra être nommé sous la forme grille[numéro de grille].txt et contenir les informations suivantes, en respectant espaces et retours à la ligne, et où chaque paramètre est un nombre entier :
- NBL : Nombre de lignes de la grille
- NBC : Nombre de colonnes de la grille
- NBCELL : Nombre de cellules initiales dans la grille
- L_CELL_X : Ligne de la cellule X (entre 0 et NBL - 1)
- C_CELL_X : Colonne de la cellule X (entre 0 et NBC - 1)
- NBCELL_NON_VIABLES : Nombre de cellules non-viables dans la grille
- L_CELLNV_X : Ligne de la cellule non-viable X (entre 0 et NBL - 1)
- C_CELLNV_X : Colonne de la cellule non-viable X (entre 0 et NBC - 1)

*Toute la partie concernant les cellules non-viables est facultative lors de la création d'une nouvelle grille.*

Fichier grilleX.txt :
~~~{.txt}
NBL NBC

NBCELL
L_CELL_1 C_CELL_1
L_CELL_2 C_CELL_2
...
L_CELL_X C_CELL_X

NBCELL_NON_VIABLES
L_CELLNV_1 C_CELLNV_1
L_CELLNV_2 C_CELLNV_2
...
L_CELLNV_X C_CELLNV_X
~~~

### Exemple de fichier grille

Considérons le fichier grille1.txt suivant :
~~~{.txt}
4 6

3
1 2
1 3
1 4
~~~

Celui-ci produira la grille suivante une fois chargé :

![](https://fboris.com/documents/project-game-of-life-techdev/grid-example.png)


Versions
--------
### Organisation des versions du projet
Les versions **v0.x** sont des versions stables du projet dans lesquelles « x » représente le dernier niveau finalisé présent dans cette version (cf. sujets de TP).

Des versions **v0.x.y** peuvent exister entre les niveaux, auquel cas « x » représente toujours le dernier niveau finalisé et « y » représente la dernière question terminée dans le niveau suivant. Néamoins, ces versions sont susceptibles de contenir des bugs ou **anomalies**. Il est donc préférable de les manipuler avec **précaution** et de se référer aux **v0.x pour des versions stables**.

### Journal des versions
- v0.5 : Niveau 5
- v0.4 : Niveau 4 finalisé (GUI)
- v0.3 : Niveau 3 finalisé
- v0.2 : Niveau 2 finalisé
- v0.1.2 : Question 2 du niveau 2 terminée
- v0.1 : Niveau 1 finalisé
- v0 : Commit initial, fichiers de départs uniquement
