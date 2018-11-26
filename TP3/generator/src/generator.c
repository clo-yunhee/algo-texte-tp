#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <errno.h>
#include <stdint.h>
#include <limits.h>

#include <sys/random.h>

#include "mtrand.h"


#define START '!' // 42
#define END   '~' // 126

#define MAX_NB (END - START)

#define GEN_TXT "genere-texte"
#define GEN_MOT "genere-mots"

#define USG_TXT "%s [longueur] [alphabet]"
#define USG_MOT "%s [nb_mots] [long_min] [long_max] [alphabet]"


/** Parses base-10 number into res , returns a negative value on error. */
signed char stoi(const char *str, size_t *res);

/** Random number with mt19937, between min (inclusive) and max (exclusive) */
size_t randrange(size_t min, size_t max);

/** Returns basename of the path (pointer on the same string) */
const char *basename(const char *str);

int main(int argc, char *argv[]) {
    
    size_t nb_lettres, lg_min, lg_max, count;

    // process arguments depending on the program name

    const char *exe = basename(argv[0]);

    if (strcmp(exe, GEN_TXT) == 0) {
        if (argc != 3
                || stoi(argv[1], &lg_min) < 0
                || stoi(argv[2], &nb_lettres) < 0) {
            fprintf(stderr, "Usage: " USG_TXT "\n", argv[0]);
            return EXIT_FAILURE;
        }
        count = 1;
        lg_max = lg_min;
    }
    else if (strcmp(exe, GEN_MOT) == 0) {
        if (argc != 5
                || stoi(argv[1], &count) < 0
                || stoi(argv[2], &lg_min) < 0
                || stoi(argv[3], &lg_max) < 0
                || stoi(argv[4], &nb_lettres) < 0) {
            fprintf(stderr, "Usage: " USG_MOT "\n", argv[0]);
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Usage: le nom du programme doit être "
                            GEN_TXT " ou " GEN_MOT "\n");
        return EXIT_FAILURE;
    }

    if (nb_lettres < 1 || nb_lettres > MAX_NB) {
        fprintf(stderr, "Usage: la taille de l'alphabet doit être positive et inférieure à %d\n", MAX_NB);
    }
    
    size_t i, lg;
    char lettre;

    // alphabet will be small enough to alloc on the stack
    char alphabet[nb_lettres];

    for (i = 0; i < nb_lettres; ++i) {
        alphabet[i] = (char) (START + i);
    }
    
    // initialise the random number generator
    unsigned long seed; 
    getrandom(&seed, sizeof(seed), 0);
    sgenrand(seed);
  
    while (count > 0) {
        lg = randrange(lg_min, lg_max+1);
        for (i = 0; i < lg; ++i) {
            lettre = alphabet[randrange(0, nb_lettres)];
            putchar(lettre);
        }

        putchar('\n');
        
        --count;
    }

    return EXIT_SUCCESS;
}

signed char stoi(const char *str, size_t *res) {
    char *endptr;
    long val;

    errno = 0;
    val = strtol(str, &endptr, 10);

    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) // long range errors
            || (errno != 0 && val == 0))
        return -1;
    if (val < 0 || val > SIZE_MAX) // must fit insize size_t
        return -2;
    if (endptr == str // needs to be non-empty
            || *endptr != '\0') // and only contain the number
        return -3;

    *res = (size_t) val;

    return 1;
}

size_t randrange(size_t min, size_t max) {
    if (min >= max) // default also if min > max
        return min;
    else if (min > 0)
        return min + randrange(0, max - min);
    else
        return genrandr(max);
}

const char *basename(const char *str) {
    char *p = strrchr(str, '/');
    return p ? p + 1 : str;
}
