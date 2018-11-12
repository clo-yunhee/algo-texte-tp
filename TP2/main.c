#include "header.h"

#ifndef RALG
# define RALG naif_bi
#endif // RALG

#define MAX_LINE 128

/* trim the last character if it's a newline */
inline void rtrim(char *str, size_t *len) {
    size_t l = --(*len);
    if (str[l] == '\n')
        str[l] = '\0';
}

int main(int argc, char *argv[]) {

    if (argc <= 2) {
        fprintf(stderr, "Usage: %s [mots] [texte] (-q)\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc > 3 && strcmp(argv[3], "-q") == 0) {
        freopen("/dev/null", "w", stdout);
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
    
    bool islast;

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
    textlen = 0;
    if (getline(&text, &textlen, ftext) == -1) {
        perror("Couldn't read the haystack file");
        return EXIT_FAILURE;
    }
    rtrim(text, &textlen);

    // print in python list format [occ_1, occ_2, ..., occ_n]
    printf("[");

    it = 1;
    while (fgets(mot, MAX_LINE, fmots) != NULL) {
        motlen = strnlen(mot, MAX_LINE);
        rtrim(mot, &motlen);

        occ = rechn(RALG, mot, motlen, text, textlen);

        islast = ({
            const char c = fgetc(fmots);
            ungetc(c, fmots);
            c == EOF;
        });

        // print "it: occ", with a comma if not last
        if (islast) {
            printf("%d", occ);
        } else {
            printf("%d, ", occ);
        }

        ++it;

        // print newline every N=10 entries
        if (!islast && it % 10 == 1) {
            printf("\n ");
        }
    }

    printf("]\n");

    fclose(fmots);
    fclose(ftext);

    return EXIT_SUCCESS;
}
