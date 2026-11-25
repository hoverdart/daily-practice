# Latest Safe Dispatch — Hard / Stretch

A package must travel from source s to destination t in a directed network. Edge [u,v,w] is a one-way link taking exactly w positive integer minutes. Node v closes at absolute integer time deadline[v]; arrival **and departure** there must occur at or before that deadline. The network is available from time zero. A package may wait at a node while it is open, but waiting is never required. An edge has no closing time of its own.

Find the latest nonnegative integer time at which the package can start at s and still reach t legally. Return -1 if impossible. If s==t, the package can finish instantly at that node. Parallel edges, directed cycles, self-loops and disconnected vertices are allowed.

Implement:

```cpp
long long latestDispatch(
    const std::vector<long long>& deadline,
    const std::vector<std::array<int,3>>& links,
    int s, int t);
```

Example 1:
deadline=[20,7,15,18], links=[[0,1,2],[1,3,3],[0,2,5],[2,3,4]], s=0, t=3.
Answer: 9. Via node 1, leave at most at 5. Via node 2, leave at 9, arrive at 14, finish at 18.

Example 2: deadline=[20,3,30], links=[[0,1,4],[1,2,1]], s=0,t=2 -> -1, even starting at 0 misses node 1's deadline.

Example 3: deadline=[8], links=[], s=0,t=0 -> 8.

Constraints: 1 <= V <= 100,000; 0 <= E <= 200,000; 0 <= deadline[v] <= 10^12; 1 <= w <= 10^9; all endpoints valid. Aim for O(V+E log(E+1)) time (or indexed-heap O((V+E) log V)) and O(V+E) space, without binary searching over absolute time. Explain the ordering and correctness of your relaxation.
