#include <array>
#include <string>
#include <vector>

std::vector<int> wildcardSignatureMatches(const std::string& stream,
                                          const std::string& signature) {
    const int n = static_cast<int>(stream.size());
    const int m = static_cast<int>(signature.size());
    std::vector<int> result;
    if (m > n) return result;

    // deficit[c] = required instances of c minus instances in current window.
    std::array<int, 26> deficit{};
    int missing = 0;
    for (char c : signature) {
        if (c != '?') {
            ++deficit[c - 'A'];
            ++missing;
        }
    }
    for (int right = 0; right < n; ++right) {
        int entering = stream[right] - 'A';
        if (deficit[entering] > 0) --missing;
        --deficit[entering];

        // Keep exactly the latest m characters before evaluating.
        if (right >= m) {
            int leaving = stream[right - m] - 'A';
            ++deficit[leaving];
            if (deficit[leaving] > 0) ++missing;
        }
        if (right + 1 >= m && missing == 0) result.push_back(right - m + 1);
    }
    return result;
}
