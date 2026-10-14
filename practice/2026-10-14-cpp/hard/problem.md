# Hard / Stretch — Critical Assembly Chains

A factory has n tasks numbered 0..n−1. Task i takes **positive** duration[i] time units. A directed prerequisite pair (u,v) means v cannot start until u finishes. Unlimited parallel workers are available, so all ready tasks can run simultaneously.

Return:
1. The **minimum time to finish every task** (makespan).
2. The number of **distinct critical chains** modulo 1,000,000,007. A critical chain is a directed source-to-sink path (from a task with no prerequisites to a task with no dependents) whose sum of task durations equals the makespan. Different vertex sequences count separately.

If a directed cycle exists, return {-1,0}.

```cpp
std::pair<long long,int> criticalAssemblyChains(
    int n,
    const std::vector<int>& duration,
    const std::vector<std::pair<int,int>>& prerequisites);
```

Examples:
- durations [1,2,2,1], prerequisites [(0,1),(0,2),(1,3),(2,3)] → {4,2}.
- durations [2,2,3,3], prerequisites [(0,2),(1,2),(0,3),(1,3)] → {5,4}.
- durations [3,5,2], no prerequisites → {5,1}.
- durations [1,1], prerequisites [(0,1),(1,0)] → {-1,0}.

Constraints: 1 ≤ n ≤ 200000, duration.size()==n, 1 ≤ duration[i] ≤ 10^9, 0 ≤ prerequisites.size() ≤ 300000, valid vertex indices, no duplicate directed prerequisite pairs. Cycles are possible.

Target: **O(n+m) time/space**. Explain why DAG longest-path DP differs from shortest paths and MST, how ties are counted without enumerating paths, and how to detect cycles.
