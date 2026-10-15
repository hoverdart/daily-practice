#include <stddef.h>

int longest_channel_window(const int *events, int n, int k) {
    int freq[256] = {0};
    int left = 0, distinct = 0, best = 0;
    for (int right = 0; right < n; ++right) {
        int code = events[right];
        if (freq[code]++ == 0) ++distinct;
        while (distinct > k) {
            int old = events[left++];
            if (--freq[old] == 0) --distinct;
        }
        int length = right - left + 1;
        if (length > best) best = length;
    }
    return best;
}
