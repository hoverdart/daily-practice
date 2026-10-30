# Friday, October 30, 2026 — JavaScript interview practice

Exactly three **original** exercises. Attempt each starter before opening `reference/`.

| Difficulty | Problem | Primary skills | Timebox |
|---|---|---|---|
| Easy | Closest Shared Supervisor | Rooted forests, parent pointers, Set | 15–20 min |
| Medium | Longest Recalibratable Signal Run | Sliding window, frequency Map, amortized proof | 25–35 min |
| Hard / Stretch | Critical Route Count in a DAG | Topological sorting, longest-path DP, path counting | 40–55 min |

## Adaptive rationale

- The last **completed** attempts (October 5) recorded hashing **5/5** (independent), sliding windows **2/5** (hint required; uncertainty about frequency maps), and shortest paths **1/5** (unfinished and needed Dijkstra help). Later attempt templates inspected through October 29 have no recorded outcomes; blank fields are not evidence of mastery.
- Easy uses parent pointers and tree ancestry, a less-recently practiced CS61B foundation. A `Set` is intentionally familiar so attention can shift to tree reasoning.
- Medium revisits a weak sliding-window concept with a **different invariant**: minimum replacements to make a window constant, and a deliberately *historical* maximum frequency.
- Hard revisits graph relaxation without repeating Dijkstra: topological order on a DAG permits **negative** edge weights and simultaneous counting of maximum-weight routes.

## Run

From repository root:

```sh
python scripts/run_problem.py practice/2026-10-30-javascript/easy
python scripts/run_problem.py practice/2026-10-30-javascript/medium
python scripts/run_problem.py practice/2026-10-30-javascript/hard
```

Starters deliberately throw TODO errors; tests initially fail. Once you have attempted each exercise, fill in its `attempt.md`, then read `reference/notes.md` and `reference/optimal.js`.

To validate reference implementations **without modifying starters**:

```sh
python scripts/check_reference.py practice/2026-10-30-javascript
```

Each test suite includes fixed edge cases, seeded small randomized cases compared with an independently structured oracle, and larger stress tests. The existing one-time `review-guides/graphs-and-cpp-review.md` was already present and is not regenerated.
