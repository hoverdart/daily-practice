#include <vector>

long long minimumCalibrationSpan(
    const std::vector<int>& sortedTimes, int maxGroups) {

    // TODO: Binary-search the minimum feasible max span.
    // Feasibility: greedy left-to-right grouping with each group's first time.
    // Differences of extreme signed 32-bit times require 64-bit arithmetic.
    (void)sortedTimes;
    (void)maxGroups;
    return -1;
}
