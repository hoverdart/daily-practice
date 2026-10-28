#include <functional>
#include <queue>
#include <vector>

int kthLargestPulse(const std::vector<int>& pulses, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> smallestOfTopK;
    for (int value : pulses) {
        if (static_cast<int>(smallestOfTopK.size()) < k) {
            smallestOfTopK.push(value);
        } else if (value > smallestOfTopK.top()) {
            smallestOfTopK.pop();
            smallestOfTopK.push(value);
        }
    }
    return smallestOfTopK.top();
}

