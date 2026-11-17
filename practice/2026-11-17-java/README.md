# Tuesday, November 17, 2026 — Java practice

Exactly **three original interview-style problems**, with independent tests and optimal references. Work on the unfinished Solution.java files and log your attempts before opening reference/.

| Level | Problem | Focus | Suggested time |
|---|---|---|---|
| Easy | Oldest Unique Event in a Live Feed | HashMap, ArrayDeque, lazy queue eviction, amortized reasoning | 15–20 minutes |
| Medium | Longest Fair Worker Session | Sliding window, HashMap frequency counts, two differently directed constraints | 25–35 minutes |
| Hard / Stretch | Safest Bottleneck Route Queries | Kruskal MST forest, union-find, binary lifting, minimax-path theorem | 40–60 minutes |

## Adaptive selection

I used curriculum/cs61b.md, CONCEPTS.md, PROGRESS.md, and the existing attempts (including October 5's completed assessments and the recent November 9–16 logs). October 5's completed attempts showed hash/set confidence **5/5**, a sliding-window problem **2/5 after a hint**, and graph shortest paths **1/5 unfinished**. Later reviewed attempts are blank; that is **missing feedback**, not evidence of mastery. PROGRESS.md contains no populated confidence ratings.

- Easy is a light Java API and data-structure warmup. It requires coordinating a HashMap with a queue and explaining why apparently nested removals are amortized O(n), rather than redoing a pure set-membership exercise.
- Medium revisits the weak frequency-map/window skill. This time each worker has a *per-value* usage cap while the window must have *enough distinct workers*. Those constraints have opposing directions, so careless "shrink until everything is satisfied" logic is wrong.
- Hard extends CS61B graph and shortest-path fundamentals without assigning another ordinary Dijkstra variant. It blends Kruskal/union-find with tree ancestors, and requires the minimum-spanning-tree minimax property. This also revisits binary lifting introduced November 11, after a spacing interval.
- The one-time graphs/C++ packet already exists at review-guides/graphs-and-cpp-review.md. This run deliberately leaves it unchanged.

## Run locally

From repository root, with JDK 17+ and Python 3:

~~~bash
python scripts/run_problem.py practice/2026-11-17-java/easy
python scripts/run_problem.py practice/2026-11-17-java/medium
python scripts/run_problem.py practice/2026-11-17-java/hard

# Replace each starter with its reference in a temporary directory and test:
python scripts/check_reference.py practice/2026-11-17-java
~~~

The starter methods intentionally throw UnsupportedOperationException until implemented; passing reference tests does **not** mean your starter already solves the problem. The test harnesses use deterministic edge cases, seeded small randomized oracle comparisons, and large performance stress cases. Tests do not edit inputs. For a useful adaptive signal, fill out each attempt.md with outcome, confidence, claimed complexity, first failure, and any hint dependencies.

