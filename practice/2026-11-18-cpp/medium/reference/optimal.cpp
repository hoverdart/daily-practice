#include <vector>

long long minimumCalibrationSpan(
    const std::vector<int>& sortedTimes, int maxGroups) {

    // A single timestamp per group always achieves span zero.
    long long low = 0;
    long long high = static_cast<long long>(sortedTimes.back())
                   - static_cast<long long>(sortedTimes.front());

    auto feasible = [&](long long span) {
        int groups = 1;
        int groupStart = sortedTimes.front();
        for (int i = 1; i < static_cast<int>(sortedTimes.size()); ++i) {
            if (static_cast<long long>(sortedTimes[i]) - groupStart > span) {
                ++groups;
                groupStart = sortedTimes[i];
                if (groups > maxGroups) return false;
            }
        }
        return true;
    };

    // Invariant: the optimal value lies in [low, high].
    while (low < high) {
        const long long mid = low + (high - low) / 2;
        if (feasible(mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}
