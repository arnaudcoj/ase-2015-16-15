#!/bin/bash

export HW_CONFIG=hardware.ini
export CURRENT_VOLUME=0
make realclean >> /dev/null
make all >> /dev/null
echo créé un volume de taille 5 à l\'emplacement secteur 0 cylindre 0 avec ./mkvol -s 5 -fs 1 -fc 1
read
./mkvol -s 5 -fs 1 -fc 1
read
echo affiche les volume présent avec ./dvol
read
./dvol
read
echo créé systeme de fichier avec ./mknfs
read
./mknfs
read
echo affiche systeme de fichier avec ./dfs
read
./dfs
read
echo créé un fichier contenant \"toto\" fichier avec echo toto \| ./if_nfile
read
fileOne=$(echo toto | ./if_nfile) 
echo $fileOne
read
echo affiche le fichier créé avec ./if_pfile $fileOne
read
./if_pfile $fileOne
read
echo affiche systeme de fichier avec ./dfs
read
./dfs
read
echo copie le fichier créé avec ./if_cfile $fileOne
read
fileTwo=$(./if_cfile $fileOne)
echo $fileTwo
read
echo affiche la copie créé avec ./if_pfile $fileTwo
read
./if_pfile $fileTwo
read
echo affiche systeme de fichier avec ./dfs
read
./dfs
read
echo seconde copie avec ./if_cfile $fileOne
read
./if_cfile $fileOne
read
echo détruit la copie créé avec ./if_dfile $fileTwo
read
./if_dfile $fileTwo
read
echo affiche systeme de fichier avec ./dfs
read
./dfs
exit 0
