#include <stddef.h>

typedef struct { int start; int length; } Window;

Window shortest_k_types(const unsigned char *events, int n, int k) {
    if (k == 0) return (Window){0, 0};
    Window best = {-1, 0};
    if (!events || n <= 0 || k < 0 || k > 256) return best;
    int count[256] = {0};
    int distinct = 0, left = 0;
    for (int right = 0; right < n; ++right) {
        if (count[events[right]]++ == 0) ++distinct;
        while (distinct >= k) {
            int len = right - left + 1;
            if (best.start == -1 || len < best.length)
                best = (Window){left, len};
            if (--count[events[left]] == 0) --distinct;
            ++left;
        }
    }
    return best;
}
