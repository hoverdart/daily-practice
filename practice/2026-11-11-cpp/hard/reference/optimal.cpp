#include <algorithm>
#include <utility>
#include <vector>

struct AncestorRequest {
    char type;
    int x;
    int y;
};

std::vector<int> rerootedLcaQueries(
    int n,
    const std::vector<std::pair<int, int>>& edges,
    const std::vector<AncestorRequest>& requests) {

    std::vector<std::vector<int>> adj(n);
    for (const auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    // Iterative tree traversal. Depth -1 denotes an unvisited vertex.
    std::vector<int> depth(n, -1);
    std::vector<int> parent(n, 0);
    std::vector<int> order;
    order.reserve(n);
    order.push_back(0);
    depth[0] = 0;
    parent[0] = 0; // root is its own ancestor

    for (std::size_t head = 0; head < order.size(); ++head) {
        const int u = order[head];
        for (int v : adj[u]) {
            if (depth[v] != -1) continue;
            depth[v] = depth[u] + 1;
            parent[v] = u;
            order.push_back(v);
        }
    }

    int levels = 1;
    while ((1LL << levels) <= n) ++levels;
    std::vector<std::vector<int>> up(levels, std::vector<int>(n));
    up[0] = parent;

    // up[bit][v] is the ancestor 2^bit steps above v.
    for (int bit = 1; bit < levels; ++bit) {
        for (int v = 0; v < n; ++v) {
            up[bit][v] = up[bit - 1][up[bit - 1][v]];
        }
    }

    // Ordinary LCA in the tree rooted permanently at vertex 0.
    const auto lcaAtZero = [&](int a, int b) {
        if (depth[a] < depth[b]) std::swap(a, b);
        int gap = depth[a] - depth[b];
        for (int bit = 0; gap > 0; ++bit, gap >>= 1) {
            if ((gap & 1) != 0) a = up[bit][a];
        }

        if (a == b) return a;
        for (int bit = levels - 1; bit >= 0; --bit) {
            if (up[bit][a] != up[bit][b]) {
                a = up[bit][a];
                b = up[bit][b];
            }
        }
        return up[0][a];
    };

    int root = 0;
    std::vector<int> answers;
    answers.reserve(requests.size());
    for (const auto& request : requests) {
        if (request.type == 'R') {
            root = request.x;
            continue;
        }

        const int uv = lcaAtZero(request.x, request.y);
        const int ur = lcaAtZero(request.x, root);
        const int vr = lcaAtZero(request.y, root);

        int answer = uv;
        if (depth[ur] > depth[answer]) answer = ur;
        if (depth[vr] > depth[answer]) answer = vr;
        answers.push_back(answer);
    }
    return answers;
}
