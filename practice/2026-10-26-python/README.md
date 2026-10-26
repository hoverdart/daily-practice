# Monday, October 26, 2026 — Adaptive Python Practice

Three original Python 3 interview problems (standard library only). Suggested pacing: easy 15–20 minutes, medium 25–35 minutes, hard/stretch 45–60 minutes.

| Level | Problem | Main skill |
| --- | --- | --- |
| Easy | First Sufficient Cache Slot | Manual lower-bound binary search, duplicates, boundary invariants |
| Medium | Longest Affordable Channel Window | Sliding window with **two** simultaneous monotone constraints |
| Hard | Safest Maintenance Route | Multi-source BFS + maximum-bottleneck (widest-path) heap search |

## Why these three?

The latest completed attempts in this repository (October 5) report **5/5** for basic hash-set lookup, **2/5** for sliding-window frequency tracking (hint needed), and **1/5** for weighted shortest-path reasoning (unfinished). Recent October 19–23 attempts are still blank, **not evidence of mastery**; PROGRESS.md has no scored topic entries. The selection follows curriculum/cs61b.md and CONCEPTS.md:

- **Easy:** revisit binary search from the CS61B cost-model/ordered-search curriculum rather than repeating set membership. Practice the exact `[lo,hi)` invariant and duplicate handling.
- **Medium:** revisit the documented weak sliding-window invariant, including the Python `dict.get` / `del` operations, but combine **distinct channel count** with a **nonnegative budget**; neither constraint can be ignored.
- **Hard:** transfer graph/heap skills into a different objective from ordinary Dijkstra: first BFS from **all** hazards, then maximize the minimum safety score along a path. It uses graph traversal and priority-queue invariants without another coupon/second-shortest-path variant.

The existing one-time `review-guides/graphs-and-cpp-review.md` was checked and is **not** recreated.

## Work sequence

1. Read each `problem.md` and edit its `solution.py`. Do not read `reference/` yet.
2. State your brute-force idea and the loop invariant aloud before coding.
3. From the repository root, run:
   ~~~bash
   python scripts/run_problem.py practice/2026-10-26-python/easy
   python scripts/run_problem.py practice/2026-10-26-python/medium
   python scripts/run_problem.py practice/2026-10-26-python/hard
   ~~~
4. Complete each `attempt.md`, including time, hints, confidence, failed cases, and claimed complexity.
5. Only then inspect `reference/notes.md` and `reference/optimal.py`.
6. Check untouched references: `python scripts/check_reference.py practice/2026-10-26-python`.

Starters deliberately raise `NotImplementedError`; tests are expected to fail until you implement them. Reference tests include seeded independent oracles and large cases.
