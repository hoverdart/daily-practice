# Medium — Fastest Emergency Route

There are `n` intersections numbered `0..n-1` and undirected roads `[u,v,time]`. All travel times are nonnegative integers. Return the minimum travel time from 0 to n-1, or -1 if unreachable.

## Signature
```cpp
long long fastestRoute(int n, const std::vector<std::array<int,3>>& roads);
```

Examples: `n=4, roads={{0,1,5},{1,3,4},{0,2,2},{2,3,10}} -> 9`; `n=3, roads={{0,1,7}} -> -1`; `n=1, roads={} -> 0`.

Target O((V+E) log V).
