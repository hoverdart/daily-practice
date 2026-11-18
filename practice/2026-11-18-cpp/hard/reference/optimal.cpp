#include <algorithm>
#include <queue>
#include <vector>

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
    const std::vector<Dependency>& dependencies) {
    const int n = static_cast<int>(duration.size());
    if (n == 0) return {0, {}, {}};

    std::vector<std::vector<int>> outgoing(n);
    std::vector<int> indegree(n, 0);
    for (const Dependency& e : dependencies) {
        outgoing[e.before].push_back(e.after);
        ++indegree[e.after];
    }

    std::queue<int> ready;
    for (int u = 0; u < n; ++u)
        if (indegree[u] == 0) ready.push(u);

    std::vector<int> order;
    order.reserve(n);
    while (!ready.empty()) {
        const int u = ready.front();
        ready.pop();
        order.push_back(u);
        for (int v : outgoing[u]) {
            if (--indegree[v] == 0) ready.push(v);
        }
    }
    // Input contract guarantees DAG, hence order.size() == n.

    std::vector<long long> ending(n), starting(n);
    for (int i = 0; i < n; ++i) {
        ending[i] = duration[i];
        starting[i] = duration[i];
    }

    for (int u : order) {
        for (int v : outgoing[u]) {
            ending[v] = std::max(ending[v],
                ending[u] + static_cast<long long>(duration[v]));
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        const int u = order[i];
        for (int v : outgoing[u]) {
            starting[u] = std::max(starting[u],
                static_cast<long long>(duration[u]) + starting[v]);
        }
    }

    const long long longest =
        *std::max_element(ending.begin(), ending.end());

    CriticalReport result{longest, {}, {}};
    for (int u = 0; u < n; ++u) {
        if (ending[u] + starting[u] - duration[u] == longest) {
            result.criticalTasks.push_back(u);
        }
    }
    for (int i = 0; i < static_cast<int>(dependencies.size()); ++i) {
        const Dependency& e = dependencies[i];
        if (ending[e.before] + starting[e.after] == longest) {
            result.criticalDependencies.push_back(i);
        }
    }
    return result;
}
