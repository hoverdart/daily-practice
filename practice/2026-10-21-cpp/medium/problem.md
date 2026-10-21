# Medium — Longest Low-Collision Window

A telemetry stream contains integer device IDs. A **collision pair** in a contiguous window is an unordered pair of *different positions* (i,j), i<j, with the same ID. For example, [4,7,4,4] contains 3 collision pairs (all among the three 4s).

Given `ids` and a nonnegative budget `k`, find the **longest contiguous half-open window [left,right)** containing **at most k collision pairs**. If several windows have the same maximum length, return the one with the **smallest left index**. For empty input return {0,0}.

```cpp
std::pair<int,int> longestLowCollisionWindow(
    const std::vector<int>& ids, long long k);
```

Examples:
- ids=[1,2,1,2,1], k=1 → {0,3}, window [1,2,1].
- ids=[5,5,5], k=0 → {0,1}; k=1 → {0,2}; k=3 → {0,3}.
- ids=[9,8,7], k=0 → {0,3}.
- ids=[], k=10 → {0,0}.

**Constraints:** 0 ≤ n ≤ 200,000; IDs are any signed 32-bit integers; 0 ≤ k ≤ 20,000,000,000. Target expected O(n) time, O(number of distinct IDs in window) auxiliary space. Explain why the pair counter can be updated in O(1) when one value enters or leaves, and why a 64-bit counter is required.
