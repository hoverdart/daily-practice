# Cheapest Transfer with Refund Loops (Hard / Stretch)

A directed transfer network charges a signed integer fee for each transfer. Negative fees represent credits. A transfer may be taken any number of times, and vertices may be revisited. Find the cheapest total fee of a finite walk from start to target, taking into account possible arbitrarily large accumulated credits.

Implement `cheapestRefundRoute(n, edges, start, target)` in solution.js. Vertices are 0 through n-1. Each edge is `[u,v,w]`, directed u to v with fee w. Return:
- `null` if no walk reaches target;
- the minimum finite total fee (a JavaScript Number) if it exists;
- exactly the string `"UNBOUNDED"` if for every integer B some start-to-target walk has total fee below B.

The zero-edge walk has fee 0 when start equals target; a relevant negative cycle can still make that answer unbounded. Parallel edges and self-loops are allowed. A walk may visit target before its final arrival. Do not mutate edges.

## Examples
1. `n=3, edges=[[0,1,5],[0,2,2],[1,2,-10]], start=0, target=2` -> -5.
2. `n=4, edges=[[0,1,1],[1,1,-1],[0,3,6]], start=0, target=3` -> 6. The negative loop cannot lead to the target.
3. `n=4, edges=[[0,1,2],[1,2,-5],[2,1,1],[2,3,7]], start=0, target=3` -> "UNBOUNDED".
4. `n=3, edges=[[0,1,-9],[1,1,-1]], start=0, target=2` -> null.
5. `n=1, edges=[[0,0,-1]], start=0, target=0` -> "UNBOUNDED".

## Constraints
- 1 <= n <= 2,000; 0 <= edges.length <= 10,000; n * edges.length <= 10,000,000.
- Fees are integers in [-10^6,10^6]; all intermediate values under these limits fit safely in JavaScript Number integer precision.
- Aim for O(n * E + n + E) worst-case time and O(n + E) auxiliary space, with early exit where possible.
- A nonnegative-weight shortest-path algorithm alone is not sufficient.

Run `node tests.js`. Suggested time: 40–65 minutes.
