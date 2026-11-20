# Hard / Stretch — Cheapest Route After Reversing One Link

## Story

A deployment system routes packages through directed links. Each link `[u,v,w]` transports a package from node `u` to `v` at nonnegative cost `w`. An engineer can **reverse the direction of at most one existing link for the entire route**; the reversed link keeps its original cost. All other links remain as directed. Determine the cheapest possible cost to get from `source` to `target`.

You may reverse **zero or one** edge. The reversal is a one-time change to the selected edge (not a free extra link): it is used as `v -> u` instead of `u -> v`. Parallel links and self-loops are allowed.

Implement:

```js
function cheapestRouteAfterOneFlip(n, edges, source, target) // returns number
```

Return `-1` when the destination cannot be reached even after one reversal.

## Examples

```text
n=3, edges=[[1,0,4],[1,2,2]], source=0,target=2
answer=6              // flip 1->0 into 0->1, then 1->2

n=3, edges=[[0,1,5],[2,1,1]], source=0,target=2
answer=6              // flip 2->1 into 1->2

n=3, edges=[[0,1,7],[1,2,2]], source=0,target=2
answer=9              // no reversal needed

n=3, edges=[], source=0,target=2
answer=-1
```

## Constraints

- `1 <= n <= 100_000`; node IDs are `0..n-1`.
- `0 <= edges.length <= 200_000`.
- `0 <= w <= 1_000_000_000`. All possible simple-path sums stay within JavaScript's safe integer range.
- `0 <= source,target < n`; `source === target` has cost 0.
- Inputs must not be mutated.

## Interview prompts

- Why would adding an undirected link for every edge solve the **wrong** problem?
- What does `distFromSource[v]` mean?
- Why does a Dijkstra on the **reversed graph** give the original graph's distance from `u` to the target?
- What candidate formula corresponds to flipping a specific original edge `u -> v`?
- What changes if negative weights were allowed?

