#include <unordered_map>
#include <vector>

long long countOverloadedWindows(const std::vector<int>& ids, long long k) {
    const long long n = static_cast<long long>(ids.size());
    const long long total = n * (n + 1) / 2;
    if (k == 0) return total;

    const long long budget = k - 1;
    std::unordered_map<int, int> freq;
    long long pairs = 0;
    long long atMost = 0;
    int left = 0;
    for (int right = 0; right < static_cast<int>(ids.size()); ++right) {
        int x = ids[right];
        int old = freq[x];
        pairs += old;
        freq[x] = old + 1;
        while (pairs > budget) {
            int y = ids[left++];
            auto it = freq.find(y);
            int previous = it->second;
            pairs -= previous - 1;
            if (--(it->second) == 0) freq.erase(it);
        }
        atMost += static_cast<long long>(right - left + 1);
    }
    return total - atMost;
}

