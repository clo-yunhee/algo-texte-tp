#!/bin/sh

ARK=ProjetAlgoTxt.tgz

tar cjvf $ARK --exclude-tag=.nodir \
    bin src inc Makefile .gitignore \
    generator/bin generator/src generator/inc generator/Makefile generator/.gitignore \
    mots.txt texte.txt script.sh package.sh toggle-test.sh
