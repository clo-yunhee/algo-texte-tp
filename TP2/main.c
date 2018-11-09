#include "header.h"

#ifndef RALG
# define RALG naif_bi
#endif // RALG

#define MAX_LINE 128

int main(int argc, char *argv[]) {

    if (argc <= 2) {
        fprintf(stderr, "Usage: %s [mots] [texte]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *motsfile;
    const char *textfile;

    FILE *fmots;
    FILE *ftext;

    int it;
    unsigned int occ;

    char mot[MAX_LINE];
    size_t motlen;
    
    char *text;
    size_t textlen;

    motsfile = argv[1];
    textfile = argv[2];

    fmots = fopen(motsfile, "r");
    if (fmots == NULL) {
        perror("Couldn't open file");
        return EXIT_FAILURE;
    }

    ftext = fopen(textfile, "r");
    if (ftext == NULL) {
        perror("Couldn't open file");
        return EXIT_FAILURE;
    }

    text = NULL;
    if (getdelim(&text, &textlen, '\0', ftext) == -1) {
        perror("Couldn't read the haystack file");
    }

    it = 1;
    while (fgets(mot, MAX_LINE, fmots) != NULL) {
        motlen = strnlen(mot, MAX_LINE);
        // remove trailing newline
        if (mot[motlen - 1] == '\n') {
            mot[motlen - 1] = '\0';
        }

        occ = rechn(RALG, mot, motlen, text, textlen);

        printf("Word #%d: %d occurrences\n", it, occ);

        ++it;
    }

    fclose(fmots);
    fclose(ftext);

    return EXIT_SUCCESS;
}
