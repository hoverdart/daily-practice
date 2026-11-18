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

    // TODO: Kahn topological order; longest path ending at every task;
    // longest path starting at every task, processed in reverse order.
    // Then classify task and input edge membership on SOME longest path.
    // Use 64-bit sums and iterative traversal (n can be 100,000).
    (void)duration;
    (void)dependencies;
    return {0, {}, {}};
}
