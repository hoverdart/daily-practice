# Easy — Balanced Sensor Hierarchy

A binary tree stores sensors. An empty subtree has height 0; otherwise its height is 1 + max(left height, right height). It is **height-balanced** when **every** node's left and right subtree heights differ by at most 1.

Implement in C:

    typedef struct Node { int id; struct Node *left, *right; } Node;
    int tree_is_balanced(const Node *root);

Return 1 if balanced, 0 otherwise. Empty tree → 1; root with two leaves → 1; a chain of three nodes → 0. A tree can be balanced at its root yet unbalanced deeper inside. IDs may repeat.

Constraints: 0 ≤ n ≤ 2,000, valid acyclic binary tree. Do not mutate or allocate tree nodes. Target O(n) time and O(h) auxiliary call-stack space.

**Hint to consider only after attempting:** Instead of recomputing height at every node, can a postorder helper return either a subtree height or a special failure sentinel?
