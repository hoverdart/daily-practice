#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution.c"

static unsigned seed = 0xabc14723u;
static unsigned rnd(void) { seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5; return seed; }
static void slow(const char *in, char *out) {
    size_t r = 0, w = 0;
    while (in[r]) {
        char ch = in[r]; size_t count = 0;
        do { ++r; ++count; } while (in[r] == ch);
        out[w++] = ch;
        if (count > 1) w += (size_t)sprintf(out + w, "%zu", count);
    }
    out[w] = '\0';
}
static void check(const char *input) {
    size_t n = strlen(input);
    char *a = malloc(n + 1), *want = malloc(n + 1);
    assert(a && want);
    memcpy(a, input, n + 1);
    slow(input, want);
    size_t got = compress_command_runs(a);
    assert(got == strlen(want));
    assert(strcmp(a, want) == 0);
    assert(got <= n);
    free(a); free(want);
}
int main(void) {
    assert(compress_command_runs(NULL) == 0);
    check(""); check("a"); check("ab"); check("aa"); check("aaabbc");
    check("aaaaaaaaaaaa"); check("aabbbbbbbbbbbccccd"); check("aabbccddeeff");
    for (int t = 0; t < 10000; ++t) {
        char s[257]; int n = (int)(rnd() % 256u);
        for (int i = 0; i < n; ++i) s[i] = (char)('a' + rnd() % 5u);
        s[n] = '\0'; check(s);
    }
    char *large = malloc(200001); assert(large);
    memset(large, 'z', 200000); large[200000] = '\0';
    size_t len = compress_command_runs(large);
    assert(len == 7 && strcmp(large, "z200000") == 0);
    free(large);
    puts("easy: in-place run compression passed");
    return 0;
}
