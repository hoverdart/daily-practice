# Reference notes — Merge Two Calibrated Chains

## Recognition signals
Two **already sorted** linked chains, output must reuse nodes, and stable ties: perform the merge step from merge sort with two head pointers and a tail pointer. No priority queue, binary search, or re-sorting needed.

## Brute force → optimal
Copy all values into a vector, sort them, then build a new list: O((n+m) log(n+m)) time and O(n+m) space; violates node-identity and allocation requirements. A recursive merge uses O(n+m) call stack in the worst case. Iteratively compare the two heads and splice the smaller (take `a` on equality), advancing only that input pointer.

## Invariant and correctness
Before each loop, the list from `dummy.next` through `tail` contains exactly the smallest already-selected original nodes in stable sorted order. `a` and `b` point at the smallest remaining node of each list. Appending the smaller head preserves sortedness; equality chooses `a` to satisfy stability. Once either chain is empty, the other chain is already sorted and can be attached in O(1). The stack-local dummy is only a sentinel; its address is never returned.

## Complexity
Every node is selected at most once: O(n+m) time, O(1) auxiliary space. No heap allocation, deletion, or recursion. Original input list boundaries are changed; this is an **in-place destructive merge**. The caller retains ownership of every original node.

## Common mistakes
- Use `<` instead of `<=`, breaking cross-list stability.
- Return `&dummy` (dangling stack pointer) instead of `dummy.next`.
- Forget to move the chosen head or update `tail`, creating loops.
- Assume both inputs are non-null or forget to append the remainder.
- Allocate new nodes despite identity-preserving requirement.
- Recursively merge a 200k-node chain and overflow the stack.

## CS61B and C++ connections
CS61B sentinel nodes and singly linked-list invariants are exactly the tools here. This is the merge step of merge sort without the split step. In C++, `Node*` is a pointer, `p->next` dereferences a member, `nullptr` marks the end, and `Node dummy(0)` is a stack object. Distinguish *rewiring borrowed pointers* from *owning/freeing nodes*; the tests own nodes via `std::unique_ptr` so every node is cleaned up after checking.
