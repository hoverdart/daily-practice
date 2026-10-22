# Reference Notes — Balanced Sensor Hierarchy

## Recognition signals
"Every node," "height of left/right subtree," and recursive binary structure signal **postorder** computation: a parent needs both children's results. C's Node pointers correspond to CS61B Java object references; NULL is an empty tree.

## Brute force versus optimal
A naive recursive check calls a separate height function for each child at every node. In a chain, this repeatedly walks lengths n-1, n-2, ..., 1: **O(n²)** worst-case time. A bottom-up helper returns the subtree height or **-1** as an impossible-height failure sentinel, visiting each node once.

## Correctness invariant
A completed helper call returns the exact height of a fully balanced subtree, or -1 if any descendant violates the balance condition. Empty tree has height 0. If either child returns -1, propagate it; otherwise check the height difference and return 1+max. Induction on subtree size proves that the root's result is nonnegative iff the tree is balanced.

## Complexity
**O(n)** time and **O(h)** call-stack space, O(n) in a chain or O(log n) in a balanced tree. No heap allocation or global state.

## Common mistakes
- Checking the root only, not every descendant.
- Recomputing subtree heights and creating quadratic work.
- Dereferencing NULL or treating an empty tree as unbalanced.
- Returning 0 as the failure sentinel even though 0 is a valid height.
- Confusing height measured downward with depth from the root.

## CS61B connections
Binary-tree recursion, postorder traversal, structural induction, recursive BST helpers, and returning combined summary state from recursive calls. An alternative is a struct {height, balanced} instead of a sentinel.
