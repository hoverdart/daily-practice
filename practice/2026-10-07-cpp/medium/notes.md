# Notes — Fastest Emergency Route

## Recognition signals
Weighted graph + minimum route + nonnegative edge weights => Dijkstra. Equal edge costs => BFS. Negative edges invalidate ordinary Dijkstra.

## Brute force -> optimal
Enumerating paths can be exponential. Dijkstra always expands the currently cheapest tentative state and relaxes outgoing edges.

## Core invariant
When a non-stale `(d,u)` is popped from the min-heap, with nonnegative edges it is safe to finalize that distance. Relax only when `d+w < dist[v]`.

## Complexity
O(V+E) graph space and O((V+E) log V) time with a binary heap.

## Common mistakes
C++ `priority_queue` is a max-heap by default; use `greater<State>`. Skip stale heap entries. Use `long long` for path sums.

## CS61B connection
Direct review of relaxation, adjacency lists, heaps, and Dijkstra. The recent Python attempt recognized shortest paths but needed implementation help, so this removes the coupon/state twist and drills the base algorithm in C++.
