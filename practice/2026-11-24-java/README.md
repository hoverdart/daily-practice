# Tuesday, November 24, 2026 — Java Interview Practice

Exactly three original exercises. Work in the unfinished Solution.java files, then fill out attempt.md before opening reference/.

| Difficulty | Problem | Pattern | Suggested time |
| --- | --- | --- | --- |
| Easy | Previous Higher Priority | Monotonic stack, nearest greater index | 15–25 min |
| Medium | Longest Quiet Block | Sliding window, equal-pair budget, HashMap | 25–40 min |
| Hard/stretch | Second Distinct Dispatch Arrival | Two-label Dijkstra, priority queue, weighted walks | 40–65 min |

## Adaptive selection

Read curriculum/cs61b.md, CONCEPTS.md, PROGRESS.md, recent attempt logs (November 19, 20, and 23), and the October 5 completed attempts. The progress table is blank, and the recent attempts examined are unfilled. October 5 recorded hashing 5/5 (independent), sliding windows 2/5 (hint-assisted, frequency-map bookkeeping), and shortest paths 1/5 (unfinished). Do not treat exposure to newer exercises as mastery.

- Easy: introduce nearest-greater stack reasoning as a variation on CS61B stacks, arrays, and amortized analysis. The last inspected easy exercise was BFS; this shifts back to sequence structures.
- Medium: revisit the exact weak spot, updating counts as either boundary moves. Yesterday counted exactly-K distinct windows; today maximizes a length under a pair-count budget. The statistic is neither distinct count nor duplicate-ID count.
- Hard: revisit weighted path relaxation after yesterday's SCC/DAG exercise. A vertex can have two useful distinct cost labels; stopping on the first target arrival is insufficient. Positive costs and allowed revisits make this a different problem from finding a second simple path.

## Run

```bash
python scripts/run_problem.py practice/2026-11-24-java/easy
python scripts/run_problem.py practice/2026-11-24-java/medium
python scripts/run_problem.py practice/2026-11-24-java/hard
python scripts/check_reference.py practice/2026-11-24-java
```

From an individual problem directory, `javac Solution.java TestSolution.java && java TestSolution` runs the starter tests. Failure before implementation is intentional. The reference runner copies the optimal code into a temporary Solution.java, preserving your starter and attempts.

The existing review-guides/graphs-and-cpp-review.md was verified on main and the inherited branch; it is unchanged.
