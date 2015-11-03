CHARNEUX Dimitri
COJEZ Arnaud

TP5 ASE - SYSTÈME DE FICHIERS À LA UNIX


Usage :
      "$ make all" pour créer les executables
      "$ ./dmps [c s]" pour afficher le secteur c s (si aucun paramètre c et s = 0)
      "$ ./frmt" pour formater l'ensemble du disque vdiskA.bin

Problèmes rencontrés :
      La commande CMD_FRMT ne formate qu'un secteur à la fois même si le paramètre nsector est > 1.
      Par conséquent, nous avons fait une boucle de 0 à nsector qui formate un secteur à la fois.
