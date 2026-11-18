#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include "solution.cpp"

static void same(const CriticalReport& got, const CriticalReport& expected) {
    assert(got.finishTime == expected.finishTime);
    assert(got.criticalTasks == expected.criticalTasks);
    assert(got.criticalDependencies == expected.criticalDependencies);
}

// Independent enumeration of ALL directed paths in tiny DAGs.
static CriticalReport brute(
    const std::vector<int>& duration,
    const std::vector<Dependency>& edges) {
    const int n = static_cast<int>(duration.size());
    if (n == 0) return {0, {}, {}};
    std::vector<std::vector<int>> out(n);
    for (int i = 0; i < static_cast<int>(edges.size()); ++i)
        out[edges[i].before].push_back(i);

    long long best = -1;
    uint64_t taskUnion = 0;
    uint64_t edgeUnion = 0;
    std::function<void(int, long long, uint64_t, uint64_t)> dfs =
        [&](int u, long long length, uint64_t taskBits, uint64_t edgeBits) {
            if (length > best) {
                best = length;
                taskUnion = taskBits;
                edgeUnion = edgeBits;
            } else if (length == best) {
                taskUnion |= taskBits;
                edgeUnion |= edgeBits;
            }
            for (int id : out[u]) {
                const int v = edges[id].after;
                dfs(v, length + duration[v],
                    taskBits | (uint64_t{1} << v),
                    edgeBits | (uint64_t{1} << id));
            }
        };
    for (int u = 0; u < n; ++u)
        dfs(u, duration[u], uint64_t{1} << u, 0);

    CriticalReport res{best, {}, {}};
    for (int u = 0; u < n; ++u)
        if ((taskUnion >> u) & 1ULL) res.criticalTasks.push_back(u);
    for (int id = 0; id < static_cast<int>(edges.size()); ++id)
        if ((edgeUnion >> id) & 1ULL) res.criticalDependencies.push_back(id);
    return res;
}

int main() {
    same(analyzeCriticalRollout({}, {}), {0, {}, {}});
    same(analyzeCriticalRollout({3, 2, 4, 5, 2},
        {{0, 2}, {1, 2}, {2, 3}, {2, 4}}),
        {12, {0, 2, 3}, {0, 2}});
    same(analyzeCriticalRollout({2, 2, 3, 3},
        {{0, 2}, {1, 3}}),
        {5, {0, 1, 2, 3}, {0, 1}});
    same(analyzeCriticalRollout({0, 0, 0, 0},
        {{0, 1}, {1, 2}, {0, 2}}),
        {0, {0, 1, 2, 3}, {0, 1, 2}});
    same(analyzeCriticalRollout({7, 1, 7}, {}),
        {7, {0, 2}, {}});
    same(analyzeCriticalRollout({3, 4},
        {{0, 1}, {0, 1}}),
        {7, {0, 1}, {0, 1}});

    std::mt19937 rng(18112028);
    for (int trial = 0; trial < 1900; ++trial) {
        const int n = 1 + static_cast<int>(rng() % 8);
        std::vector<int> dur(n);
        for (int& d : dur) d = static_cast<int>(rng() % 7);

        // Random permutation gives a topological order unrelated to task IDs.
        std::vector<int> perm(n);
        std::iota(perm.begin(), perm.end(), 0);
        std::shuffle(perm.begin(), perm.end(), rng);
        std::vector<Dependency> edges;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rng() % 4 == 0) edges.push_back({perm[i], perm[j]});
            }
        }
        std::shuffle(edges.begin(), edges.end(), rng);
        same(analyzeCriticalRollout(dur, edges), brute(dur, edges));
    }

    // Long chain + shortcuts: shortcuts cannot be on the longest task path,
    // because every duration is positive and a shortcut skips a task.
    const int n = 100000;
    std::vector<int> dur(n, 1);
    std::vector<Dependency> edges;
    edges.reserve(2 * n);
    for (int i = 0; i + 1 < n; ++i) edges.push_back({i, i + 1});
    for (int i = 0; i + 2 < n; ++i) edges.push_back({i, i + 2});
    const CriticalReport got = analyzeCriticalRollout(dur, edges);
    assert(got.finishTime == n);
    assert(got.criticalTasks.size() == static_cast<size_t>(n));
    assert(got.criticalDependencies.size() == static_cast<size_t>(n - 1));
    for (int i = 0; i < n; ++i) assert(got.criticalTasks[i] == i);
    for (int i = 0; i + 1 < n; ++i)
        assert(got.criticalDependencies[i] == i);

    std::cout << "hard: all tests passed\n";
}
