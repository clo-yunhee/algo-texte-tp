#ifndef RECH_HEADER_H
#define RECH_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define decl_rech(name) unsigned int rech_##name (const char *mot, const size_t motlen, const char *wor, const size_t worlen)

#define rech(name, mot, wor) rech_##name(mot, strlen(mot), wor, strlen(wor))

int min(int, int);
int max(int, int);

/*
 * Algorithme naif: fenetre glissante
 *  - boucle interne: sur le motif
 *  - boucle rapide: occurence première lettre
 *  - sentinelle: concat du mot à la fin
 *
 */

decl_rech(naif_bi);
decl_rech(naif_bi_rap);
decl_rech(naif_bi_rap_sen);

decl_rech(naif_scmp);
decl_rech(naif_scmp_rap);
decl_rech(naif_scmp_rap_sen);

decl_rech(morris_pratt);
decl_rech(knuth_morris_pratt);
decl_rech(boyer_moore);
//decl_rech(horspool);
//decl_rech(quick_search);

#endif // RECH_HEADER_H
