#!/bin/sh
make TRIE=hachage
make TRIE=matrice
make generator
bin/genere-texte 50000 3 > texte3.txt
bin/genere-mots 10 5 25 3 > mots3.txt
bin/ac-matrice mots3.txt texte3.txt > res-ac-matrice
bin/ac-hachage mots3.txt texte3.txt > res-ac-hachage
diff res-ac-matrice res-ac-hachage
