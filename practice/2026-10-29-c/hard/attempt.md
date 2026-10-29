# Attempt — Maximum Reward with Setup Cooldown

Complete before opening `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognition and baseline
- Why is this weighted interval scheduling rather than greedy earliest-finish?
- What does exhaustive include/exclude recursion cost?

## DP invariant
- What does `dp[i]` mean after sorting jobs by end time?
- How do you find the count of compatible earlier jobs via binary search?
- Write the skip/take recurrence.
- Why does using `start - cooldown` avoid 32-bit overflow?
- What if jobs have equal end times, zero rewards, or huge cooldown?

## C / complexity
- Why must `qsort` comparators avoid subtraction?
- Time / auxiliary space; malloc/calloc/free handling:
- Failed cases / hints / binary-search off-by-one friction:
- One CS61B sorting/binary-search connection and one DP lesson:
