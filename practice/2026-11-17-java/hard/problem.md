# Safest Bottleneck Route Queries — Hard / Stretch

You operate an undirected network of n relay stations, numbered 0 through n-1. Each existing cable has an integer **exposure level** w. For a route, its bottleneck exposure is the **maximum edge exposure on that route** (not the sum of exposures).

For each query [source, target], report the **minimum achievable bottleneck exposure among all routes** from source to target. Return -1 if the vertices are disconnected. Return 0 when source == target, since the empty route uses no edges.

Implement:

~~~java
public static int[] minimumBottleneckCosts(int n, int[][] edges, int[][] queries)
~~~

Each edge is [u, v, exposure], undirected. Cables can be parallel; self-loops can occur. The original input graph need not be connected. Do not modify either input array.

Example:

~~~text
n = 5
edges = [
  [0,1,9], [1,2,5], [0,2,8],
  [2,3,2], [3,4,10], [1,4,1]
]
queries = [[0,2], [0,4], [3,4], [0,0], [0,3]]
answer  = [8, 8, 5, 0, 8]
~~~

For 0 to 4, take 0–2–1–4, whose worst cable has exposure 8. A shorter-in-edges route 0–1–4 has a worse bottleneck 9. This is **not a shortest-sum problem**.

**Constraints:** 1 <= n <= 100,000; 0 <= edges.length <= 200,000; 0 <= queries.length <= 200,000; 0 <= exposure <= 1,000,000,000; all endpoints in [0,n). Queries may repeat. Answers fit in signed 32-bit int.

Aim for approximately **O(m log m + (n+q) log n)** time and **O(m + n log n)** auxiliary space, excluding result, using a minimum-spanning forest followed by binary-lifting maximum-edge queries. Kruskal's sorting plus union-find may be used. A less efficient but correct per-query minmax-Dijkstra baseline is useful for reasoning.

Interview checkpoints: Why can a minimum-spanning **forest** answer bottleneck queries even though it is not built for shortest sums? How do you answer maximum-edge-on-tree-path queries efficiently after preprocessing? Why is a normal BFS or shortest-sum Dijkstra incorrect for this objective?

