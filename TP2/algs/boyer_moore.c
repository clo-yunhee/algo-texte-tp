#include "header.h"

int *bm_calc_suff(const char *mot, size_t motlen);
int *bm_calc_bon_suff(const char *mot, size_t motlen);
int *bm_calc_dern_occ(const char *mot, size_t motlen);

decl_rech(boyer_moore) {
    
    int i, j;
    int *bon_suff, *dern_occ;

    unsigned int occ;

    occ = 0;
    
    bon_suff = bm_calc_bon_suff(mot, motlen);
    dern_occ = bm_calc_dern_occ(mot, motlen);

    j = motlen - 1;
    while (j < worlen) {
        i = motlen - 1;
        while (i >= 0 && mot[i] == wor[j - motlen + 1 + i]) {
            --i;
        }
        if (i < 0) {
            occ++;
            j += bon_suff[0]; // période
        } else {
            j += max(
                bon_suff[i],
                dern_occ[(int) wor[j - motlen + 1 + i]] - motlen + 1 + i
            );
        }
    }

    free(bon_suff);
    free(dern_occ);

    return occ;

}

int *bm_calc_suff(const char *mot, size_t motlen) {
    int i, f, g;
    int *suff;

    suff = malloc(sizeof(int) * motlen);

    f = motlen - 2;
    g = motlen - 1;
    suff[motlen - 1] = motlen;

    for (i = motlen - 2; i >= 0; --i) {
        if (i > g && suff[i + motlen - 1 - f] != i - g) {
            suff[i] = min(
                suff[i + motlen - 1 - f],
                i - g
            );
        } else {
            g = min(i, g);
            f = i;
            while (g >= 0 && mot[g] == mot[g + motlen + 1 - f]) {
                --g;
            }
            suff[i] = f - g;
        }
    }

    return suff;
}

int *bm_calc_bon_suff(const char *mot, size_t motlen) {
    int i, j;
    int *suff, *bon_suff;

    suff = bm_calc_suff(mot, motlen);
    
    bon_suff = malloc(sizeof(int) * motlen);

    i = 0;
    for (j = motlen - 2; j >= -1; --j) {
        if (j == -1 || suff[j] == j + 1) {
            while (i < motlen - 1 - j) {
                bon_suff[i] = motlen - 1 - j;
                ++i;
            }
        }
    }
    for (j = 0; j <= motlen - 2; ++j) {
        bon_suff[motlen - 1 - suff[j]] = motlen - 1 - j;
    }

    free(suff);

    return bon_suff;
}

int *bm_calc_dern_occ(const char *mot, size_t motlen) {
    int *dern_occ;

    dern_occ = malloc(sizeof(int) * (UCHAR_MAX + 1));

    for (int a = 0; a <= UCHAR_MAX; ++a) {
        dern_occ[a] = motlen;
    }
    for (int i = 0; i <= motlen - 2; ++i) {
        dern_occ[(int) mot[i]] = motlen - 1 - i;
    }

    return dern_occ;
}
