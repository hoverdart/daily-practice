struct Node {
    int value;
    Node* next;
    explicit Node(int v, Node* n = nullptr) : value(v), next(n) {}
};

Node* mergeCalibratedChains(Node* a, Node* b) {
    // TODO: relink nodes, taking from a first on equal values.
    // You may use a stack-allocated dummy sentinel; do not allocate nodes.
    (void)b;
    return a;
}
