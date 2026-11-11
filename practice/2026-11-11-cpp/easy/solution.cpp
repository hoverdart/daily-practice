#include <vector>

struct IdRange {
    int low;
    int high;
};

std::vector<int> archiveRangeCounts(
    const std::vector<int>& sortedIds,
    const std::vector<IdRange>& queries) {

    // TODO: Binary-search the first ID >= low and first ID > high.
    // A reversed query contributes zero. Preserve all duplicates.
    (void)sortedIds;
    (void)queries;
    return {};
}
