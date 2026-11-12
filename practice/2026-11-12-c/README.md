# Thursday, November 12, 2026 — C Interview Practice

Exactly **three original** exercises. Solve the starter before opening reference/. C11 is used throughout.

| Level | Problem | Central techniques | Suggested time |
|---|---|---|---|
| Easy | Two-Log Replay Quota | Two pointers, sorted runs, careful size_t arithmetic | 15–20 min |
| Medium | Longest Drift-Controlled Span | Sliding window on adjacent-edge costs, 64-bit arithmetic | 25–40 min |
| Hard / stretch | Which Cables Are True Bridges? | Undirected DFS, low-link values, iterative stack, parallel edges | 45–70 min |

## Adaptive rationale

Selection uses curriculum/cs61b.md, CONCEPTS.md, PROGRESS.md and inspected recent practice/**/attempt.md files. PROGRESS.md's confidence table remains blank and the November 6, 9, 10, and 11 attempt logs inspected are unfilled templates: do **not** infer improvement from the mere appearance of a problem. Earlier completed feedback identified sliding windows as weaker than hashing; shortest paths and graph reasoning remain retention priorities.

- Easy: review the basic sorted-sequence/two-pointer pattern with duplicates and C unsigned indices, after several implementation-heavy easy tasks.
- Medium: spaced repetition for **sliding-window invariants**, but use a *sum of costs on edges between adjacent readings* rather than item counts/frequency tables. The cost removed at a left shift is an edge, not a reading.
- Hard: return to CS61B DFS/connectivity with **low-link bridge detection**, different from shortest-path critical edges. Explicit edge IDs handle parallel cables; an iterative DFS avoids a C call-stack overflow.

## Run

From the repository root:

~~~sh
python scripts/run_problem.py practice/2026-11-12-c/easy
python scripts/run_problem.py practice/2026-11-12-c/medium
python scripts/run_problem.py practice/2026-11-12-c/hard
~~~

Your starters are intentionally unfinished, so their tests should fail until you implement them. To validate reference answers without touching starters:

~~~sh
python scripts/check_reference.py practice/2026-11-12-c
~~~

Tests include fixed examples, edge cases, seeded random comparisons against separate brute-force oracles, and large inputs. The runner compiles C11 with cc -O2 -Wall -Wextra.

## Reflection

1. Explain the monotone motion of the two pointers in the easy problem; what happens to a whole run of duplicates?
2. In the medium, state the exact meaning of drift in the current window. What single edge disappears when the left boundary advances?
3. In the hard, write down the discovery-time/low-link invariant and explain why the parent **edge ID**, rather than the parent vertex, must be excluded.
4. Record your own runtimes, confidence, failed cases, and any manual-memory mistakes in each attempt.md.

## One-time review packet

review-guides/graphs-and-cpp-review.md already exists on the inherited branch. Preserved unchanged; no duplicate guide generated.

