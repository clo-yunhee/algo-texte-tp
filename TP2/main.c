#include "header.h"

#ifndef RALG
# define RALG naif_bi
#endif // RALG

#define test(name) rech(name, mot, wor)

int main(int argc, char *argv[]) {

    const char *mot, *wor;
    unsigned int occ; 

    mot = "abc";
    wor = "abcaacbbaaabcbbcabcbaaabcabc";
    occ = test(RALG);

    printf("Motif: \"%s\"\n", mot);
    printf("Texte: \"%s\"\n", wor);

    printf("Occurences: %d\n", occ);

    return EXIT_SUCCESS;
}
