#!/bin/bash

make realclean >> /dev/null
make all >> /dev/null
echo affiche secteur 0 cylindre 0 avec ./dmps 0 0
read
./dmps 0 0
read
echo formate avec ./frmt
./frmt
 echo affiche secteur 0 cylindre 0 avec ./dmps 0 0
 read
./dmps 0 0
exit 0
