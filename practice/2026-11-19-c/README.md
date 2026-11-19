# Thursday, November 19, 2026 — C Interview Practice

Exactly three original exercises. Solve each `solution.c` before opening its `reference/` directory. Each `tests.c` includes the sibling solution file; starter tests **intentionally fail** until you implement the functions.

| Level | Exercise | Target pattern | Suggested time |
|---|---|---|---|
| Easy | Solo Alerts in a Sorted Chain | Singly linked lists, pointer ownership, freeing removed runs | 15–25 min |
| Medium | Longest Stable Sensor Window | Sliding window + two monotonic deques, extreme integer bounds | 25–40 min |
| Hard/stretch | Fewest Turns for a Grid Relay | 0–1 BFS, directional state graphs, an explicit C deque | 40–65 min |

## Why these concepts

Reviewed `curriculum/cs61b.md`, `CONCEPTS.md`, `PROGRESS.md`, and recent `attempt.md` files on the November 18 branch. The PROGRESS confidence table is empty. The latest November 12, 16, 17, and 18 attempt templates remain blank; do not treat a generated problem as a completed attempt.

The most recent *filled* evaluations (October 5) report easy hashing **5/5 independently**, medium sliding-window bookkeeping **2/5 with a hint**, and hard shortest-path algorithms **1/5 unfinished**. Today's easy rehearses the C linked-list/ownership skill after a two-week gap; the medium revisits a contiguous-window invariant but replaces a frequency table or drift sum with *two monotonic deques*; the hard revisits graph shortest paths through a new 0–1 BFS variant, extending the BFS and deque topics in CS61B. These are new problem stories and constraints, not repeats of November 12's drift window or November 13's expanded-state Dijkstra.

## Run

From repository root:

```bash
python scripts/run_problem.py practice/2026-11-19-c/easy
python scripts/run_problem.py practice/2026-11-19-c/medium
python scripts/run_problem.py practice/2026-11-19-c/hard

# Reference validation (runs the optimal solutions in a temporary copy):
python scripts/check_reference.py practice/2026-11-19-c
```

Or directly from a problem folder: `cc -std=c11 -O2 -Wall -Wextra tests.c -o /tmp/practice-test && /tmp/practice-test`. Tests have deterministic edge cases, seeded randomized comparisons to independent small-input oracles, and larger stress cases.

Work in this order: statement → brute-force idea and invariant → starter implementation → local tests → fill attempt.md → reference notes and implementation. For C, track not only time/space, but also **who owns every allocation** and what overflow/underflow can occur.

## One-time review packet

`review-guides/graphs-and-cpp-review.md` already exists on the repository's main branch. It has been checked and is intentionally **not** regenerated or modified.
