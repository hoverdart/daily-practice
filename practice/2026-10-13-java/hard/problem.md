# Hard / Stretch — Prelinked Fiber Network

There are n stations labeled 0..n-1. Some undirected links already exist and are free. You may purchase optional undirected links with nonnegative costs. Return the **minimum total cost** needed to connect all stations, or -1 if impossible.

Implement `public static long minimumUpgradeCost(int n, int[][] existing, int[][] candidates)`.

Existing links have shape [u,v]; candidates have shape [u,v,cost]. Both lists may contain cycles, duplicates, self-loops, and parallel edges. Do not mutate caller arrays.

Example: n=4, existing=[[0,1],[2,3]], candidates=[[1,2,5],[0,3,2],[0,2,9]]. Answer: 2.

Constraints: n 1..100000; existing and candidate counts each 0..200000; IDs valid; costs 0..1000000000. Use long for totals.

Target: O(E log E + (E+P) alpha(n)) time and O(n+E) extra space (E candidates, P existing links). Sort candidate links and use union-find with path compression and union by size. Explain why this is a minimum spanning tree/forest completion rather than shortest path.
