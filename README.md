Projet : Game of Life
=====================

Ce [dépôt](https://git.unistra.fr/bflesch/Projet-Game-of-Life) contient l'intégralité du projet du cours de Techniques de Développement intitulé « Game of Life ».

Structure des fichiers
----------------------

/ racine
-- src/ contient toutes les sources (*.c)
-- include/ contient toutes les en-têtes de fonctions et structures du programme (*.h)
-- grilles/ contient l'ensemble des grilles disponibles

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


Journal des versions
--------------------
v0.0.0 : Commit initial, fichiers de départs uniquement
v0.1 : Premier niveau terminé