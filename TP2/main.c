#include "header.h"

#ifndef RALG
# define RALG naif_bi
#endif // RALG

#define MAX_LINE 128

/* trim the last character if it's a newline */
inline char *rtrim(char *string, ssize_t *len, char junk) {
    char *original = string + *len;

    while (original != string && *(--original) == junk)
        --(*len);

    if (*original != '\0')
        original[*original == junk ? 0 : 1] = '\0';

    return string;
}

int main(int argc, char *argv[]) {

    if (argc <= 2) {
        fprintf(stderr, "Usage: %s [mots] [texte] (-q)\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc > 3 && strcmp(argv[3], "-q") == 0) {
        if (freopen("/dev/null", "w", stdout) == NULL) {
            perror("Couldn't redirect standard output to /dev/null");
            fclose(stdout);
        }
    }

    const char *motsfile;
    const char *textfile;

    FILE *fmots;
    FILE *ftext;

    int it;
    unsigned int occ;

    char *mot, *text;
    ssize_t motlen, textlen;
    size_t readlen;
    
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
    readlen = 0;
    if ((textlen = getdelim(&text, &readlen, '\0', ftext)) == -1) {
        perror("Couldn't read the haystack file");
        return EXIT_FAILURE;
    }
    rtrim(text, &textlen, '\n');

    // print in python list format [occ_1, occ_2, ..., occ_n]
    printf("[");

    it = 1;
    mot = NULL;
    readlen = 0;
    while ((motlen = getline(&mot, &readlen, fmots)) != -1) {
        rtrim(mot, &motlen, '\n');

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

        // print newline every N=10 entries
        if (!islast && it % 10 == 0) {
            printf("\n ");
        }

        ++it;
        mot = NULL;
        readlen = 0;
    }

    printf("]\n");

    fclose(fmots);
    fclose(ftext);

    return EXIT_SUCCESS;
}
