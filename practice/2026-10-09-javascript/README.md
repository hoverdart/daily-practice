# Friday, October 9, 2026 — JavaScript (Node.js)

Exactly three original interview problems. Work on solution.js and attempt.md before opening reference/.

| Level | Problem | Main pattern | Suggested time |
| --- | --- | --- | --- |
| Easy | First Saturated Checkpoint | Lower-bound binary search, duplicate boundaries | 15–20 min |
| Medium | Longest Compatible Batch | Frequency-map sliding window, earliest tie | 25–40 min |
| Hard | Hop-Limited Resilient Route | Binary search on answer + BFS hop feasibility | 45–70 min |

## Adaptive selection

The only completed attempt logs are from October 5: hash/set lookup 5/5 independent; sliding-window frequency accounting 2/5 with hints; shortest-path work 1/5 and unfinished. October 6–8 logs remain blank, so those concepts are not treated as mastered.

Easy covers a previously unassessed CS61B binary-search skill. Medium repeats the weak frequency-map invariant in JavaScript. Hard revisits graph traversal with BFS and a monotone threshold predicate instead of repeating another Dijkstra-state-expansion problem.

## Run

From repository root:

    python scripts/run_problem.py practice/2026-10-09-javascript/easy
    python scripts/run_problem.py practice/2026-10-09-javascript/medium
    python scripts/run_problem.py practice/2026-10-09-javascript/hard

Starter solutions intentionally fail. Tests include deterministic edge cases and seeded independent brute-force comparisons.

Verify reference implementations without touching your starters:

    python scripts/check_reference.py practice/2026-10-09-javascript

Node.js 18+; no npm dependencies. Complete each attempt.md before reading reference/.

The one-time review-guides/graphs-and-cpp-review.md already exists and is intentionally unchanged.
