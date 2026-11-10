# Tuesday, November 10, 2026 — Java practice

Exactly **three original interview-style problems**. Write your own implementation in each Solution.java before opening reference/.

| Level | Problem | Skills | Suggested time |
|---|---|---|---|
| Easy | Two-Stack Alert Inbox | FIFO queue implemented with LIFO stacks, amortized analysis, ArrayDeque | 15–20 min |
| Medium | Count Affordable Mixed-Channel Bursts | Sliding window, HashMap frequencies, two monotone constraints, counting windows | 25–35 min |
| Hard / Stretch | Evacuate the Flooded Relay Station | Multi-source BFS, time-dependent safety, expanded grid states, shortest paths | 40–55 min |

## Adaptation and spaced repetition

Grounding: curriculum/cs61b.md, CONCEPTS.md, PROGRESS.md, and actual recent practice/**/attempt.md files on the latest practice branch.

- The last **completed** assessments in October 5's attempts were hash/set **5/5 independently**, sliding window **2/5 with a hint**, and shortest-path graph search **1/5, unfinished**. Latest inspected November 2–9 templates were blank, not evidence of improvement. PROGRESS.md still has no filled topic-confidence cells.
- Easy rotates to under-rehearsed queue implementation and an amortized invariant, rather than another set/hash problem.
- Medium returns to the weak sliding-window frequency-map skill, but counts **all valid intervals** under simultaneous limits on total cost and distinct channels. The key is that both restrictions are monotone on shrinking because costs are nonnegative.
- Hard targets weak shortest-path recognition **without repeating Dijkstra**. A multi-source flood BFS produces a deadline for each grid cell; then a human BFS uses a separate permit-used state and only enters cells before flooding. This combines CS61B BFS layering and state graphs.
- No existing practice folder was overwritten. The one-time guide at review-guides/graphs-and-cpp-review.md already exists and is not recreated.

## Run and review

From repository root, with JDK 17+ and Python 3:

~~~bash
python scripts/run_problem.py practice/2026-11-10-java/easy
python scripts/run_problem.py practice/2026-11-10-java/medium
python scripts/run_problem.py practice/2026-11-10-java/hard

# Tests reference implementations in separate temporary directories:
python scripts/check_reference.py practice/2026-11-10-java
~~~

The starter methods deliberately throw UnsupportedOperationException until you solve them. Each test harness contains fixed edge cases, randomized comparisons against a simpler independent oracle, input immutability checks, and a stress case. Record your first attempt and confidence in attempt.md **before** looking at reference/notes.md or reference/Optimal.java.
