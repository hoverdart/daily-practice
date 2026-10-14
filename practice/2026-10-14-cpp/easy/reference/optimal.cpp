#include <vector>
#include <algorithm>
int longestRepairableRun(const std::vector<int>& status, int k) {
    int left = 0, faults = 0, best = 0;
    for (int right = 0; right < static_cast<int>(status.size()); ++right) {
        if (status[right] == 0) ++faults;
        while (faults > k) {
            if (status[left] == 0) --faults;
            ++left;
        }
        best = std::max(best, right - left + 1);
    }
    return best;
}
