# Attempt — Minimum Calibration Group Span

Complete before opening reference/.

- Start / finish / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):
- Brute-force algorithm and complexity:
- Optimal time / auxiliary space:
- First failed test or C++ syntax issue:
- One concept to revisit in 2–4 days:

## Recognition and reasoning

- Which words indicate *minimize the maximum*, and why could binary search target a numeric answer rather than an index?
- What precisely does feasible(X) mean? Why is it monotone?
- For fixed X, explain why keeping the current group open until the next timestamp exceeds X uses the fewest groups.
- Why is at most k sufficient even though every timestamp must be assigned?
- Write the low/high inclusive search invariant. Why do we use high=mid on success and low=mid+1 on failure?
- Does k >= n always allow span 0, even with negative timestamps and duplicates?
- What happens if you subtract two int values before promoting the result to long long?

## CS61B and interview pattern transfer

- Compare ordinary binary search in an array with binary search on a monotonic feasibility predicate.
- Explain why the left-to-right greedy scan is O(n), and why no nested quadratic search is hidden in the binary search.
- Compare this greedy invariant with sliding-window invariants: which constraint is checked and when does the segment boundary advance?
