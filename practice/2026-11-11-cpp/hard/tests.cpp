#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include "solution.cpp"

static std::vector<int> independentOracle(
    int n, const std::vector<std::pair<int, int>>& edges,
    const std::vector<AncestorRequest>& requests) {
    std::vector<std::vector<int>> adj(n);
    for (const auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    int root = 0;
    std::vector<int> result;
    for (const auto& request : requests) {
        if (request.type == 'R') {
            root = request.x;
            continue;
        }

        // Independent, deliberately slow oracle: rebuild parent array
        // for THIS root, then walk ancestor chains without lifting.
        std::vector<int> parent(n, -1);
        std::vector<int> queue{root};
        parent[root] = root;
        for (size_t head = 0; head < queue.size(); ++head) {
            const int u = queue[head];
            for (int v : adj[u]) {
                if (parent[v] == -1) {
                    parent[v] = u;
                    queue.push_back(v);
                }
            }
        }

        std::vector<char> ancestor(n, false);
        int u = request.x;
        while (true) {
            ancestor[u] = true;
            if (u == parent[u]) break;
            u = parent[u];
        }
        int v = request.y;
        while (!ancestor[v]) v = parent[v];
        result.push_back(v);
    }
    return result;
}

int main() {
    assert((rerootedLcaQueries(1, {}, {
        {'Q', 0, 0}, {'R', 0, 0}, {'Q', 0, 0}
    }) == std::vector<int>{0, 0}));

    const std::vector<std::pair<int, int>> chain{
        {0, 1}, {1, 2}, {2, 3}, {3, 4}
    };
    assert((rerootedLcaQueries(5, chain, {
        {'Q', 1, 4}, {'R', 4, 0}, {'Q', 1, 4}, {'Q', 1, 3},
        {'R', 2, 0}, {'Q', 0, 4}, {'Q', 2, 2},
        {'R', 0, 0}, {'Q', 0, 4}
    }) == std::vector<int>{1, 4, 3, 2, 2, 0}));

    const std::vector<std::pair<int, int>> star{
        {0, 1}, {0, 2}, {0, 3}
    };
    assert((rerootedLcaQueries(4, star, {
        {'R', 1, 0}, {'Q', 2, 3}, {'Q', 1, 3}, {'Q', 0, 1},
        {'R', 3, 0}, {'Q', 2, 1}
    }) == std::vector<int>{0, 1, 1, 0}));
    assert(rerootedLcaQueries(2, {{0, 1}}, {{'R', 1, 0}}).empty());

    std::mt19937 rng(11112028);
    for (int trial = 0; trial < 1700; ++trial) {
        const int n = 1 + static_cast<int>(rng() % 14);
        std::vector<std::pair<int, int>> edges;
        for (int v = 1; v < n; ++v) {
            edges.push_back({v, static_cast<int>(rng() % v)});
        }
        const int count = 1 + static_cast<int>(rng() % 90);
        std::vector<AncestorRequest> requests;
        for (int i = 0; i < count; ++i) {
            if (rng() % 3 == 0) {
                requests.push_back({'R', static_cast<int>(rng() % n), 0});
            } else {
                requests.push_back({'Q',
                    static_cast<int>(rng() % n),
                    static_cast<int>(rng() % n)});
            }
        }
        assert(rerootedLcaQueries(n, edges, requests)
               == independentOracle(n, edges, requests));
    }

    // Chain stress: with endpoints 0 and n-1, their LCA under root r is r.
    constexpr int n = 200000;
    std::vector<std::pair<int, int>> longChain;
    longChain.reserve(n - 1);
    for (int v = 1; v < n; ++v) longChain.push_back({v - 1, v});

    std::vector<AncestorRequest> requests;
    requests.reserve(n);
    for (int i = 0; i < n / 2; ++i) {
        requests.push_back({'R', (i * 17) % n, 0});
        requests.push_back({'Q', 0, n - 1});
    }
    const auto result = rerootedLcaQueries(n, longChain, requests);
    assert(result.size() == static_cast<size_t>(n / 2));
    for (int i = 0; i < n / 2; ++i) {
        assert(result[i] == (i * 17) % n);
    }
    std::cout << "hard: all tests passed\n";
}
