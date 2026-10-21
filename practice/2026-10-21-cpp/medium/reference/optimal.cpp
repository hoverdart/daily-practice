#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

std::pair<int,int> longestLowCollisionWindow(
    const std::vector<int>& ids, long long k) {
    std::unordered_map<int,int> freq;
    int left = 0;
    long long pairs = 0;
    std::pair<int,int> best{0,0};
    for (int right = 0; right < static_cast<int>(ids.size()); ++right) {
        int x = ids[right];
        pairs += freq[x];  // f existing occurrences form f new pairs
        ++freq[x];
        while (pairs > k) {
            int y = ids[left++];
            auto it = freq.find(y);
            --it->second;
            pairs -= it->second; // old f -> f-1 removes f-1 pairs
            if (it->second == 0) freq.erase(it);
        }
        if (right+1-left > best.second-best.first)
            best = {left,right+1};
    }
    return best;
}
