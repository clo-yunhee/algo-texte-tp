#ifndef TRIE_HACHAGE_H
#define TRIE_HACHAGE_H

# ifdef TRIE_USE_HACHAGE

struct _list {
    int startNode,        // etat de depart
        targetNode;       // etat d'arrivee
    char letter; // etiquette de la transition
    struct _list *next;
};

typedef struct _list *List;

struct _trie {
    size_t maxNode;      // nombre max de noeuds
    int lastNode;     // nindice du prochain noeud disponible
    List *transition; // listes d'adjacence
    char *finite;     // etats terminaux
};

typedef struct _trie *Trie;


// load factor
#define LOAD_FACTOR 1.5

// hash the pair (startNode, letter) to [0..maxNode-1]
int hashKey(size_t maxNode, int startNode, char letter);

# endif // TRIE_USE_HACHAGE

#endif // TRIE_HACHAGE_H
