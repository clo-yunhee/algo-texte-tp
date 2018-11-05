#include "header.h"

int *kmp_calc_meil_pref(const char *mot, const size_t motlen);

decl_rech(knuth_morris_pratt) {
    int i, j, *meil_pref;
    unsigned int occ;

    meil_pref = kmp_calc_meil_pref(mot, motlen);

    occ = 0;

    i = 0;
    for (j = 0; j < worlen; ++j) {
        while (i >= 0 && mot[i] != wor[j]) {
            i = meil_pref[i];
        }
        ++i;
        
        if (i == motlen) {
            occ++;
            i = meil_pref[i];
        }
    }

    free(meil_pref);

    return occ;
}


int *kmp_calc_meil_pref(const char *mot, const size_t motlen) {
    int i, j, *meil_pref;
    
    meil_pref = malloc((motlen + 1) * sizeof(int));
    meil_pref[0] = -1;

    i = 0;
    for (j = 1; j < motlen; ++j) {
        if (mot[i] == mot[j]) {
            meil_pref[j] = meil_pref[i];
        } else {
            meil_pref[j] = i;
            do {
                i = meil_pref[i];
            } while (i >= 0 && mot[i] != mot[j]);
        }
        ++i;
    }

    meil_pref[motlen] = i;
    
    return meil_pref;
}

