#include "header.h"

decl_rech(naif_bi_rap) {
   
    const size_t n = worlen - motlen + 1;

    unsigned int occ;
    unsigned int i, j; // j: wor, i: mot

    char first;
    
    occ = 0;

    first = mot[0];
    j = 0;
    while (j < n) {
        // search first letter
        while (j < n && wor[j] != first) {
            ++j;
        }

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

