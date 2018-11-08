Projet : Game of Life
=====================

Ce [dépôt](https://git.unistra.fr/bflesch/Projet-Game-of-Life) contient l'intégralité du projet du cours de Techniques de Développement intitulé « Game of Life ».


![](https://fboris.com/documents/project-game-of-life-techdev/preview.gif)


Structure des fichiers
----------------------

- / racine
	- src/ contient toutes les sources (*.c)
	- include/ contient toutes les en-têtes de fonctions et structures du programme (*.h)
	- grilles/ contient l'ensemble des grilles disponibles

Commandes importantes
---------------------

### Pour compiler le programme

~~~{.sh}
make
~~~
Le fichier exécutable se trouve au chemin suivant : /bin/main

### Pour exécuter le programme

~~~{.sh}
./bin/make <chemin vers une grille>
~~~

Exemple :
~~~{.sh}
./bin/make "grilles/grille3.txt"
~~~

### Pour générer la documentation (Doxygen)

~~~{.sh}
doxygen
~~~
Il suffit ensuite d'ouvrir le fichier /doc/html/index.html pour accéder à l'intégralité de la documentation

### Pour nettoyer les artefacts de compilation

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

Fichier grilleX.txt :
~~~{.txt}
NBL NBC

NBCELL
L_CELL_1 C_CELL_2
L_CELL_2 C_CELL_2
...
L_CELL_X C_CELL_X
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


Journal des versions
--------------------
**Organisation des versions du projet :** pour chaque version de la forme v0.x, « x » représente le niveau finalisé dans cette version (cf. sujets de TP). Des versions v0.x.y peuvent exister, auquel cas « x » représente toujours le dernier niveau finalisé et « y » représente la dernière question terminée dans le niveau suivant.
- v0.2 : Niveau 2 finalisé
- v0.1.2 : Question 2 du niveau 2 terminée
- v0.1 : Niveau 1 finalisé
- v0 : Commit initial, fichiers de départs uniquement
