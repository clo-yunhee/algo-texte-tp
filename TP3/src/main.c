#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "search.h"


#define MOTS_INISIZE 5
#define MOTS_LOADFAC 1.75

#define USAGE_STRING "%s [f_mots] [f_texte]"


/** Trim trailing characters */
void trimend(char *string, ssize_t *len, char junk);

/** Read one line of the file */
const char *readline(FILE *f);

/** Read the mots file and fill it in a dynamic array */
const char **readmots(FILE *f, size_t *length);


int main(int argc, char *argv[]) {

    FILE *f_mots, *f_texte;

    const char *text;

    const char **mots;
    size_t mots_count;

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
    text = readline(f_texte);
    fclose(f_texte);

    // read mots file
    mots = readmots(f_mots, &mots_count);
    fclose(f_mots);
    
    // execute alg
    occ = search(mots, mots_count, text);

    // print result
    printf("%d\n", occ);

    // dispose of all resources
    free((char *) text);
    for (size_t n = 0; n < mots_count; ++n) {
        free((char *) mots[n]);
    }
    free(mots);

    return EXIT_SUCCESS;
}

const char **readmots(FILE *f, size_t *length) {
    const char *mot, **mots;
    size_t capacity;

    mots = malloc(MOTS_INISIZE * sizeof(*mots));
    capacity = MOTS_INISIZE;
    *length = 0;
   
    while ((mot = readline(f)) != NULL) {
        if (*length == capacity) {
            capacity = (size_t) (capacity * MOTS_LOADFAC);
            mots = realloc(mots, capacity * sizeof(*mots));
        }
        
        mots[(*length)++] = mot;
    }

    return mots;
}


void trimend(char *string, ssize_t *len, char junk) {
    char *original = string + *len;

    while (original != string && *(--original) == junk)
        --(*len);

    if (*original != '\0')
        original[*original == junk ? 0 : 1] = '\0';
}

const char *readline(FILE *f) {
    char *glmot;
    size_t readlen;
    
    char *mot;
    ssize_t motlen;

    glmot = NULL;
    readlen = 0;

    motlen = getline(&glmot, &readlen, f);
    if (motlen == -1) {
        free(glmot);
        return NULL;
    }
    
    mot = strdup(glmot);
    free(glmot);

    trimend(mot, &motlen, '\n');

    return mot;
}
