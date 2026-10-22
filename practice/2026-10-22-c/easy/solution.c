#include <stddef.h>

typedef struct Node {
    int id;
    struct Node *left;
    struct Node *right;
} Node;

/* Return 1 iff every node has left/right subtree heights differing by <= 1. */
int tree_is_balanced(const Node *root) {
    (void)root;
    /* TODO: postorder helper should propagate both subtree height and failure. */
    return 0;
}
