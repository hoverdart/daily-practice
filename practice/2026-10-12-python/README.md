# Monday, October 12, 2026 — Adaptive Python Practice

**Three original problems, in order:** easy (~15–20 min), medium (~25–40 min), hard/stretch (~45–65 min). Python 3.12; standard library only.

| Difficulty | Problem | Main idea |
| --- | --- | --- |
| Easy | First Unique Alert Stream | Hash counts + FIFO deque; amortized queue operations |
| Medium | Exactly K Event Types | Sliding window; count at-most-K and subtract |
| Hard | Timetabled Relay Network | Dijkstra with waiting times and time-dependent edge relaxation |

## Why these?

The latest *completed* logs are from October 5: set lookup 5/5, sliding window 2/5 (hint needed; confusion about the frequency dictionary), and Dijkstra 1/5 (unfinished; heap API/relaxation recall). October 6–9 attempt logs are unfilled; **do not assume mastery**. The easy problem extends known hashing to a deque, medium revisits the exact sliding-window weakness with a counting objective, and hard revisits Dijkstra without another coupon/risk-budget state expansion. This week's hard instead tests whether a time-dependent edge still permits Dijkstra.

This selection follows `curriculum/cs61b.md`, `CONCEPTS.md`, `PROGRESS.md`, and the actual attempt logs. The long-term confidence table is still blank; today's outcomes should be recorded in each `attempt.md`.

## How to practice

1. Read `problem.md`; state a brute-force approach, then an invariant and expected complexity.
2. Edit only `solution.py`. Run `python scripts/run_problem.py practice/2026-10-12-python/easy` from the repository root; replace `easy` with `medium` or `hard`.
3. Record time, hints, bugs, and confidence in each `attempt.md` **before** opening `reference/`.
4. Afterward compare with the reference notes. To check the untouched reference implementations, run `python scripts/check_reference.py practice/2026-10-12-python`.

The tests include deterministic edge cases, reproducible randomized comparisons against independent slow oracles, and a larger input. Starters intentionally raise `NotImplementedError` until you implement them.

The one-time graph/C++ packet already exists at `review-guides/graphs-and-cpp-review.md`; it was not duplicated.
