#include <algorithm>
#include <array>
#include <queue>
#include <utility>
#include <vector>

long long latestDispatch(
    const std::vector<long long>& deadline,
    const std::vector<std::array<int,3>>& links,
    int s, int t) {
    const int n = static_cast<int>(deadline.size());
    std::vector<std::vector<std::pair<int,int>>> incoming(n);
    for (const auto& e : links)
        incoming[e[1]].emplace_back(e[0], e[2]);

    std::vector<long long> latest(n, -1);
    std::priority_queue<std::pair<long long,int>> pq;
    latest[t] = deadline[t];
    pq.emplace(latest[t], t);

    while (!pq.empty()) {
        const auto [time, v] = pq.top();
        pq.pop();
        if (time != latest[v]) continue;
        if (v == s) return time;
        for (const auto& [u,w] : incoming[v]) {
            const long long candidate = std::min(deadline[u], time - w);
            if (candidate >= 0 && candidate > latest[u]) {
                latest[u] = candidate;
                pq.emplace(candidate,u);
            }
        }
    }
    return -1;
}
