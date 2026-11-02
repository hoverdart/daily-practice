# Monday, November 2, 2026 — Python interview practice

Exactly three original interview-style exercises. Work in `solution.py` before looking inside `reference/`.

| Difficulty | Problem | Core skills | Suggested time |
|---|---|---|---|
| Easy | Prefix Counts in a Routing Directory | Trie, prefix counts, duplicate handling | 15–20 min |
| Medium | Longest Policy-Compliant Event Window | Sliding window, frequency maps, amortized proof | 25–35 min |
| Hard / Stretch | Directional Rail Repairs | Implicit grid graphs, 0-1 BFS, deque, relaxation | 40–55 min |

## Adaptive rationale

- The last **filled-in** October 5 attempts showed hashing/set usage **5/5** independently, sliding-window frequency maps **2/5** with a hint, and shortest-path graph algorithms **1/5** with an unfinished solution. More recent attempt files through October 30 were checked and are still unfilled, so no later mastery is inferred.
- Easy introduces an under-practiced CS61B structure: tries. The familiar dictionary API allows focus on prefix-node invariants and duplicates.
- Medium targets the known weak spot (sliding-window frequency maps) using **per-ID capacity constraints**, including the subtle zero-cap case.
- Hard revisits shortest paths without another standard Dijkstra exercise: **0-1 BFS** uses a deque to implement shortest-path relaxation in linear time.
- These choices follow `curriculum/cs61b.md`, `CONCEPTS.md`, and `PROGRESS.md` and avoid repeating the immediately preceding daily problem surfaces.

## Run

From repository root:

```sh
python scripts/run_problem.py practice/2026-11-02-python/easy
python scripts/run_problem.py practice/2026-11-02-python/medium
python scripts/run_problem.py practice/2026-11-02-python/hard
```

Starters intentionally raise `NotImplementedError`; tests fail until you implement them. For reference-only validation (without changing your starter files):

```sh
python scripts/check_reference.py practice/2026-11-02-python
```

Each test suite contains fixed edge cases, a seeded independent oracle, and large stress tests. After each attempt, record time, confidence, approach, failed cases, and hints in `attempt.md`, then compare against the reference.

The existing one-time `review-guides/graphs-and-cpp-review.md` was checked and **left unchanged**.