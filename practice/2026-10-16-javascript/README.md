# Friday, October 16, 2026 — JavaScript (Node.js 18+)

Three original interview-style problems, chosen from the CS61B curriculum and actual attempt history.

| Level | Problem | Core pattern | Target time |
| --- | --- | --- | --- |
| Easy | First Nearby Duplicate Signal | Sliding window + Set, window boundary invariant | 15–20 min |
| Medium | Prefix Router Ledger | Trie, multiplicity, prefix counts, deletion | 30–40 min |
| Hard / stretch | Keycard Escape Maze | BFS on (cell, key mask) state space | 45–65 min |

## Why these, not three random questions?

The October 5 completed logs record **5/5** on basic hash/set lookup, **2/5** on frequency-based sliding windows (hint needed), and **1/5** on shortest-path recognition/implementation (unfinished). October 6–15 attempt logs are unfilled in the latest branch, so the set **does not assume those later problems were solved**. PROGRESS.md's confidence table is also still blank.

- Easy revisits the weak *window boundary* concept with a familiar Set instead of another frequency-map exercise.
- Medium introduces **tries**, a central CS61B concept not yet assessed in the available completed logs; multiplicity and deletion force careful invariants.
- Hard returns to the weakest **shortest-path** skill, but uses unweighted BFS with *augmented state* rather than repeating Dijkstra yet again.

## Run

Work in each `solution.js` and fill `attempt.md` **before** opening `reference/`. Starter files intentionally throw.

```bash
python scripts/run_problem.py practice/2026-10-16-javascript/easy
python scripts/run_problem.py practice/2026-10-16-javascript/medium
python scripts/run_problem.py practice/2026-10-16-javascript/hard
python scripts/check_reference.py practice/2026-10-16-javascript
```

Or from a problem directory: `node tests.js`. Tests include fixed edge cases and deterministic randomized oracle comparisons; no npm packages required.

The existing one-time `review-guides/graphs-and-cpp-review.md` is intentionally unchanged.
