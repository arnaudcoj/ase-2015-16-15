CHARNEUX Dimitri
COJEZ Arnaud

TP1 ASE - Implantation d’une bibliothèque de retour dans la pile d’exécution


Usage :
      "$ make all" pour créer les executables
      "$ ./display_stack" pour afficher les valeurs et adresses des registres ebp et esp
      "$ ./try_mul" pour lancer la multiplication avec try (ctrl-d pour valider la saisie des entiers demandés)


Explications registres ebp et esp :
      L'adresse d'esp est la plus petite que l'on voit. Les variables locales se trouvent entre esp et ebp. Les paramètres se trouvent à des adresses plus hautes que esp, ebp et les variables locales.
      Au fil des appels de fonctions, les adresses sont de plus en plus petites (monte dans la pile), et gardent la même structure que ci-dessus.




Problèmes rencontrés :
      Nous avions une erreur de segmentation (GLOBAL_OFFSET_TABLE) que nous avons contourné en appelant la fonction wait (réinitialise la pile ?)

