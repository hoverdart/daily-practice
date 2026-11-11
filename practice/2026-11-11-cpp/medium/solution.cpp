#include <utility>
#include <vector>

// Returns {earliest start, maximum number of visits}.
std::pair<int, int> longestHandoffTrace(
    const std::vector<int>& stations, int maxRepeats) {

    // TODO: Track frequencies of unordered pairs of consecutive stations.
    // Use a collision-free 64-bit packing of two signed 32-bit IDs,
    // or a hash map with a proper pair hash.
    //
    // Maintain the number of occurrences BEYOND the first per handoff type.
    // The window over visits [left, right] has edges [left, right-1].
    (void)stations;
    (void)maxRepeats;
    return {0, 0};
}
