CHARNEUX Dimitri
COJEZ Arnaud

TP6 ASE - GESTION DE VOLUMES

Usage :
      "$ make all" pour créer les executables
      "$ make clean" pour supprimer les objets et exécutables
      "$ make realclean" pour supprimer les éléments ci-dessus ainsi que les périphériques

      "$ ./test_script" pour lancer un script de test faisant la démonstration des programmes ci-dessous :

      ======

      Attention : Pour lancer les programmes suivants, la variable d'environnement HW_CONFIG doit être définie avec le nom du fichier de configuration utilisé par la bibliothèque hardware : (ici vous pouvez utiliser "hardware.ini")

      "./mkvol -fc <premier cylindre> -fs <premier secteur> -s <nb de secteurs> [-v (verbose)]" pour créer un volume
      "./dvol" pour afficher les volumes du périphérique

      Attention : Pour lancer les programmes suivants, la variable d'environnement CURRENT_VOLUME avec l'indice d'un volume déja créé (par exemple "0")

      "./mknfs" pour initialiser un volume
      "./dfs" pour afficher l'état d'un volume
      "./test_free_bloc" pour lancer le programme de test
