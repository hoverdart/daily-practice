# Hard / Stretch — Critical Firmware Rollout Chains

A firmware project contains n independent-duration tasks, numbered 0 through n-1. Task i takes duration[i] time units (possibly zero). A directed prerequisite edge (u, v) means that task u must finish before v can begin.

The prerequisite graph is guaranteed to be a **DAG**. Tasks with no prerequisites can start at time zero; tasks can run concurrently when their prerequisites allow it. The project's earliest finish time is the **maximum sum of durations on any directed path** (a path may consist of one task).

A *critical chain* is any directed task path whose total duration equals the project's earliest finish time. Return:

1. the earliest finish time;
2. all task IDs appearing on **at least one** critical chain (ascending order);
3. all input prerequisite-edge indices appearing on **at least one** critical chain (ascending order).

Multiple equally long chains matter. Parallel duplicate prerequisite edges, if present, have separate input indices. An isolated zero-duration task belongs to a critical chain if the project's duration is also zero.

Implement:

~~~cpp
struct Dependency {
    int before;
    int after;
};
struct CriticalReport {
    long long finishTime;
    std::vector<int> criticalTasks;
    std::vector<int> criticalDependencies;
};
CriticalReport analyzeCriticalRollout(
    const std::vector<int>& duration,
    const std::vector<Dependency>& dependencies);
~~~

### Example

- duration = [3, 2, 4, 5, 2]
- dependencies = [(0,2), (1,2), (2,3), (2,4)] (indices 0,1,2,3)
- result: finishTime = 12, criticalTasks = [0,2,3], criticalDependencies = [0,2]

The chain 0 -> 2 -> 3 takes 3+4+5=12; it is the unique longest chain.

### Constraints

- 0 <= n <= 100,000; 0 <= dependencies.size() <= 200,000.
- 0 <= duration[i] <= 1,000,000,000.
- Every endpoint is in [0,n), and the graph is acyclic.
- For n=0, return {0, {}, {}}.
- The results must be increasing in their respective ID/index spaces.
- Do not mutate input. Target O(n+m) time and space. Avoid recursion-depth problems on long chains.

### Think first

After a topological order, you can compute the longest path **ending** at each task. What if you also compute the longest path **starting** at each task by walking the order backward? How can these two arrays identify whether an individual vertex or edge is on any maximum-duration path? Why is subtracting the vertex's own duration necessary when combining two vertex-inclusive paths?
