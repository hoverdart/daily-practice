# October 20, 2026 — Java Practice

| Level | Original problem | Concepts |
| --- | --- | --- |
| Easy | Next Higher Voltage Reading | Monotonic stack, ArrayDeque |
| Medium | Longest Stream with Limited Repeated Types | Sliding window, HashMap |
| Hard | Count the Fastest Dispatch Routes | Dijkstra, shortest-path counting |

## Why these topics?
The completed October 5 attempt logs show hashing confidence 5/5, sliding windows 2/5 with a hint, and Dijkstra 1/5 unfinished. More recent attempt logs and PROGRESS.md confidence cells are blank, so no newer mastery is assumed. These exercises revisit weak window and shortest-path invariants, plus an underpracticed stack pattern. Selection follows curriculum/cs61b.md and CONCEPTS.md.

## Run
Use Java 17+ and the repository runner:

```bash
python scripts/run_problem.py practice/2026-10-20-java/easy
python scripts/run_problem.py practice/2026-10-20-java/medium
python scripts/run_problem.py practice/2026-10-20-java/hard
```

Write your answers in Solution.java and complete attempt.md before reading reference/. Validate the reference solutions with:

```bash
python scripts/check_reference.py practice/2026-10-20-java
```

Each problem includes fixed cases, seeded randomized oracles, and stress tests. Starters intentionally throw until implemented.

The existing one-time graph/C++ review guide was preserved unchanged.
