#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alg_ac.h"


#define MOTS_INISIZE 5
#define MOTS_LOADFAC 1.75

#define USAGE_STRING "%s [f_mots] [f_texte]"

/** Trim trailing characters */
const char *trimend(char *string, ssize_t *len, char junk) {
    char *original = string + *len;

    while (original != string && *(--original) == junk)
        --(*len);

    if (*original != '\0')
        original[*original == junk ? 0 : 1] = '\0';

    return string;
}

int main(int argc, char *argv[]) {

    FILE *f_mots, *f_texte;

    size_t readlen;
    char *text, *mot;
    ssize_t textlen, motlen;

    const char **mots;
    size_t mots_count, mots_cap;

    struct ac_data *data;
    unsigned int occ;

    if (argc != 3) {
        fprintf(stderr, "Usage: " USAGE_STRING "\n", argv[0]);
        return EXIT_FAILURE;
    }

    f_mots = fopen(argv[1], "r");
    if (f_mots == NULL) {
        perror("Couldn't open mots file");
        return EXIT_FAILURE;
    }

    f_texte = fopen(argv[2], "r");
    if (f_texte == NULL) {
        perror("Couldn't open texte file");
        return EXIT_FAILURE;
    }

    // read texte file
    text = NULL;
    readlen = 0;
    if ((textlen = getdelim(&text, &readlen, '\0', f_texte)) == -1) {
        perror("Couldn't read texte file");
        return EXIT_FAILURE;
    }
    trimend(text, &textlen, '\n');

    fclose(f_texte);

    // read mots file
    mots = malloc(MOTS_INISIZE * sizeof(*mots));
    mots_cap = MOTS_INISIZE;
    mots_count = 0;
   
    mot = NULL;
    readlen = 0;
    while ((motlen = getline(&mot, &readlen, f_mots)) != -1) {
        if (mots_count == mots_cap) {
            mots_cap = (size_t) (mots_cap * MOTS_LOADFAC);
            mots = realloc(mots, mots_cap * sizeof(*mots));
        }
        trimend(mot, &motlen, '\n');
        
        mots[mots_count] = strdup(mot);
        mots_count++;
    }

    free(mot);
    fclose(f_mots);
    
    // execute alg
    data = init_ac(mots, mots_count);

    occ = count_occ_ac(data, text);

    // print result
    
    printf("%d\n", occ);

    // dispose of all resources

    for (size_t n = 0; n < mots_count; ++n) {
        free((char *) mots[n]);
    }
    free(mots);
    free(text);

    dispose_ac(data);

    return EXIT_SUCCESS;

}
