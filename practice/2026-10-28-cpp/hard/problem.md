# Hard / Stretch — Budgeted Long-Cable Network

You are connecting `n` research stations using undirected candidate cables. A cable `(u,v,w)` has a positive integer latency rating `w`. Parallel cables and self-loops may appear.

For a chosen threshold `T >= 0`, call a cable **long** if `w > T`. Your design must select a **spanning tree** (exactly n-1 cables connecting every station, with no cycles), using **at most k long cables**.

Return the **smallest integer threshold T** for which such a spanning tree exists. Return `-1` if the graph cannot be connected even when all cables are allowed.

```cpp
long long minimumCableThreshold(
    int n, const std::vector<std::tuple<int,int,int>>& cables, int k);
```

**Examples**

- `n=4, cables={(0,1,3),(1,2,9),(2,3,5),(0,3,20)}`
  - `k=0` → `9`
  - `k=1` → `5`
  - `k=2` → `3`
  - `k=3` → `0`
- `n=3, cables={(0,1,2)}`, any valid k → `-1` (station 2 is isolated)
- `n=1, cables={}`, `k=0` → `0`

**Constraints:** `1 <= n <= 200000`, `0 <= cables.size() <= 300000`, `0 <= k <= n-1`, endpoints in `[0,n)`, weights `1 <= w <= 10^9`.

**Target:** O((n+m) α(n) log W) time and O(n) extra space beyond the input, where W is the largest weight. No enumeration of spanning trees.

**Think first:** If you connect stations using only cables with `w <= T`, and that leaves c connected components, what is the *minimum possible* number of long cables in any spanning tree? Why does this give a monotone yes/no test suitable for binary search?

