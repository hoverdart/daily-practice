# Reference notes — Budgeted Long-Cable Network

## Recognition signals
The requirement is to connect **all** vertices using a **spanning tree**, with a bound on how many selected edges exceed a chosen threshold. This is a connectivity/MST-family problem, not a source-to-target shortest path. The unknown answer is a number T, and "can we meet the constraint at T?" becomes easier as T grows: classic **binary search on a monotone predicate**.

## Brute force versus optimal
Enumerating every subset of n-1 cables and testing whether it is a spanning tree is exponential in m. Another approach could sort cables by weight and reason about the (k+1)th-largest edge in an optimal spanning tree, but it is easy to mishandle disconnected cases. The reference uses a direct DSU feasibility test and binary search over integer T.

## Key lemma: c-1 expensive edges
Fix T and build the graph containing only **cheap** edges, those with w<=T. Suppose it has c connected components. Any spanning tree must connect those c components, so it needs at least c-1 edges crossing between components; every such edge is long (w>T). Conversely, if the original graph is connected, contracting the c cheap components produces a connected graph whose intercomponent edges are all long. Select a spanning tree of this contracted graph, using exactly c-1 long edges; inside each cheap component, use a cheap spanning tree. The union is a full spanning tree. Therefore **feasible(T) iff c-1<=k**, provided the original graph is connected.

This proof explains why no shortest-path algorithm is needed. It also handles parallel edges and self-loops: DSU ignores edges whose endpoints are already joined.

## Binary-search invariant and correctness
First union all cables; if the graph is disconnected, return -1. Otherwise T=maxWeight is always feasible, and T=0 is the smallest permitted threshold. Binary-search the smallest feasible T in the inclusive interval [lo,hi]. For mid, union only edges w<=mid and count cheap components. If components<=k+1, mid is feasible, so set hi=mid; otherwise set lo=mid+1. Feasibility is monotone because adding more cheap edges cannot increase component count. On termination lo=hi is the minimum feasible threshold. For n=1 the empty spanning tree works at T=0.

## Complexity
One full-connectivity DSU pass takes O((n+m) α(n)). Each feasibility check rebuilds DSU in O(n) and scans m edges in O(m α(n)), for O((n+m) α(n) log(W+1)) time overall and O(n) auxiliary space (parent and size arrays). W<=10^9, so there are at most about 30 binary-search iterations. Input edges are never copied or sorted.

## Common mistakes
- Check whether the **cheap** graph itself is connected, incorrectly requiring zero long cables even when k>0.
- Use c instead of c-1 for the minimum number of long edges.
- Skip the initial full-connectivity check, mistakenly treating an impossible graph as feasible when k is large.
- Treat w>=T as long; the definition is **strictly w>T**.
- Forget that T=0 is valid even though all input weights are positive.
- Use Dijkstra (optimizes one route), or Kruskal without explaining the spanning-tree budget.
- Reuse a mutated DSU across binary-search probes instead of rebuilding it.
- Mishandle n=1, self-loops, or duplicate edges.

## CS61B connections
Union-find is weighted quick union plus path compression, giving inverse-Ackermann amortized operations. Kruskal's MST algorithm uses the same DSU to avoid cycles, but here DSU identifies components under a threshold. The cut/contracted-component argument is an MST-style connectivity invariant. Binary search on the answer connects CS61B logarithmic runtime reasoning with a monotone graph feasibility predicate.

