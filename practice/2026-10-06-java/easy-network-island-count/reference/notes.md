# Notes

## Recognition signals
Objects + undirected pairwise connections + separate groups = connected components.

## Brute force -> optimal
Do not redo reachability for every pair. Start DFS/BFS only from an unseen vertex; that traversal marks one whole component.

## Invariant
Every seen vertex belongs to a component already counted. Each unseen outer-loop start creates exactly one new component.

## Complexity
O(V+E) time and O(V+E) space with adjacency lists.

## Common mistakes
One-way edges in an undirected graph; counting every vertex; marking visited too late; forgetting isolated vertices.

## CS61B connection
Canonical graph traversal/connected-components pattern. DFS and BFS are interchangeable here.
