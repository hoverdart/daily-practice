# Tuesday, October 13, 2026 — Adaptive Java Practice

Exactly three original problems (Java 17+, standard library only).

| Level | Problem | Pattern |
| --- | --- | --- |
| Easy | Deepest Leftmost Sensor | Tree level-order BFS |
| Medium | Minimum Calibration Segment | Sliding window with quota counts |
| Hard | Prelinked Fiber Network | Kruskal, sorting, union-find |

## Adaptive selection

Read curriculum/cs61b.md, CONCEPTS.md, PROGRESS.md, and the October 5–12 attempt logs. The only completed attempts remain October 5: hash lookup 5/5, sliding window 2/5 with hints and confusion about frequency counts, and Dijkstra 1/5 unfinished. Subsequent attempt logs and the progress table are blank; no newer mastery is assumed.

Easy introduces underpracticed trees while revisiting queue-based traversal. Medium targets the weak sliding-window invariant in Java. Hard broadens graph fluency to minimum spanning trees and disjoint sets rather than another Dijkstra variant.

## Run

From the repository root:

```bash
python scripts/run_problem.py practice/2026-10-13-java/easy
python scripts/run_problem.py practice/2026-10-13-java/medium
python scripts/run_problem.py practice/2026-10-13-java/hard
```

Work in Solution.java and fill attempt.md before opening reference/. Starter solutions intentionally throw. Test untouched references with:

```bash
python scripts/check_reference.py practice/2026-10-13-java
```

Tests include edge cases, seeded independent slow oracles, and stress cases. The existing one-time review-guides/graphs-and-cpp-review.md is preserved.
