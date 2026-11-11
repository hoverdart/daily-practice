#include <algorithm>
#include <vector>

struct IdRange {
    int low;
    int high;
};

std::vector<int> archiveRangeCounts(
    const std::vector<int>& sortedIds,
    const std::vector<IdRange>& queries) {
    std::vector<int> answers;
    answers.reserve(queries.size());

    for (const IdRange& query : queries) {
        if (query.low > query.high) {
            answers.push_back(0);
            continue;
        }

        // lower_bound: first element >= low (inclusive left edge).
        const auto first = std::lower_bound(
            sortedIds.begin(), sortedIds.end(), query.low);

        // upper_bound: first element > high (exclusive right edge).
        const auto pastLast = std::upper_bound(
            sortedIds.begin(), sortedIds.end(), query.high);

        // The number of archived events is at most 200,000.
        answers.push_back(static_cast<int>(pastLast - first));
    }

    return answers;
}
