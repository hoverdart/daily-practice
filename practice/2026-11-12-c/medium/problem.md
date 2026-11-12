# Medium — Longest Drift-Controlled Span

A telemetry array records signed integer sensor readings. For a contiguous span [l..r], define its **drift cost** as the sum of absolute changes between *adjacent* readings **inside that span**:

~~~text
drift(l,r) = |a[l+1]-a[l]| + |a[l+2]-a[l+1]| + ... + |a[r]-a[r-1]|
drift(l,l) = 0
~~~

Find the **longest nonempty contiguous span** whose drift cost is at most budget. If several spans share maximum length, return the one with the **smallest start index**.

Implement in solution.c:

~~~c
typedef struct { int start, length; } DriftSpan;
DriftSpan longest_drift_span(const int *readings, int n, long long budget);
~~~

For n=0, return {0,0}. NULL is permitted only for n=0.

## Examples

- readings = [4,8,7,15,13], budget=5 -> {start:0,length:3}. The span [4,8,7] costs 4+1=5.
- readings = [6,6,6,6], budget=0 -> {start:0,length:4}.
- readings = [INT_MIN,INT_MAX,INT_MIN], budget=4294967295 -> {start:0,length:2}; each edge costs 4294967295.
- readings = [4,3,2,1], budget=2 -> {start:0,length:3} (tie broken to earliest).

## Constraints

- 0 <= n <= 200,000.
- Readings are arbitrary signed 32-bit integers.
- 0 <= budget <= LLONG_MAX.
- Return O(n) time and **O(1) auxiliary space**.
- The individual difference must not be computed as a signed int; 32-bit subtraction can overflow.

## Interview questions

1. Why is this a window over *vertices/readings* but a sum over *edges/adjacent changes*?
2. What exactly should be added when the right index grows?
3. What exactly should be removed when the left index grows?
4. Why can a left pointer move only forward as right advances?
5. How do you implement earliest-start tie breaking?

