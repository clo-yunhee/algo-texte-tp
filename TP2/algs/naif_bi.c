#include "header.h"

decl_rech(naif_bi) {

    const size_t n = worlen - motlen + 1;
    
    unsigned int occ;
    int i, j; // j: wor, i: mot

    occ = 0;

    j = 0;
    while (j < n) {
        i = 0;
        while (i < motlen && mot[i] == wor[i+j]) {
            ++i;
        }
        if (i == motlen) {
            occ++;
        }
        ++j;
    }

    return occ;

}

