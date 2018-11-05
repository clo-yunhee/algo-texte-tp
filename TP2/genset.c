#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mtrand.h"

#define START '!' // 42
#define END   '~' // 126

#define MAX_NB (END - START)

int main(int argc, char *argv[]) {
    
    if (argc <= 3) {
        fprintf(stderr, "Usage: %s [card] [len] [file] [count=1]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int i;

    int nb_lettres, lg_texte, count;
    const char *filename;
    FILE *f;
    
    char *alphabet;
    char lettre;

    nb_lettres = atoi(argv[1]);
    lg_texte = atoi(argv[2]);
    filename = argv[3];
    count = (argc > 4) ? atoi(argv[4]) : 1;

    if (nb_lettres > MAX_NB) {
        fprintf(stderr, "Alphabet size too high. (max %d)", MAX_NB);
    }

    f = fopen(filename, "w");
    if (f == NULL) {
        perror("Couldn't open file");
        return EXIT_FAILURE;
    }
   
    alphabet = malloc(nb_lettres * sizeof (*alphabet));
    for (i = 0; i < nb_lettres; ++i) {
        alphabet[i] = (char) (START + i);
    }
    
    // init mt19937 random generator
    sgenrand(time(NULL));
  
    while (count > 0) {
        for (i = 0; i < lg_texte; ++i) {
            lettre = alphabet[genrand() % nb_lettres];
            fputc(lettre, f);
        }

        fputc('\n', f);
        
        --count;
    }

    fclose(f);

    return EXIT_SUCCESS;
}


