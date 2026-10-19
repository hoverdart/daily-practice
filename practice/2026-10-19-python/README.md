# Monday, October 19, 2026 — Adaptive Python Practice

Three **original** interview problems for Python 3.12 (standard library only). Attempt in order: easy (15–20 minutes), medium (25–35 minutes), hard/stretch (45–60 minutes).

| Level | Problem | Recognition focus |
| --- | --- | --- |
| Easy | Zero-Balance Telemetry Spans | Prefix sums + hash frequency map |
| Medium | Low-Load Processing Batches | Multiplicative sliding window + count-all-endings |
| Hard | Repair-Station Relay Route | Two Dijkstra runs + path reconstruction |

## Why this selection?

The latest **completed** attempt logs (October 5) report **5/5** for basic hash/set membership, **2/5** for sliding-window counting (hint needed; unclear frequency-map invariant and Python deletion syntax), and **1/5** for Dijkstra (unfinished; heap API and relaxation needed review). Recent October 7–16 attempt logs inspected remain blank; they are **not** evidence of mastery. PROGRESS.md's topic confidence table is also blank.

- **Easy:** transfer comfortable hashing into a new prefix-sum invariant; practice Python dict.get.
- **Medium:** revisit the weak moving-window invariant seven-plus days later, but with products and a counting objective instead of distinct-type frequency maps.
- **Hard:** revisit weighted shortest paths after a week, this time requiring two independent distance arrays, a selected waypoint, and actual parent-based route reconstruction. No resource/coupon state expansion.

These choices draw on curriculum/cs61b.md, CONCEPTS.md, PROGRESS.md, and actual practice attempt logs. The one-time graph/C++ packet already exists at review-guides/graphs-and-cpp-review.md and is **not regenerated**.

## Practice protocol

1. Read only each problem.md and starter solution.py. Explain the brute-force baseline and state the invariant aloud.
2. Edit solution.py. From the repo root run:
   ~~~bash
   python scripts/run_problem.py practice/2026-10-19-python/easy
   python scripts/run_problem.py practice/2026-10-19-python/medium
   python scripts/run_problem.py practice/2026-10-19-python/hard
   ~~~
3. Complete attempt.md **before** opening reference/.
4. Then study reference/notes.md and reference/optimal.py. Validate untouched references with:
   ~~~bash
   python scripts/check_reference.py practice/2026-10-19-python
   ~~~

Tests include fixed edge cases, seeded independent brute-force oracles, and large inputs. Starters intentionally raise NotImplementedError. Record outcomes so future selection can respond to actual progress.

