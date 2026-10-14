# Reference notes — Critical Assembly Chains

## Recognition signals

**Prerequisites + unlimited parallel workers + minimum time to finish all tasks** means a dependency DAG and **critical-path scheduling**. The makespan is the maximum sum of durations along a source-to-sink chain. This is a **longest weighted path in a DAG**, not a shortest route (Dijkstra), and not minimum total wiring cost (MST/Kruskal). Longest paths in arbitrary graphs are hard, but DAG topological order makes them linear-time.

## Brute force versus optimal

Enumerate every source-to-sink path, sum durations, count those attaining the maximum. Layered DAGs can have exponentially many paths. Instead aggregate by ending vertex: best[v] is maximum duration of a source-to-v chain, ways[v] counts chains attaining best[v], modulo 1e9+7.

## Topological DP invariant

Build adjacency, indegree, outdegree. Initialize best[source]=duration[source], ways[source]=1 for every indegree-zero source; other vertices start best=-1, ways=0. Process sources using Kahn's queue. When u is removed, all its predecessors have been processed, so best[u] and ways[u] are final. For each edge u→v, candidate=best[u]+duration[v]:

- If candidate > best[v], replace best[v] and set ways[v]=ways[u].
- If candidate == best[v], add ways[u] modulo MOD.
- If smaller, ignore.

Decrement indegree[v], enqueue at zero. If fewer than n vertices are processed, a cycle exists and the answer is {-1,0}. Examine **sinks only** (outdegree zero), take maximum best[sink], sum ways[sink] across tied sinks. Positive durations ensure that completing all tasks takes the duration of a longest source-to-sink chain.

## Complexity

O(n+m) time: each vertex queued once, each edge relaxed once. O(n+m) space for adjacency, degree arrays, DP, counts, queue. A chain can total n·1e9 ≤ 2e14, so use long long. Counts can grow exponentially; reduce modulo 1,000,000,007.

## Common mistakes

- Use Dijkstra or Kruskal, which solve different graph objectives.
- Sum all task durations, ignoring parallel execution.
- Initialize every vertex as a source, counting invalid mid-chain starts.
- Overwrite ways on ties rather than adding; count inferior paths.
- Sum ways from all vertices rather than only critical sinks.
- Lose original sink information by reusing mutated indegree arrays.
- Use int for accumulated duration; ignore cycles; recurse through a 150k-deep chain.

## CS61B / C++ connection

Kahn's algorithm is queue-based graph traversal; longest-path DP uses the **relaxation** idea from shortest paths but takes max in topological order. Ways is a second DP state layered on the optimum. vector<vector<int>> stores adjacency, queue<int> ready tasks, pair<long long,int> returns result. Contrast union-find/Kruskal (connect-all cost) and Dijkstra/heap (minimum-sum route). Classify the objective before picking an algorithm.
