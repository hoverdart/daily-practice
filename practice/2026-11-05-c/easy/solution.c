#include <stddef.h>

typedef struct Node {
    int reading;
    struct Node *next;
} Node;

Node *stable_faults_last(Node *head) {
    (void)head;
    /* TODO: relink existing nodes into two stable chains and concatenate. */
    return NULL;
}

