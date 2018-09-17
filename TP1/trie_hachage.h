#ifndef TRIE_HACHAGE_H
#define TRIE_HACHAGE_H

# ifdef TRIE_USE_HACHAGE

struct _list {
    int startNode,        // etat de depart
        targetNode;       // etat d'arrivee
    unsigned char letter; // etiquette de la transition
    struct _list *next;
};

typedef struct _list *List;

struct _trie {
    int maxNode;      // nombre max de noeuds
    int nextNode;     // nindice du prochain noeud disponible
    List *transition; // listes d'adjacence
    char *finite;     // etats terminaux
};

typedef struct _trie *Trie;

# endif // TRIE_USE_HACHAGE

#endif // TRIE_HACHAGE_H
