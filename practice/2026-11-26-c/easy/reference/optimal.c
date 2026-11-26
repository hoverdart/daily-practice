static int boundary(const int *a, int n, int x, int strict) {
    int l = 0, r = n;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] < x || (strict && a[m] == x)) l = m + 1;
        else r = m;
    }
    return l;
}
void audit_counts(const int *a, int n, const int *lo, const int *hi, int q, int *out) {
    for (int i = 0; i < q; ++i)
        out[i] = lo[i] > hi[i] ? 0 : boundary(a,n,hi[i],1) - boundary(a,n,lo[i],0);
}
