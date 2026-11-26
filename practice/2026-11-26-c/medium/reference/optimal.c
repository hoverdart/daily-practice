#include <stdlib.h>
long long repeated_windows(const int *ids, int n, int universe, int k) {
    if (!n) return 0;
    int *freq = calloc((size_t)universe, sizeof *freq);
    if (!freq) abort();
    int left=0, repeated=0;
    long long total=0;
    for(int right=0;right<n;++right) {
        if(++freq[ids[right]]==2) ++repeated;
        while(repeated>k) {
            if(--freq[ids[left++]]==1) --repeated;
        }
        total += (long long)(right-left+1);
    }
    free(freq);
    return total;
}
