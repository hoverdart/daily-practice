#include <utility>
#include <vector>

struct AncestorRequest {
    char type; // 'R' changes the current root; 'Q' queries an LCA.
    int x;
    int y;
};

std::vector<int> rerootedLcaQueries(
    int n,
    const std::vector<std::pair<int, int>>& edges,
    const std::vector<AncestorRequest>& requests) {

    // TODO:
    // 1. Build an undirected adjacency list.
    // 2. Iteratively BFS/DFS from fixed root 0 to get depth and parent.
    // 3. Build binary-lifting ancestors up[bit][vertex].
    // 4. Write LCA_0(u, v) using lifting in O(log n).
    // 5. For each Q under active root r, find the deepest among:
    //       LCA_0(u,v), LCA_0(u,r), LCA_0(v,r).
    (void)n;
    (void)edges;
    (void)requests;
    return {};
}
