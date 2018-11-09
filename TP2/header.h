#ifndef RECH_HEADER_H
#define RECH_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>

#define decl_rech(name) unsigned int rech_##name (const char *mot, const size_t motlen, const char *wor, const size_t worlen)

#define rech2(name, mot, motlen, wor, worlen) rech_##name(mot, motlen, wor, worlen)

#define rech(name, mot, wor)                  rech2(name, mot, strlen(mot), wor, strlen(wor))
#define rechn(name, mot, motlen, wor, worlen) rech2(name, mot, motlen, wor, worlen)

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
