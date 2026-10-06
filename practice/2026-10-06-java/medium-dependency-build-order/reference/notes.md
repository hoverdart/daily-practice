# Notes

## Recognition signals
"Must happen before", prerequisites, dependencies, scheduling = directed graph + topological sort.

## Brute force -> optimal
Permutations are O(V!). Kahn repeatedly emits vertices with zero remaining prerequisites.

## Invariant
indegree[v] is the number of prerequisites not yet removed. Zero means safe to emit.

## Cycle detection
If the queue empties before V outputs, the remainder contains a directed cycle.

## Complexity
Kahn is O(V+E); deterministic min-heap tie-breaking gives O((V+E) log V), O(V+E) space.

## Common mistakes
Reversed edges; wrong indegree updates; treating arbitrary DFS/BFS order as topological; missing disconnected components.

## CS61B connection
DAGs/topological ordering; compare Kahn with DFS reverse postorder.
