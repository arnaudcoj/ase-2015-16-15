#!/bin/bash

make realclean >> /dev/null
make all >> /dev/null
echo "affiche secteur 0 cylindre 0 avec ./dmps 0 0 (Appuyez sur une touche)"
read
./dmps 0 0
echo "formate avec ./frmt (Appuyez sur une touche)"
read
./frmt
 echo "affiche secteur 0 cylindre 0 avec ./dmps 0 0 (Appuyez sur une 
touche)"
 read
./dmps 0 0
exit 0
