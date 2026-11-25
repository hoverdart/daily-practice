#include <algorithm>
#include <deque>
#include <vector>

int longestFreeSpan(const std::vector<int>& costs, long long budget) {
    std::deque<int> maxima;
    long long sum = 0;
    int left = 0, best = 0;
    for (int right = 0; right < static_cast<int>(costs.size()); ++right) {
        sum += costs[right];
        while (!maxima.empty() && costs[maxima.back()] <= costs[right])
            maxima.pop_back();
        maxima.push_back(right);

        while (sum - costs[maxima.front()] > budget) {
            if (maxima.front() == left) maxima.pop_front();
            sum -= costs[left++];
        }
        best = std::max(best, right-left+1);
    }
    return best;
}
