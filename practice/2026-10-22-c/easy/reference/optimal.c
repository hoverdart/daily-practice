#include <stddef.h>

typedef struct Node {
    int id;
    struct Node *left;
    struct Node *right;
} Node;

/* Returns subtree height, or -1 if any descendant is unbalanced. */
static int balanced_height(const Node *node) {
    if (node == NULL) return 0;
    int left = balanced_height(node->left);
    if (left == -1) return -1;
    int right = balanced_height(node->right);
    if (right == -1) return -1;
    if (left - right > 1 || right - left > 1) return -1;
    return 1 + (left > right ? left : right);
}

int tree_is_balanced(const Node *root) {
    return balanced_height(root) != -1;
}
