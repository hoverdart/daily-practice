#include <assert.h>
#include <stdio.h>
#include "solution.c"

static unsigned state = 0xabcdef12u;
static unsigned next_rand(void) {
    state ^= state << 13; state ^= state >> 17; state ^= state << 5;
    return state;
}
static int brute(const int *a, int n, int k) {
    int best = 0;
    for (int left = 0; left < n; ++left) {
        int count[256] = {0}, distinct = 0;
        for (int right = left; right < n; ++right) {
            if (count[a[right]]++ == 0) ++distinct;
            if (distinct <= k && right - left + 1 > best)
                best = right - left + 1;
        }
    }
    return best;
}
static void check(const int *a, int n, int k) {
    assert(longest_channel_window(a, n, k) == brute(a, n, k));
}
int main(void) {
    int a[] = {1,2,1,3,3,2,2};
    check(a, 7, 2); assert(longest_channel_window(a, 7, 2) == 4);
    check(a, 7, 0); check(a, 7, 256);
    int b[] = {255,255,255,255}; check(b, 4, 1);
    int empty[] = {0}; check(empty, 0, 0);
    for (int t = 0; t < 2200; ++t) {
        int n = (int)(next_rand() % 45), data[64];
        int k = (int)(next_rand() % 9);
        for (int i = 0; i < n; ++i) data[i] = (int)(next_rand() % 8);
        check(data, n, k);
    }
    int big[100000];
    for (int i = 0; i < 100000; ++i) big[i] = i % 2 ? 255 : 0;
    assert(longest_channel_window(big, 100000, 2) == 100000);
    assert(longest_channel_window(big, 100000, 1) == 1);
    puts("medium: bounded distinct-window passed");
    return 0;
}
