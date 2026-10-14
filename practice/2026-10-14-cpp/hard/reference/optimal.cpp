#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
std::pair<long long,int> criticalAssemblyChains(
    int n,
    const std::vector<int>& duration,
    const std::vector<std::pair<int,int>>& prerequisites) {
    constexpr int MOD = 1000000007;
    std::vector<std::vector<int>> adj(n);
    std::vector<int> indegree(n,0), outdegree(n,0);
    for (auto [u,v] : prerequisites) {
        adj[u].push_back(v);
        ++indegree[v];
        ++outdegree[u];
    }
    std::queue<int> q;
    std::vector<long long> best(n,-1);
    std::vector<int> ways(n,0);
    for (int i=0;i<n;++i) if (indegree[i]==0) {
        best[i]=duration[i];
        ways[i]=1;
        q.push(i);
    }
    int processed=0;
    while (!q.empty()) {
        int u=q.front(); q.pop();
        ++processed;
        for (int v:adj[u]) {
            long long candidate=best[u]+duration[v];
            if (candidate>best[v]) {
                best[v]=candidate;
                ways[v]=ways[u];
            } else if (candidate==best[v]) {
                ways[v]=static_cast<int>((static_cast<long long>(ways[v])+ways[u])%MOD);
            }
            if (--indegree[v]==0) q.push(v);
        }
    }
    if (processed!=n) return {-1,0};
    long long makespan=0;
    int count=0;
    for (int i=0;i<n;++i) if (outdegree[i]==0) {
        if (best[i]>makespan) {
            makespan=best[i];
            count=ways[i];
        } else if (best[i]==makespan) {
            count=static_cast<int>((static_cast<long long>(count)+ways[i])%MOD);
        }
    }
    return {makespan,count};
}
