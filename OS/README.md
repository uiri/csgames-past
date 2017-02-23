# Description

Les participants devront étudier la spécification d’un système de fichiers fictif afin d’implémenter un traducteur vers un format plus compréhensible par les machines de l’époque α.

Une spécification leur sera donnée ainsi qu’un blob de données formattées selon la spécification.

# Contexte et rôle-play

L’on raconte qu’un jour, des études du pré-cataclysme étaient courantes sous le dôme, et que des personnes étaient spécialisées dans ce genre d’études existaient.
L’on appelait ces personnes: des archéologues.

Un jour, une de ces équipes participa à une expédition hors du dôme, à leur retour, il ramenèrent une étrange relique, ainsi que des papiers, en grande majorité attaqués par le temps.

Après un long effort de traduction, la pile de papier s’est avérée être en majorité sans importance: des journaux relatant des faits connus des scientifiques du dôme, des publicités de l’époque pré-alpha, des illustrations obscènes que le gouvernement décide de garder dans un endroit à l’abri des yeux non-préparés...

Cependant, au milieu de ce tas d’informations sans importance, une reliure semblait avoir plus d’importance: elle décrit le fonctionnement d’une machine aujourd’hui disparue, le Disque Dur.

Après examen de la documentation, il s’avère que la relique ramenée par l’expédition était un de ces fameux disques-durs, depuis, des travaux afin d’en extraire les données ont commencé.

À l’heure d’aujourd’hui, les données ont été extraites sous forme d’un blob, et un document relatant l’organisation de ces données a été rédigé par des générations de travailleurs.

La seule étape restante est l’écriture d’un programme pour le déchiffrage des données...

# Règles

Chaque équipe possèdera un dump des données et une spécification du format des données qu’ils auront sous les yeux.

Leur travail sera d’implémenter un programme qui extraira les données du dump vers des fichiers dans le système hôte.

Seuls les langages C et C++ seront autorisés, pas de bibliothèque externe en dehors de la lib standard.

Les programmes devront être compilés avec GCC ou Clang, les participants auront accès à GDB (avec un frontend graphique style DDD ou Nemiver éventuellement) pour déboguer leur programme et au man des fonctions C (ou si quelqu’un a une idée d’outil de doc client-side pour C/C++ c’est bien aussi).
