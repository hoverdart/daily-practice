# Friday, November 6, 2026 — JavaScript interview practice

Exactly **three original interview-style problems**. Timebox each independently before opening the corresponding reference folder.

| Difficulty | Problem | Focus | Suggested time |
|---|---|---|---|
| Easy | Nearest Blocking Beacon | Monotonic stack, nearest qualifying element, equal values | 15–20 min |
| Medium | Exactly K Signal Collision Pairs | Hash-map sliding window, counting intervals, atMost difference | 25–40 min |
| Hard / stretch | Cheapest Compliant Deployment Order | Dependency DAG, bitmask DP, transition costs | 40–60 min |

## Why these three?

The curriculum/cs61b.md and CONCEPTS.md emphasize stacks, hashing, graph representations, directed dependencies, runtime analysis, and dynamic programming as an interview extension. PROGRESS.md has not been filled in with updated confidence scores. Recent attempt logs (November 2–5) still contain blank outcomes, so they **do not** establish new mastery.

The latest completed records (October 5) showed independent hashing success (5/5), a hint-dependent frequency-map sliding window (2/5), and an unfinished shortest-path problem (1/5). This set intentionally builds on a familiar Map while requiring a stronger two-pointer invariant. The easy introduces a monotonic stack, rather than repeating a familiar Set problem; the hard mixes graph prerequisites and dynamic programming, without assigning another conventional Dijkstra problem after many graph-heavy days.

## How to use

From the repository root, run your own unfinished starter solutions:

~~~bash
python scripts/run_problem.py practice/2026-11-06-javascript/easy
python scripts/run_problem.py practice/2026-11-06-javascript/medium
python scripts/run_problem.py practice/2026-11-06-javascript/hard
~~~

They intentionally throw an error until implemented. After each attempt, fill in attempt.md. Then inspect reference/notes.md and reference/optimal.js.

To check the references **without changing starter files**:

~~~bash
python scripts/check_reference.py practice/2026-11-06-javascript
~~~

Tests include fixed boundary cases, deterministic seeded randomized comparisons to simple independent oracles, and large stress cases. Node.js 18+ is sufficient.

## Questions for your notebook

1. Easy: Why must the monotonic stack pop strictly *smaller* readings, not equal readings?
2. Medium: If a new occurrence of x enters the window, why does the number of colliding pairs increase by the old frequency of x? What happens upon removal?
3. Hard: What information is missing if a DP state stores only the set of completed tasks, without the most recently completed task?
4. Can you state the loop invariant and complexity *before* opening each reference?

The one-time review-guides/graphs-and-cpp-review.md was verified on the existing repository and is intentionally left unchanged.
