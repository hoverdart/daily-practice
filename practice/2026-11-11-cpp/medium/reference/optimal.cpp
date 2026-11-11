#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <utility>
#include <vector>

// Every ordered pair of uint32_t occupies a unique uint64_t value.
// Sort SIGNED station IDs first, then store their 32-bit bit patterns.
static std::uint64_t encodeHandoff(int first, int second) {
    const int lo = std::min(first, second);
    const int hi = std::max(first, second);
    return (static_cast<std::uint64_t>(static_cast<std::uint32_t>(lo)) << 32)
         | static_cast<std::uint32_t>(hi);
}

std::pair<int, int> longestHandoffTrace(
    const std::vector<int>& stations, int maxRepeats) {
    const int n = static_cast<int>(stations.size());
    if (n == 0) return {0, 0};

    std::unordered_map<std::uint64_t, int> freq;
    freq.reserve(static_cast<std::size_t>(n));

    int left = 0;
    int repeats = 0;
    std::pair<int, int> best{0, 0};

    // Window of visits: [left, right] inclusive.
    for (int right = 0; right < n; ++right) {
        // Expanding adds precisely one handoff, unless this is the first visit.
        if (right > 0) {
            const auto key = encodeHandoff(stations[right - 1], stations[right]);
            int& count = freq[key];
            if (count >= 1) ++repeats; // another copy beyond the first
            ++count;
        }

        while (repeats > maxRepeats) {
            // Moving left one visit discards handoff (left, left+1).
            const auto key = encodeHandoff(stations[left], stations[left + 1]);
            auto it = freq.find(key);
            if (it->second > 1) --repeats;
            if (--(it->second) == 0) freq.erase(it);
            ++left;
        }

        const int length = right - left + 1;
        if (length > best.second) {
            best = {left, length}; // strict > preserves earliest equal-length start
        }
    }
    return best;
}
