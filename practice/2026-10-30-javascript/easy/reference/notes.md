# Explanation — Closest Shared Supervisor

## Recognition signals
"Unique parent," "rooted hierarchy," "closest common ancestor," and "possibly disconnected" suggest ancestor-chain intersection in a rooted forest. There is no need for full BFS/DFS or tree construction.

## Brute force versus optimal
**Brute force:** climb a's ancestors and, for every candidate, climb all of b's ancestors to test membership. Worst case `O(h_a h_b)` time and `O(1)` extra space.

**Optimal:** insert all of a's ancestors into a JavaScript `Set`. Starting at b, climb toward the root; the first member in that set is the deepest shared ancestor. Expected `O(h_a+h_b)` time and `O(h_a)` auxiliary space (expected constant-time Set membership). No recursion and no mutation.

## Invariant / correctness
After the first loop, `ancestors` is exactly the ancestor chain of a, including a. The second loop visits b's ancestors from **deepest to shallowest**. Any common ancestor must occur in both chains, so the first encountered match is the lowest one. If no match exists, the roots differ and the answer is -1.

## Common mistakes
- Excluding a or b themselves (they can be their own ancestor).
- Assuming every employee belongs to the same tree.
- Assuming parent IDs are smaller than child IDs; not promised.
- Recursing on a chain of 200,000 employees and overflowing the JS call stack.
- Comparing only immediate parents rather than all ancestors.

## CS61B connections
Rooted trees, reference/pointer chains, and the `parent` / `edgeTo` arrays used to reconstruct graph search paths. The `Set` is a hash-based membership index: the key improvement is **representation**, not a complicated traversal. For many repeated LCA queries, preprocess depths/binary lifting instead of rebuilding a set per query.
