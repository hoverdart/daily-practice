# Friday, November 13, 2026 — JavaScript Interview Practice

Exactly **three original** interview-style exercises. Solve the unfinished `solution.js` in each folder before reading `reference/`.

| Level | Problem | Central techniques | Suggested time |
|---|---|---|---|
| Easy | First Full Network Merge | Disjoint sets, path compression, union by size | 15–25 min |
| Medium | Longest Exact Net-Change Run | Signed prefix sums, earliest occurrence map | 25–40 min |
| Hard / stretch | Alternating-Band Relay Route | Weighted shortest paths, expanded states, min-heap | 45–70 min |

## Adaptive rationale

Selection uses `curriculum/cs61b.md`, `CONCEPTS.md`, `PROGRESS.md`, and recent `practice/**/attempt.md` through November 12. PROGRESS's confidence table is blank and the latest attempt files inspected are unfilled templates, so no new improvement is inferred. Earlier feedback identified sliding-window reasoning and shortest paths as weaker than hashing.

- **Easy:** DSU/weighted quick union is explicit CS61B material that has not been tested in the recent rotation. This reviews component invariants and amortized analysis.
- **Medium:** revisit sliding-window **recognition by contrast**: negative values invalidate the monotone-sum assumption needed by standard sliding windows. Use prefix sums + earliest hash-map entries instead. Choosing the right pattern is part of spaced repetition.
- **Hard:** return to weighted shortest paths with a new **last-transition-band** state dimension, rather than repeating the coupon, bridge, or LCA problems. JavaScript requires a hand-built min-heap.

## Run locally

```sh
python scripts/run_problem.py practice/2026-11-13-javascript/easy
python scripts/run_problem.py practice/2026-11-13-javascript/medium
python scripts/run_problem.py practice/2026-11-13-javascript/hard
```

The starters intentionally throw TODO errors until implemented. Check reference implementations without editing starters:

```sh
python scripts/check_reference.py practice/2026-11-13-javascript
```

All suites contain fixed edge cases, seeded independent brute-force oracles, and large stress tests. Log failures, runtime reasoning and confidence in each `attempt.md`.

The existing one-time `review-guides/graphs-and-cpp-review.md` was confirmed on the inherited branch; it is retained unchanged without duplication.
