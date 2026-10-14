#include <vector>
#include <utility>
std::pair<long long,int> criticalAssemblyChains(
    int n,
    const std::vector<int>& duration,
    const std::vector<std::pair<int,int>>& prerequisites) {
    // TODO: Kahn topological ordering + longest-path DP + number of ties.
    // If fewer than n tasks can be processed, return {-1,0}.
    (void)n; (void)duration; (void)prerequisites;
    return {-1,0};
}
