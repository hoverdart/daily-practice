#!/usr/bin/env python3
"""Generate one weekday's adaptive coding-practice set."""

from __future__ import annotations

import argparse
import json
import os
import re
import sys
from datetime import date, datetime
from pathlib import Path
from zoneinfo import ZoneInfo

from openai import OpenAI

ROOT = Path(__file__).resolve().parents[1]
PRACTICE = ROOT / "practice"
PACIFIC = ZoneInfo("America/Los_Angeles")

LANGUAGES = {
    0: {"name": "Python", "slug": "python", "solution": "solution.py", "tests": "tests.py", "optimal": "optimal.py"},
    1: {"name": "Java", "slug": "java", "solution": "Solution.java", "tests": "Tests.java", "optimal": "Optimal.java"},
    2: {"name": "C++", "slug": "cpp", "solution": "solution.cpp", "tests": "tests.cpp", "optimal": "optimal.cpp"},
    3: {"name": "C", "slug": "c", "solution": "solution.c", "tests": "tests.c", "optimal": "optimal.c"},
    4: {"name": "JavaScript", "slug": "javascript", "solution": "solution.js", "tests": "tests.js", "optimal": "optimal.js"},
}


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8") if path.exists() else ""


def recent_attempts(limit: int = 18) -> str:
    files = sorted(PRACTICE.glob("**/attempt.md"), key=lambda p: p.stat().st_mtime, reverse=True)
    chunks: list[str] = []
    for path in files[:limit]:
        rel = path.relative_to(ROOT)
        text = read_text(path).strip()
        if text:
            chunks.append(f"\n--- {rel} ---\n{text[:3500]}")
    return "".join(chunks) or "No prior attempts yet. Start with broad foundational coverage."


def strip_json_fence(text: str) -> str:
    text = text.strip()
    if text.startswith("```"):
        text = re.sub(r"^```(?:json)?\s*", "", text)
        text = re.sub(r"\s*```$", "", text)
    return text.strip()


def validate(payload: dict) -> None:
    problems = payload.get("problems")
    if not isinstance(problems, list) or len(problems) != 3:
        raise ValueError("Expected exactly three problems")
    expected = ["easy", "medium", "hard"]
    got = [str(p.get("difficulty", "")).lower() for p in problems]
    if got != expected:
        raise ValueError(f"Expected difficulty order {expected}, got {got}")
    required = {"title", "slug", "difficulty", "focus", "target_minutes", "problem_md", "starter_code", "tests_code", "optimal_code", "notes_md"}
    for p in problems:
        missing = required - set(p)
        if missing:
            raise ValueError(f"Missing fields for {p.get('title')}: {sorted(missing)}")


def build_prompt(target: date, lang: dict[str, str]) -> str:
    curriculum = read_text(ROOT / "curriculum" / "cs61b.md")
    concepts = read_text(ROOT / "CONCEPTS.md")
    progress = read_text(ROOT / "PROGRESS.md")
    attempts = recent_attempts()

    harness_rules = {
        "Python": "solution.py must expose the requested function(s). tests.py must import from solution and use only the standard library.",
        "Java": "Solution.java must define public class Solution. Tests.java must define public class Tests with a main method and throw AssertionError on failure. No JUnit dependency.",
        "C++": "solution.cpp should contain the requested function(s) but no main. tests.cpp must #include \"solution.cpp\" and contain main. Use C++17 standard library only.",
        "C": "solution.c should contain the requested function(s) but no main. tests.c must #include \"solution.c\" and contain main. Use C11 and the standard library only. Specify memory ownership clearly.",
        "JavaScript": "solution.js must export the requested function(s) through module.exports. tests.js must require('./solution') and use Node's built-in assert module.",
    }[lang["name"]]

    return f"""
You are designing a rigorous daily coding-practice set for a UC Berkeley CS student.

DATE: {target.isoformat()}
LANGUAGE: {lang['name']}

GOAL
Create exactly three ORIGINAL interview-style problems: easy, medium, hard. Do not copy or closely paraphrase proprietary problem statements from LeetCode, HackerRank, Coderbyte, textbooks, or course assignments. You may use common algorithmic ideas, but write a fresh scenario, fresh wording, fresh examples, and fresh tests.

PEDAGOGY
- Reinforce CS61B material and interview pattern recognition.
- Use spaced repetition: infer weak areas from the recent attempt logs below.
- Easy should usually reinforce implementation fluency or a recently weak fundamental.
- Medium should exercise a recognizable pattern with nontrivial reasoning.
- Hard should be a stretch or synthesis problem, not automatically an extreme contest problem.
- Across the three problems, avoid three variants of the same pattern.
- Prefer concepts that connect to known material, but introduce at most one genuinely new pattern per day.
- Include explicit brute-force vs. optimal reasoning in notes.
- Notes should explain recognition signals, invariants, complexity, common mistakes, and the connection to the learner's prior CS61B material.
- If using a newer interview pattern (e.g. sliding window, monotonic stack, DP), explain it from first principles and connect it to known ideas.
- Tests must include normal cases, boundary cases, and at least one adversarial/edge case.
- Starter code must contain the correct signature and TODOs but no hidden solution.

LANGUAGE / TEST HARNESS
{harness_rules}
The tests must run with `python scripts/run_problem.py <problem-folder>` from the repository root.

SOURCE CURRICULUM
{curriculum}

LIVING CONCEPT INDEX
{concepts}

PROGRESS SUMMARY
{progress}

RECENT ATTEMPTS
{attempts}

RETURN FORMAT
Return ONLY valid JSON, no Markdown fence and no commentary, with this exact shape:
{{
  "day_summary": "short paragraph describing today's focus and why",
  "new_concept": "name of new concept or empty string",
  "review_concepts": ["..."],
  "problems": [
    {{
      "title": "...",
      "slug": "lowercase-kebab-case",
      "difficulty": "easy",
      "focus": ["concept 1", "concept 2"],
      "target_minutes": 15,
      "problem_md": "complete Markdown problem statement including signature, examples, constraints, and expected complexity goal",
      "starter_code": "complete starter file",
      "tests_code": "complete runnable tests file",
      "optimal_code": "complete optimal reference solution",
      "notes_md": "complete Markdown explanation"
    }},
    {{"difficulty": "medium", "...": "same fields"}},
    {{"difficulty": "hard", "...": "same fields"}}
  ]
}}

Difficulty order MUST be easy, medium, hard.
""".strip()


