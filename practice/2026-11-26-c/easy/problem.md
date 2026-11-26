# Audit Range Counts (Easy)

An audit log stores sorted integer readings (duplicates allowed). For each inclusive query `[lo, hi]`, report the number of readings in that interval. If `lo > hi`, report zero. Do not modify the inputs. Output counts in query order, including duplicate queries.

Implement `void audit_counts(const int *a, int n, const int *lo, const int *hi, int q, int *out)`. The caller provides `out` of length q, disjoint from inputs. Arrays are valid for their lengths; NULL is allowed for zero length. `0 <= n,q <= 200000`; values and endpoints can be any int. Aim for O(q log(n+1) + q) time and O(1) extra space.

Example: `a=[-3,2,2,8]`, `lo=[2,0,9,8]`, `hi=[2,8,1,8]` gives `[2,3,0,1]`. Empty readings give zero for every query. Do not compute `hi+1` (it may overflow).
