# Friday, November 20, 2026 — JavaScript Interview Practice

**Exactly three new interview problems**. First implement each unfinished `solution.js`, run `tests.js`, log your actual performance in `attempt.md`, and only then examine `reference/`.

| Difficulty | Problem | Skills | Suggested time |
| --- | --- | --- | --- |
| Easy | Filter Invalid Routing Markers | Stack, greedy parentheses matching, string reconstruction | 15–25 min |
| Medium | Shortest Incident Evidence Segment | Sliding window, multiplicity map, reset barrier, tie-breaking | 25–40 min |
| Hard/stretch | Cheapest Route After Reversing One Link | Directed weighted graphs, two Dijkstra passes, min-heap | 40–70 min |

## Adaptive rationale and spaced repetition

I checked `curriculum/cs61b.md`, `CONCEPTS.md`, `PROGRESS.md`, and recent `attempt.md` entries (November 16–19 plus older completed attempts). The confidence tables in PROGRESS are blank and the latest attempts are **unfilled templates**, not measured success. The last filled October 5 feedback describes hashing confidence 5/5, sliding-window bookkeeping 2/5 with hints, and shortest paths 1/5 unfinished.

- **Easy:** basic stack correctness and string/array fluency are core CS61B foundations, providing variety after yesterday's C pointer and deque practice.
- **Medium:** returns to a weak frequency-map window invariant in a new *minimum covering segment with a reset barrier* setting. This is a spaced follow-up, not the same exact-K-counting or longest-window problem recently used.
- **Hard:** revisits the weaker weighted-shortest-path topic through an edge-reversal theorem and a **forward + reverse** Dijkstra strategy. Unlike recent expanded-state 0–1 BFS, this has a different algorithmic reduction.

## How to run

From the repository root:

```bash
python scripts/run_problem.py practice/2026-11-20-javascript/easy
python scripts/run_problem.py practice/2026-11-20-javascript/medium
python scripts/run_problem.py practice/2026-11-20-javascript/hard

# Checks the optimal reference implementations without touching the starters:
python scripts/check_reference.py practice/2026-11-20-javascript
```

Or in an individual problem folder: `node tests.js`. **Starter tests deliberately fail** because the solutions are unfinished. The tests exercise deterministic corner cases, seeded small randomized comparisons with independent oracles, and large stress inputs.

## Reflection after solving

1. Why does a stack resolve unmatched open delimiters, and why is an unmatched close irrevocable?
2. In a variable-length minimum window, what does the missing count mean? What happens at a reset marker?
3. Why is the shortest path to a target in the reverse graph useful?
4. What precise invariant distinguishes Dijkstra from ordinary BFS and from 0–1 BFS?

## One-time review guide

`review-guides/graphs-and-cpp-review.md` already exists on the inherited branch. It is intentionally **not** recreated or modified.

