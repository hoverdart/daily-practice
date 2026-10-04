# Daily Practice

A weekday interview-prep system that keeps algorithmic problem solving, data structures, and language fluency sharp.

Every weekday at **9:00 AM Pacific Time**, the repo generates three original interview-style problems for one language:

| Day | Language |
|---|---|
| Monday | Python |
| Tuesday | Java |
| Wednesday | C++ |
| Thursday | C |
| Friday | JavaScript |
| Saturday | Rest |
| Sunday | Rest |

Each day contains an **easy**, **medium**, and **hard/stretch** problem. The generator is deliberately curriculum-aware: it revisits CS61B material, uses spaced repetition, and gradually introduces adjacent interview patterns.

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
6. Commit your attempt. Future daily sets use recent attempt notes as feedback for spaced repetition.

## Philosophy

The goal is not raw LeetCode volume. The system optimizes for:

- **pattern recognition** — knowing when to reach for binary search, BFS, heaps, hashing, etc.;
- **implementation fluency** — writing the same ideas comfortably in Python, Java, C++, C, and JavaScript;
- **CS fundamentals retention** — especially the material from CS61B;
- **runtime reasoning** — being able to justify time and space complexity;
- **deliberate review** — weak concepts recur more often, strong concepts recur less often;
- **transfer** — some problems constrain library use or ask you to implement the underlying structure.

Problems are generated as **original interview-style exercises** rather than copying proprietary problem statements from LeetCode, HackerRank, Coderbyte, or similar platforms.

## Automation setup

The workflow lives at `.github/workflows/daily-practice.yml` and runs twice around the Pacific-time boundary; the generator itself proceeds only when the local time in `America/Los_Angeles` is 9 AM on a weekday. This keeps the schedule correct across daylight-saving changes.

The workflow requires one repository secret:

- `OPENAI_API_KEY` — used by `scripts/generate_daily.py` to create the day's set through the OpenAI Responses API.

Optional repository variable:

- `PRACTICE_MODEL` — defaults to `gpt-6.1-sol`.

You can also trigger the workflow manually from GitHub Actions.

## Manual generation

```bash
python -m pip install -r requirements.txt
OPENAI_API_KEY=... python scripts/generate_daily.py --force
```

Use `--date YYYY-MM-DD` to generate a particular weekday and `--force` to bypass the 9 AM scheduler guard.

## Curriculum

The core curriculum is in [`curriculum/cs61b.md`](curriculum/cs61b.md). [`CONCEPTS.md`](CONCEPTS.md) is the living review index, and [`PROGRESS.md`](PROGRESS.md) is for periodic summaries of performance.
