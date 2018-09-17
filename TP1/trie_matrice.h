#ifndef TRIE_MATRICE_H
#define TRIE_MATRICE_H

# ifdef TRIE_USE_MATRICE

struct _trie {
    int maxNode;      // nombre max de noeuds
    int nextNode;     // indice du prochain noeud disponible
    int **transition; // matrice de transitions
    char *finite;     // etats terminaux
};

typedef struct _trie *Trie;

# endif // TRIE_USE_MATRICE

#endif // TRIE_MATRICE_H
