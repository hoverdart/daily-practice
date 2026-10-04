# One-time setup

No OpenAI API key is required for this repository.

Daily problem generation is handled by the ChatGPT weekday automation. GitHub Actions only validates generated content after it is committed.

## What GitHub Actions does

On pushes or pull requests that touch `practice/**` (or the validation scripts), the workflow:

1. checks out the repository;
2. installs Python, Java, and Node runtimes;
3. finds every generated `practice/YYYY-MM-DD-language/` directory;
4. runs `scripts/check_reference.py` for each day;
5. fails CI if a reference solution does not compile or fails its own tests.

No repository secrets are needed.

## Local testing

Run a problem's tests with:

```bash
python scripts/run_problem.py practice/YYYY-MM-DD-language/easy
```

Validate a whole day with:

```bash
python scripts/check_reference.py practice/YYYY-MM-DD-language
```

## Daily schedule

- Monday, 9:00 AM Pacific — Python
- Tuesday, 9:00 AM Pacific — Java
- Wednesday, 9:00 AM Pacific — C++
- Thursday, 9:00 AM Pacific — C
- Friday, 9:00 AM Pacific — JavaScript
- Saturday/Sunday — rest

The ChatGPT automation should generate exactly one easy, one medium, and one hard/stretch problem, use recent attempt logs for spaced repetition, create runnable tests plus hidden-in-plain-sight `reference/` materials, and commit the new dated directory to `main`.
