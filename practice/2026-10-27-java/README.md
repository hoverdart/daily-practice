# October 27, 2026 — Java Interview Practice

| Difficulty | Original problem | Topics |
| --- | --- | --- |
| Easy | Closest Calibration Threshold | BST search, height, tie-breaking |
| Medium | Budgeted Distinct Signal Windows | Sliding windows, HashMap, exactly-K counting |
| Hard / Stretch | Timetabled Relay Network | Time-dependent Dijkstra, min-heaps, waiting |

## Adaptive selection

The October 5 completed attempts reported hashing confidence 5/5, sliding-window confidence 2/5 with a hint, and shortest-path confidence 1/5 unfinished. More recent attempt logs on the latest practice branch are blank; PROGRESS.md also has unfilled confidence fields. This set therefore revisits the two weaker areas with different problem structures and adds an under-practiced CS61B binary search tree fundamental. The selection follows curriculum/cs61b.md and CONCEPTS.md.

## Instructions

Read each problem.md and solve in Solution.java before viewing reference/. Record your approach, timing, confidence, mistakes, and complexity in attempt.md. Java 17+ recommended. From repository root:

~~~bash
python scripts/run_problem.py practice/2026-10-27-java/easy
python scripts/run_problem.py practice/2026-10-27-java/medium
python scripts/run_problem.py practice/2026-10-27-java/hard
python scripts/check_reference.py practice/2026-10-27-java
~~~

The starter implementations deliberately throw until completed. Tests include deterministic edge cases, seeded randomized independent oracles, and large performance cases. The existing one-time graph/C++ guide is unchanged.
