# Hard / Stretch — Second Distinct Dispatch Arrival

Dispatchers can traverse an undirected network of positively weighted links. A dispatch **walk** starts at a given vertex and ends at a target; it may revisit vertices or links, including the target before the final arrival. The cost is the sum of weights of every traversal.

Return the second **distinct** achievable total cost from start to target: the smallest cost strictly greater than the minimum achievable cost. Different walks of the same cost count only once. Return -1 if fewer than two distinct costs exist.

```java
public static long secondArrival(int n, int[][] links, int start, int target)
```

Each links[i] is [u,v,w], representing a bidirectional edge of positive weight. Parallel edges are allowed; no self-loops. Vertices are 0 through n-1. Do not modify links.

## Examples
- n=2, links=[[0,1,5]], start=0, target=1 -> 15. The shortest walk costs 5; the next distinct cost comes from 0->1->0->1. There is no alternative simple path.
- n=3, links=[[0,1,1],[1,2,1],[0,2,2]], start=0, target=2 -> 4. Two routes of cost 2 are tied for first; 4 is the next distinct cost.
- n=2, links=[[0,1,3],[0,1,3],[0,1,4]], start=0, target=1 -> 4.
- n=3, links=[[0,1,1]], start=0, target=2 -> -1.
- start=target, n=2, links=[[0,1,5]] -> 10 (empty walk costs 0). With no incident edges, answer -1.

## Constraints
- 1 <= n <= 100,000; 0 <= links.length <= 200,000.
- 1 <= w <= 1,000,000,000.
- Valid vertices, non-null input.
- Use long for costs. Aim for O(n + m log(m+1)) time with a lazy priority queue and O(n+m) space.
- The problem asks for walks, **not** the second shortest simple path. No need to list the walks.
