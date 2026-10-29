# Thursday, October 29, 2026 — C interview practice

Three **original** exercises, ordered by difficulty. Work in each `solution.c` first; do not open `reference/` until after recording your attempt.

| Level | Problem | Main skills |
|---|---|---|
| Easy | Compress Repeated Command Runs | C strings, two pointers, in-place writes |
| Medium | Shortest Distinct-Signal Coverage | Sliding window, frequency table, shrink-while-valid |
| Hard / stretch | Maximum Reward with Setup Cooldown | Sorting, binary search, weighted interval DP |

## Why this selection?
The latest **completed** attempts (October 5) recorded 5/5 for hashing, 2/5 for sliding windows (hint needed), and 1/5 for shortest paths (unfinished). The October 22–28 attempt files remain unfilled, so they are **not** evidence of improvement or failure. This set revisits sliding-window bookkeeping in C while adding string/pointer fluency and a dynamic-programming alternative to the many recent graph hard problems. The CS61B curriculum and CONCEPTS.md also call for amortized reasoning, binary search, sorting, and DP extensions.

## Run
From the repository root:

```sh
python scripts/run_problem.py practice/2026-10-29-c/easy
python scripts/run_problem.py practice/2026-10-29-c/medium
python scripts/run_problem.py practice/2026-10-29-c/hard
python scripts/check_reference.py practice/2026-10-29-c
```

The starter files intentionally return placeholders; tests are designed to fail until you implement them. The reference checker substitutes each `reference/optimal.c` into the starter slot. Recommended timeboxes: 15 / 30 / 50 minutes. Record complexity, test failures, and hint usage in each `attempt.md`.
