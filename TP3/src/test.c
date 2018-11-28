#include "alg_ac.h"
#include "queue.h"

#include <assert.h>

int main(void) {

    Queue q;
    Trie t, x;
   
    q = createQueue(3);

    assert( isEmpty(q) );

    enqueue(q, 2);
    enqueue(q, 80);
    enqueue(q, 13);

    assert(isFull(q));

    assert( dequeue(q) == 2 );
    assert( dequeue(q) == 80 );
    assert( dequeue(q) == 13 );

    assert( isEmpty(q) );

    t = createTrie(100);

    insertInTrie(t, "ab");
    insertInTrie(t, "cj");

    assert( isInTrie(t, "ab") );
    assert( isInTrie(t, "cj") );
    
    assert( !isInTrie(t, "") );
    assert( !isInTrie(t, "a") );
    assert( !isInTrie(t, "b") );
    assert( !isInTrie(t, "c") );

    x = createTrie(10);

    insertInTrie(x, "c");
    insertInTrie(x, "abcb");
    insertInTrie(x, "zzz");

    assert( isInTrie(x, "c") );
    assert( isInTrie(x, "abcb") );
    assert( isInTrie(x, "zzz") );

    
    mergeTries(&t, x, 100);

    assert( isInTrie(t, "zzz") );
    assert( isInTrie(t, "c") );
    assert( isInTrie(t, "abcb") );

    assert( isInTrie(t, "ab") );
    assert( isInTrie(t, "cj") );

    assert( !isInTrie(t, "") );
    assert( !isInTrie(t, "a") );
    assert( !isInTrie(t, "b") );
    assert( !isInTrie(t, "zz") );
    assert( !isInTrie(t, "abc") );


    freeTrie(t);
    //freeTrie(x);

    return 0;

}
