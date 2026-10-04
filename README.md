# Daily Practice

A weekday interview-prep system that keeps algorithmic problem solving, data structures, and language fluency sharp.

Every weekday at **9:00 AM Pacific Time**, ChatGPT prepares three original interview-style problems for one language and commits them into this repository:

| Day | Language |
|---|---|
| Monday | Python |
| Tuesday | Java |
| Wednesday | C++ |
| Thursday | C |
| Friday | JavaScript |
| Saturday | Rest |
| Sunday | Rest |

Each day contains an **easy**, **medium**, and **hard/stretch** problem. Problem selection is curriculum-aware: it revisits CS61B material, uses spaced repetition from recent `attempt.md` files, and gradually introduces adjacent interview patterns.

## Daily structure

```text
practice/
  YYYY-MM-DD-language/
    README.md
    easy/
      problem.md
      solution.<ext>      # your file
      tests.<ext>
      attempt.md
      reference/
        optimal.<ext>
        notes.md
    medium/
      ...
    hard/
      ...
```

**Rule:** do not open `reference/` until you have made a serious attempt.

## Recommended workflow

1. Read the day's `README.md` and each `problem.md`.
2. Work only in `solution.<ext>`.
3. Run the provided tests locally.
4. Fill out `attempt.md` honestly.
5. Only then read `reference/notes.md` and `reference/optimal.<ext>`.
6. Commit your attempt. Future daily sets can use recent attempt notes as feedback for spaced repetition.

## Philosophy

The goal is not raw LeetCode volume. The system optimizes for:

- **pattern recognition** — knowing when to reach for binary search, BFS, heaps, hashing, etc.;
- **implementation fluency** — writing the same ideas comfortably in Python, Java, C++, C, and JavaScript;
- **CS fundamentals retention** — especially the material from CS61B;
- **runtime reasoning** — being able to justify time and space complexity;
- **deliberate review** — weak concepts recur more often, strong concepts recur less often;
- **transfer** — some problems constrain library use or ask you to implement the underlying structure.

Problems are generated as **original interview-style exercises** rather than copying proprietary problem statements from LeetCode, HackerRank, Coderbyte, or similar platforms.

## Automation architecture

Generation is handled by ChatGPT on the weekday schedule and does **not** require an OpenAI API key in this repository.

GitHub Actions is validation-only. Whenever generated practice content is pushed, `.github/workflows/daily-practice.yml` compiles/runs every stored reference solution against its tests. This catches bad generated answers without paying for API generation inside Actions.

There are no required repository secrets for the daily-practice workflow.

## Run tests locally

For one problem:

```bash
python scripts/run_problem.py practice/YYYY-MM-DD-language/easy
```

To validate all reference solutions for one generated day:

```bash
python scripts/check_reference.py practice/YYYY-MM-DD-language
```

## Curriculum

The core curriculum is in [`curriculum/cs61b.md`](curriculum/cs61b.md). [`CONCEPTS.md`](CONCEPTS.md) is the living review index, and [`PROGRESS.md`](PROGRESS.md) is for periodic summaries of performance.
