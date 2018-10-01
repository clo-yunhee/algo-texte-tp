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


// load factor
#define LOAD_FACTOR 1.5

// hash the pair (startNode, letter) to [0..maxNode-1]
int hashKey(int maxNode, int startNode, unsigned char letter);

// search for the pair (startNode, letter) in list, NULL otherwise
List listFind(List list, int startNode, unsigned char letter);

// push the node (startNode, letter) in trie, returning the target node number
int pushIfAbsent(Trie trie, int startNode, unsigned char letter);


# endif // TRIE_USE_HACHAGE

#endif // TRIE_HACHAGE_H
