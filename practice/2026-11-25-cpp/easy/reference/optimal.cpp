#include <algorithm>
#include <array>
#include <vector>

std::vector<int> stableDispatch(const std::vector<int>& priorities) {
    std::array<int, 101> next{};
    for (int p : priorities) ++next[p];

    int offset = 0;
    for (int p = 100; p >= 0; --p) {
        const int count = next[p];
        next[p] = offset;
        offset += count;
    }

    std::vector<int> order(priorities.size());
    for (int i = 0; i < static_cast<int>(priorities.size()); ++i) {
        order[next[priorities[i]]++] = i;
    }
    return order;
}