def generate_payload(target: date, lang: dict[str, str]) -> dict:
    client = OpenAI()
    model = os.environ.get("PRACTICE_MODEL", "gpt-6.1-sol")
    prompt = build_prompt(target, lang)

    last_error: Exception | None = None
    for attempt in range(2):
        extra = "\nIMPORTANT: Your prior output was invalid JSON. Return strictly parseable JSON only." if attempt else ""
        response = client.responses.create(
            model=model,
            input=prompt + extra,
            max_output_tokens=22000,
        )
        try:
            payload = json.loads(strip_json_fence(response.output_text))
            validate(payload)
            return payload
        except Exception as exc:  # one repair retry
            last_error = exc
    raise RuntimeError(f"Could not obtain valid practice JSON: {last_error}")


def problem_readme(problem: dict, target: date, lang: dict[str, str]) -> str:
    focuses = ", ".join(problem["focus"])
    return f"""# {problem['title']}

- **Date:** {target.isoformat()}
- **Language:** {lang['name']}
- **Difficulty:** {problem['difficulty'].title()}
- **Focus:** {focuses}
- **Target time:** {problem['target_minutes']} minutes

Run tests from the repository root:

```bash
python scripts/run_problem.py practice/{target.isoformat()}-{lang['slug']}/{problem['difficulty']}
```

Do not open `reference/` until you have attempted the problem and filled in `attempt.md`.
"""


def write_day(target: date, lang: dict[str, str], payload: dict) -> Path:
    day_dir = PRACTICE / f"{target.isoformat()}-{lang['slug']}"
    if day_dir.exists():
        raise FileExistsError(day_dir)
    day_dir.mkdir(parents=True)

    problem_rows = []
    for p in payload["problems"]:
        problem_rows.append(f"| {p['difficulty'].title()} | {p['title']} | {', '.join(p['focus'])} | {p['target_minutes']} min |")

    day_readme = f"""# {target.isoformat()} — {lang['name']}

{payload['day_summary']}

## Today's set

| Difficulty | Problem | Focus | Target |
|---|---|---|---:|
{chr(10).join(problem_rows)}

## Review concepts

{chr(10).join('- ' + x for x in payload.get('review_concepts', []))}

## New concept

{payload.get('new_concept') or 'None — pure reinforcement day.'}

## Rules

1. Start with the easy problem, but do not feel obligated to finish the hard problem in one sitting.
2. State your intended complexity before coding when possible.
3. Run the tests, then fill in each `attempt.md`.
4. Open `reference/` only after a real attempt.
"""
    (day_dir / "README.md").write_text(day_readme, encoding="utf-8")

    attempt_template = read_text(ROOT / "templates" / "attempt.md")
    for p in payload["problems"]:
        folder = day_dir / p["difficulty"]
        ref = folder / "reference"
        ref.mkdir(parents=True)
        (folder / "README.md").write_text(problem_readme(p, target, lang), encoding="utf-8")
        (folder / "problem.md").write_text(p["problem_md"].rstrip() + "\n", encoding="utf-8")
        (folder / lang["solution"]).write_text(p["starter_code"].rstrip() + "\n", encoding="utf-8")
        (folder / lang["tests"]).write_text(p["tests_code"].rstrip() + "\n", encoding="utf-8")
        (folder / "attempt.md").write_text(attempt_template, encoding="utf-8")
        (ref / lang["optimal"]).write_text(p["optimal_code"].rstrip() + "\n", encoding="utf-8")
        (ref / "notes.md").write_text(p["notes_md"].rstrip() + "\n", encoding="utf-8")

    return day_dir


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--date", help="Generate YYYY-MM-DD instead of today's Pacific date")
    parser.add_argument("--force", action="store_true", help="Bypass weekday/9AM scheduler guard")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    now = datetime.now(PACIFIC)
    target = date.fromisoformat(args.date) if args.date else now.date()

    if target.weekday() >= 5:
        print(f"{target}: weekend rest day; nothing generated.")
        return 0

    if not args.force and not args.date and now.hour != 9:
        print(f"Pacific time is {now:%H:%M}; scheduler guard requires the 9 AM hour.")
        return 0

    lang = LANGUAGES[target.weekday()]
    day_dir = PRACTICE / f"{target.isoformat()}-{lang['slug']}"
    if day_dir.exists():
        print(f"Already exists: {day_dir.relative_to(ROOT)}")
        return 0

    payload = generate_payload(target, lang)
    created = write_day(target, lang, payload)
    print(f"Created {created.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
