# Thursday, November 26, 2026 — C interview practice

| Level | Exercise | Target | Time |
|---|---|---|---|
| Easy | Audit Range Counts | Binary search, sorted arrays | 15–25 min |
| Medium | Repeated-ID Window Census | Sliding window, frequency thresholds, 64-bit counting | 25–40 min |
| Hard/stretch | Cheapest Dispatch, Fewest Hops | Lexicographic Dijkstra, binary heaps, path counting | 40–65 min |

## Adaptive rationale

Reviewed `curriculum/cs61b.md`, `CONCEPTS.md`, `PROGRESS.md`, the October 5 completed logs, and all nine November 23–25 attempt logs on the November 25 branch. PROGRESS has no confidence entries; the nine recent logs are blank. October 5 reports hashing 5/5 independently, sliding windows 2/5 with a hint (frequency bookkeeping and shrinking), and shortest paths 1/5 unfinished. Do not infer mastery from generated exercises. Easy revisits binary search; medium revisits the exact frequency transitions that caused difficulty, with a counting objective; hard returns to a forward Dijkstra invariant with a tie-break and path multiplicity instead of yesterday's reverse deadlines. C practice emphasizes bounds, allocation ownership, and integer widths.

## Run

From repository root, `python scripts/run_problem.py practice/2026-11-26-c/easy` (repeat for medium/hard), or in each exercise `cc -std=c11 -O2 -Wall -Wextra tests.c -o /tmp/practice-test && /tmp/practice-test`. Starter tests intentionally fail until implemented. Reference validation: `python scripts/check_reference.py practice/2026-11-26-c`. Read the statement, design a baseline and invariant, implement, run tests, fill attempt.md, then open reference/.

The one-time `review-guides/graphs-and-cpp-review.md` already exists on main and the inherited branch (same blob); it is not regenerated.
