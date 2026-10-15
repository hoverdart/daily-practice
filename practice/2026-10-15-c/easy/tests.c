#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "solution.c"

static unsigned state = 0x91abcdeu;
static unsigned next_rand(void) {
    state ^= state << 13; state ^= state >> 17; state ^= state << 5;
    return state;
}
static int cmp_int(const void *pa, const void *pb) {
    int a = *(const int *)pa, b = *(const int *)pb;
    return (a > b) - (a < b);
}
static void check(int *a, int n) {
    int original[128];
    for (int i = 0; i < n; ++i) original[i] = a[i];
    int expected[128], count = 0;
    for (int i = 0; i < n; ++i)
        if (i == 0 || original[i] != original[i - 1])
            expected[count++] = original[i];
    int got = compact_sorted_ids(a, n);
    assert(got == count);
    for (int i = 0; i < count; ++i) assert(a[i] == expected[i]);
}
int main(void) {
    int empty[1] = {0}; check(empty, 0);
    int single[] = {-7}; check(single, 1);
    int all_same[] = {4,4,4,4,4}; check(all_same, 5);
    int mixed[] = {-9,-9,-2,0,0,0,7,9,9}; check(mixed, 9);
    int unique[] = {-3,-1,0,4,8}; check(unique, 5);
    for (int t = 0; t < 3000; ++t) {
        int n = (int)(next_rand() % 100), a[128];
        for (int i = 0; i < n; ++i) a[i] = (int)(next_rand() % 25) - 12;
        qsort(a, (size_t)n, sizeof(a[0]), cmp_int);
        check(a, n);
    }
    puts("easy: sorted ID compaction passed");
    return 0;
}
