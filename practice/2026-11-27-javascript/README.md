# Friday, November 27, 2026 — JavaScript interview practice

| Level | Exercise | Target | Time |
|---|---|---|---|
| Easy | Calibration Neighbors in a Search Tree | BST bounds, tree height, iterative search | 15–25 min |
| Medium | Shortest Archive Cut | Complement sliding window, frequency threshold, Map | 25–40 min |
| Hard/stretch | Cheapest Transfer with Refund Loops | Bellman–Ford, negative cycles, reverse BFS | 40–65 min |

## Adaptive rationale
Reviewed curriculum/cs61b.md, CONCEPTS.md, PROGRESS.md, nine November 24–26 attempt logs, and the three completed October 5 logs on the November 26 parent. PROGRESS is blank; the nine recent attempts are unfilled, not evidence of success. The October 5 records show hashing 5/5 independently, sliding windows 2/5 with a hint (frequency-map purpose and shrinking), and shortest paths 1/5 unfinished (algorithm recognition and API recall). Easy returns to the underrepresented BST topic after yesterday's array bounds; medium reinforces the same frequency transitions in a complement/minimum-length window instead of a repeated-ID counting problem; hard deliberately changes from the recent Dijkstra variants to recognizing negative weights and relevant negative cycles. JavaScript focus: Map, null vs zero, adjacency arrays, iterative queue traversal, and Number precision.

## Run
From the repository root, run `python scripts/run_problem.py practice/2026-11-27-javascript/easy` (repeat for medium/hard), or in each problem folder `node tests.js`. Starters intentionally throw until implemented. Check reference solutions without changing starters: `python scripts/check_reference.py practice/2026-11-27-javascript`.

Read the problem, write a brute force and an invariant, implement, run tests, then complete attempt.md before opening reference/. Tests include fixed cases, seeded independent oracles, and stress inputs.

The existing review-guides/graphs-and-cpp-review.md has the same blob on main and the inherited branch and is intentionally not recreated.
