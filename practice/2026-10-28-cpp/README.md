# Wednesday, October 28, 2026 — Adaptive C++17 Practice

Three original interview problems, increasing in difficulty:

| Level | Problem | Main concepts |
| --- | --- | --- |
| Easy | Kth Strongest Calibration Pulse | Fixed-size min-heap, streaming top-k, duplicate handling |
| Medium | Count Overloaded Signal Windows | Sliding window, hash-map frequencies, counting complement |
| Hard / Stretch | Budgeted Long-Cable Network | Union-find, minimum-spanning-tree intuition, binary search on answer |

## Why these today?

The last **completed** attempt logs (October 5) report **hash sets 5/5**, **sliding windows 2/5 with a hint**, and **shortest paths 1/5, unfinished**. October 21–27 logs are still unfilled; this is not evidence of mastery. We revisit the sliding-window frequency invariant in a *counting* problem after the October 21 longest-window problem, and use a graph optimization problem with union-find and a monotone feasibility predicate instead of another routine Dijkstra exercise. The easy problem rehearses C++ priority-queue syntax and CS61B heap invariants.

This follows `curriculum/cs61b.md`, `CONCEPTS.md`, `PROGRESS.md`, and the actual attempt logs. The hard problem also reinforces graph recognition, but today's focus is MST/connectivity rather than weighted shortest paths.

## Workflow

1. Read `easy/problem.md`, implement `easy/solution.cpp`, then run `python scripts/run_problem.py practice/2026-10-28-cpp/easy` from the repository root.
2. Repeat for `medium` and `hard`. Starter implementations intentionally fail substantive tests until you implement them.
3. Record `attempt.md` **before** opening `reference/`. Use `python scripts/check_reference.py practice/2026-10-28-cpp` to validate all reference solutions.

Each `reference/notes.md` contains recognition signals, brute-force vs. optimal reasoning, invariants, complexity, mistakes, and CS61B connections. Use C++17 and treat tests as the executable specification.

The one-time `review-guides/graphs-and-cpp-review.md` already exists, so it was not recreated.

