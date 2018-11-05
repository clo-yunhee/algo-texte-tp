#include "header.h"

int *mp_calc_bon_pref(const char *mot, const size_t motlen);

decl_rech(morris_pratt) {
    int i, j, *bon_pref;
    unsigned int occ;

    bon_pref = mp_calc_bon_pref(mot, motlen);

    occ = 0;

    i = 0;
    for (j = 0; j < worlen; ++j) {
        while (i >= 0 && mot[i] != wor[j]) {
            i = bon_pref[i];
        }
        ++i;
        
        if (i == motlen) {
            occ++;
            i = bon_pref[i];
        }
    }

    free(bon_pref);

    return occ;
}


int *mp_calc_bon_pref(const char *mot, const size_t motlen) {
    int i, j, *bon_pref;
    
    bon_pref = malloc((motlen + 1) * sizeof(int));
    bon_pref[0] = -1;

    i = 0;
    for (j = 1; j < motlen; ++j) {
        bon_pref[j] = i;
        while (i >= 0 && mot[i] != mot[j]) {
            i = bon_pref[i];
        }
        ++i;
    }
    bon_pref[motlen] = i;

    return bon_pref;
}

