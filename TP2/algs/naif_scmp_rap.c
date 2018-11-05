#include "header.h"

decl_rech(naif_scmp_rap) {
    
    const size_t n = worlen - motlen + 1;

    unsigned int occ;
    int j; // j: wor

    char first;

    occ = 0;

    first = mot[0];
    j = 0;
    while (j < n) {
        while (j < n && wor[j] != first) {
            ++j;
        }

        if (strncmp(wor + j, mot, motlen) == 0) {
            occ++;
        }
        ++j;
    }

    return occ;

}
