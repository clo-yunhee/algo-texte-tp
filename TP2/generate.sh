#!/bin/bash

mkdir -p data

for card in 2 4 20 70; do
    ftxt="data/texte_${card}";
    rm -f $ftxt;
    ./genset $card 500000 $ftxt;

    for lg in 4 5 6 7 8 9 10 15 20 30 40 50; do
        fmot="data/mots_${card}_lg${lg}";
        rm -f $fmot;
        ./genset $card $lg $fmot 100;
    done;
done;
