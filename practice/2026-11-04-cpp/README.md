# Wednesday, November 4, 2026 — C++ Practice

Three original interview-style exercises. **Try each problem before opening its reference/ directory.**

| Level | Problem | Interview pattern | Suggested time |
|---|---|---|---|
| Easy | Calibration Undo Stack | Stack, prefix aggregates, constant-time queries | 15–20 min |
| Medium | Wildcard Signature Matches | Fixed-size sliding window, frequency deficits | 25–35 min |
| Hard / stretch | Coordinated Relay Rendezvous | Three Dijkstra runs, reverse graph, minimax arrival | 45–60 min |

## Why this selection is adaptive

The CS61B curriculum and CONCEPTS.md emphasize stacks, hashing, graphs, shortest paths, asymptotic reasoning, and deque/window fluency. PROGRESS.md has no current self-ratings. Recent inspected attempt.md files (October 28 through November 3) contain prompts but no filled performance scores, so no recent success is presumed. Older recorded feedback flagged sliding-window bookkeeping and shortest paths as weaker than hashing.

- **Easy:** reinforce the CS61B stack invariant with a query-ready running maximum and C++ vector/pair syntax.
- **Medium:** repeat the weaker sliding-window concept in a **fixed-length** setting instead of another longest-valid-window problem. Frequency deficits and wildcard slots are the trick.
- **Hard:** revisit nonnegative shortest paths without repeating coupon-state, 0-1 BFS, or time-dependent routes. Three shortest-path runs and reversed edges model two independently moving agents that synchronize.

## How to run

~~~bash
python scripts/run_problem.py practice/2026-11-04-cpp/easy
python scripts/run_problem.py practice/2026-11-04-cpp/medium
python scripts/run_problem.py practice/2026-11-04-cpp/hard
~~~

Tests deliberately fail until you implement solution.cpp. To validate the provided reference solutions without modifying your own starters:

~~~bash
python scripts/check_reference.py practice/2026-11-04-cpp
~~~

For each problem: read problem.md, fill in solution.cpp, run tests, complete attempt.md, then consult reference/notes.md and reference/optimal.cpp.

## Spaced-repetition checkpoints

1. Stack: what makes a maximum query O(1), even after undo?
2. Window: what does a **positive** frequency deficit mean, and when does removing a letter increase it?
3. Graph: why does one shortest-path search from the destination need **reversed** directed edges?

The existing one-time graph and C/C++ packet at review-guides/graphs-and-cpp-review.md was checked and left unchanged.
