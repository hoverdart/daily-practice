#!/usr/bin/env python3
"""Verify generated reference solutions against their generated tests."""

from __future__ import annotations

import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RUNNER = ROOT / "scripts" / "run_problem.py"

PAIRS = [
    ("solution.py", "optimal.py"),
    ("Solution.java", "Optimal.java"),
    ("solution.cpp", "optimal.cpp"),
    ("solution.c", "optimal.c"),
    ("solution.js", "optimal.js"),
]


def check(folder: Path) -> bool:
    pair = next(((s, o) for s, o in PAIRS if (folder / s).exists()), None)
    if not pair:
        print(f"Cannot identify language in {folder}", file=sys.stderr)
        return False

    solution_name, optimal_name = pair
    optimal = folder / "reference" / optimal_name
    if not optimal.exists():
        print(f"Missing reference solution: {optimal}", file=sys.stderr)
        return False

    with tempfile.TemporaryDirectory(prefix="daily-practice-") as tmp:
        copy = Path(tmp) / folder.name
        shutil.copytree(folder, copy)
        shutil.copy2(copy / "reference" / optimal_name, copy / solution_name)
        result = subprocess.run([sys.executable, str(RUNNER), str(copy)])
        return result.returncode == 0


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: python scripts/check_reference.py practice/YYYY-MM-DD-language", file=sys.stderr)
        return 2

    day = Path(sys.argv[1]).resolve()
    ok = True
    for difficulty in ("easy", "medium", "hard"):
        folder = day / difficulty
        print(f"\n== Checking {folder} ==")
        ok = check(folder) and ok
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
