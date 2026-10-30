# Hard / Stretch — Critical Route Count in a DAG

A build pipeline contains `n` stages and directed transitions. The pipeline is a **DAG** (directed acyclic graph): a stage can depend on others, but no dependency cycle exists.

Each transition `[u, v, w]` contributes an integer **score change** `w` to a route. Scores can be **negative**, zero, or positive. You need to find the **maximum total score** among all directed routes from `start` to `target`, and count how many distinct routes achieve that maximum, modulo `1_000_000_007`.

Implement:

```javascript
function criticalRouteCount(n, edges, start, target) {
  // Return { maxWeight: number | null, ways: number }.
}
```

**Input:**
- `1 <= n <= 100000`, vertices labeled `0..n-1`.
- `0 <= edges.length <= 200000`. Each edge is `[u,v,w]`, with `u != v`, `-1000000 <= w <= 1000000`.
- The directed graph is acyclic, but **vertex IDs are not a topological order**.
- No duplicate directed edge `(u,v)` occurs. Distinct routes are distinct sequences of vertices.
- `start` and `target` are valid vertex IDs.

**Output:**
- If unreachable: `{ maxWeight: null, ways: 0 }`.
- Otherwise: maximum total weight and number of maximizing paths modulo `1_000_000_007`.
- A zero-edge route from a vertex to itself has weight 0 and counts as **one** route. In a DAG, there is no nonempty route from a vertex back to itself.
- Do not mutate inputs.

**Examples:**

```javascript
criticalRouteCount(5, [
  [0,1,2],[0,2,2],[1,3,3],[2,3,3],[3,4,-2],[0,4,1]
], 0, 4);
// { maxWeight: 3, ways: 2 }  // 0-1-3-4 and 0-2-3-4

criticalRouteCount(4, [[0,1,-2],[1,3,-4],[0,2,-1],[2,3,-3]],0,3);
// { maxWeight: -4, ways: 1 }

criticalRouteCount(3, [[2,0,7]], 1, 0);
// { maxWeight: null, ways: 0 }
```

**Target:** `O(n+m)` time and `O(n+m)` space, where `m=edges.length`. Use topological sorting (Kahn or DFS) and dynamic programming; **Dijkstra is invalid for negative weights** and cannot solve this longest-route objective.

**Optional hint:** When all predecessors of a vertex have been processed, its best score and count are final. Relax `u -> v`: overwrite count on strictly better score, add counts on equal score.
