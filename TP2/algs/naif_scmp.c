#include "header.h"

decl_rech(naif_scmp) {
   
    const size_t n = worlen - motlen + 1;

    unsigned int occ;
    int j; // j: wor

    occ = 0;

    j = 0;
    while (j < n) {
        if (strncmp(wor + j, mot, motlen) == 0) {
            occ++;
        }
        ++j;
    }

    return occ;

}
