# Medium — Minimum Audit Window

A factory event log is an array of integer event codes from 0 through 255. An auditor gives a list of required event codes. Find the **shortest contiguous window** containing *every distinct required code at least once*. If several windows share the minimum length, return the **earliest starting index**.

Implement:

    int shortestAuditWindow(const int *events, int n,
                            const int *required, int required_count,
                            int *start_out);

Return the minimum length and write its start index to `*start_out`. Return **-1** and write **-1** if no window covers all required codes. If `required_count == 0`, return length **0** and start **0**. Duplicate codes in `required` count only once. `events` may be NULL when `n == 0`, and `required` may be NULL when `required_count == 0`.

## Examples

- `events=[9,2,9,4,2,7,4]`, `required=[2,4,7]` -> **length 3, start 3** (window `[4,2,7]`).
- `events=[2,4,7,2,4,7]`, `required=[2,4,7]` -> **length 3, start 0** (tie).
- `events=[9,2,9,4,2,7,4]`, `required=[2,2,7]` -> **length 2, start 4**.
- `events=[1,2]`, `required=[7]` -> **-1, start -1**.

## Constraints and target

`0 <= n <= 200000`, `0 <= required_count <= 256`, every code in `[0,255]`. Aim for **O(n + required_count + 256)** time and **O(256)** auxiliary space. No hash-map library is necessary: the alphabet is small.

**Hint-free recognition question:** in a longest-at-most-K window, you shrink when *invalid*. In this minimum-covering window, when should you shrink?

**CS61B connection:** arrays as direct-address frequency maps, amortized two-pointer scans, invariants, and careful index bounds.
