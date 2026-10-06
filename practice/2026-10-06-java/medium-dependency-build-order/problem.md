# Medium — Dependency Build Order

There are n modules 0..n-1. Each dependency [a,b] means a must be built before b. Return a valid order containing every module once; return [] if a cycle exists. For deterministic tests, when several modules are available choose the smallest first.

Signature: `static int[] buildOrder(int n, int[][] dependencies)`

Examples: n=4, [[0,1],[0,2],[1,3],[2,3]] -> [0,1,2,3]; n=3, [[0,1],[1,2],[2,0]] -> [].
