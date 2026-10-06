# Notes

## Recognition signals
Shortest path + one coupon / k wall breaks / fuel / keys = vertex alone is not the full state.

## Brute force -> optimal
Do not choose each coupon edge and rerun shortest path. Use two layers: (node,couponUnused), (node,couponUsed).

## Transitions
From (u,0), traverse normally to (v,0) or spend coupon to (v,1). From (u,1), normal only.

## Invariant
All transformed edge costs are nonnegative, so Dijkstra relaxation and min-PQ finalization logic applies.

## Complexity
2V states and O(E) transformed transitions: O((V+E) log V) time up to constants, O(V+E) space.

## Common mistakes
One dist[node]; merging coupon states; using coupon twice; int overflow; stale PQ entries.

## CS61B connection
Weighted shortest paths + relaxation + heaps, extended by state-space graph modeling.
